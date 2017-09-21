#ifndef FACIALRECOGNITION_H
#define FACIALRECOGNITION_H

#include <opencv2/core/core.hpp>

class FacialRecognition
{
    public:
        FacialRecognition();
        virtual ~FacialRecognition();
        void createTrainingSet(const int count, cv::VideoCapture & capWebcam, std::string dir);
        void readTrainingSet(const int count, std::vector<cv::Mat>& training, std::string dir);
        cv::Mat processForDetection(cv::Mat img, int convert = CV_BGR2GRAY);
        void setup();
    protected:

    private:
};

#endif // FACIALRECOGNITION_H
