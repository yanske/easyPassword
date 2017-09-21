#include "FacialRecognition.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/contrib/contrib.hpp"
#include <iostream>
#include <conio.h>
#include <vector>
#include <string>

#define CASCADE_PATH  "./haarcascade_frontalface_default.xml"

FacialRecognition::FacialRecognition()
{
    //ctor
}

FacialRecognition::~FacialRecognition()
{
    //dtor
}

void FacialRecognition::createTrainingSet(const int count, cv::VideoCapture & capWebcam, std::string dir)
{
	std::cout << "Press 'C' to take the picture." << std::endl;
	std::cout << "Taking 5 training pictures." << std::endl;

	if (capWebcam.isOpened() == false)
	{
		std::cout << "error: capWebcam not accessed successfully\n\n";
	}
	else
	{
		cv::Mat imgOriginal;
		char charCheckForEscKey = 0;
		int i = 1;

		std::vector<int> compression_params;
		compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION); //specify the compression technique
		compression_params.push_back(5); //specify the compression quality

		while (charCheckForEscKey != 27 && capWebcam.isOpened() && i <= count) {       //27 is escape key
			capWebcam >> imgOriginal;
			// declare windows
			cv::namedWindow("imgOriginal", CV_WINDOW_NORMAL);
			cv::imshow("imgOriginal", imgOriginal);
			if (charCheckForEscKey == 'C')
			{
				std::string source = dir + std::to_string(i) + ".png";
				if (cv::imwrite(source, imgOriginal))
				{
					i++;
					std::cout << "Image taken." << std::endl;
				}
			}
			charCheckForEscKey = cv::waitKey(1) & 0xFF;
		}   // end while
	}
}

void FacialRecognition::readTrainingSet(const int count, std::vector<cv::Mat>& training, std::string dir)
{
	for (int i = 0; i < count; i++)
	{
		std::string path = dir + std::to_string(i + 1) + ".png";
		training.push_back(cv::imread(path, CV_LOAD_IMAGE_COLOR));
	}
}

cv::Mat FacialRecognition::processForDetection(cv::Mat img, int convert = CV_BGR2GRAY)
{
	cv::Mat temp;
	cv::cvtColor(img, temp, CV_BGR2GRAY);
	cv::equalizeHist(temp, temp);
	return temp;
}

void FacialRecognition::setup()
{
	const int count = 2;
	std::string imgName = "./test";
	std::string trainingName = "./training";
	std::vector<cv::Mat> trainingSet;
	//creates training set for facial recognition

	cv::VideoCapture capWebcam(0);
	createTrainingSet(count, capWebcam, imgName);
	readTrainingSet(count, trainingSet, imgName);


	double scaleFactor = 1.01;
	double minSizeRatio = 0.06*3;
	double maxSizeRatio = 0.18*3;
	int minNeighbors = 40;
	cv::CascadeClassifier face_cascade;
	if (!face_cascade.load(CASCADE_PATH))
	{
		int x;
		std::cout << "Error loading cascade!";
		std::cin >> x;
		return -1;
	}


	std::vector<cv::Mat> processed;
	std::vector<cv::Rect> res;

	int width = trainingSet[0].size().width;
	int height = trainingSet[0].size().height;

	cv::Size minScaleSize = cv::Size(minSizeRatio * width, minSizeRatio*height);
	cv::Size maxScaleSize = cv::Size(maxSizeRatio * width, maxSizeRatio*height);

	//processes training data set, returns it in vector processed
	for (int i = 0; i < count; i++)
	{
		processed.push_back(processForDetection(trainingSet[i]));
		face_cascade.detectMultiScale(processed[i], res, scaleFactor, minNeighbors, 0, minScaleSize, maxScaleSize);
		processed[i] = processed[i](res[0]);

		//read the image from storage
		cv::imwrite(trainingName + std::to_string(i + 1) + ".png", processed[i]);
	}

	//display one of the training data
	/*
    cv::namedWindow("imgOriginal", CV_WINDOW_NORMAL);
    cv::imshow("imgOriginal", processed[0]);

    cv::namedWindow("face", CV_WINDOW_NORMAL);
    cv::imshow("face", trainingSet[0]); */

    //for each image of the training set, reduce to single row
    std::vector<std::vector<double>> matrix;

    for (int i = 0; i < count; i++)
    {
        if(trainingSet[i].isContinuous())
        {
            cv::Mat temp = trainingSet[i];
            std::vector<double> tempRow;

            double *ptrMat = temp.ptr<double>();
            for(int j = 0; j < temp.total() ; j++)
            {
                tempRow.push_back(ptrMat[j]);
            }

            matrix.push_back(tempRow);
        } else {
            std::cout<< "Error! Mat not continuous!";
        }
    }

    //calculate average image and subtract the average from each image
    std::vector<double> averageImage;
    for(int i = 0; i < matrix.at(0).size(); i++)
    {
        double sum = 0;
        for(int j = 0; j < matrix.size(); j++)
        {
            sum += matrix.at(j).at(i);
        }
        averageImage.push_back(sum/matrix.size());
    }

    //subtract the average image from each image
    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix.at(i).size(); j++)
        {
            matrix.at(i)[j] = averageImage[j] - matrix.at(i)[j];
        }
    }

    //TODO: derive the co-variance matrix

	cv::waitKey(0) & 0xFF;

	return;
}
