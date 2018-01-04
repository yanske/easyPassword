class UsersController < ApplicationController
  before_action :logged_in_user, only: [:show, :edit, :update, :destroy]
  before_action :correct_user, only: [:show, :edit, :update, :destroy]

  def new
    @user = User.new
  end

  def show
    @user = User.find(params[:id])
    @accounts = @user.accounts
  end

  def create
    @user = User.new(user_params)
    if @user.save
      login(@user)
      redirect_to @user
    else
      render 'new'
    end
  end

  def edit
    # load existing user for update request
    @user = User.find(params[:id])
  end

  def update
    @user = User.find(params[:id])
    if @user.update_attributes(user_params)
      flash.now[:success] = "User updated!"
      render 'edit'
    else
      render 'edit'
    end
  end

  def destroy
    @user = User.find(params[:id])
    first_name = @user.first_name
    @user.delete
    flash[:success] = "#{first_name}'s account has been deleted."
    logout
    redirect_to root_path
  end

  private 
    def user_params
      params.require(:user).permit(:first_name, :last_name, :email, :password, :password_confirmation)
    end

    def logged_in_user
      unless is_logged_in?
        flash[:danger] = "Please login to access accounts!"
        redirect_to login_path
      end
    end

    def correct_user
      unless is_current_user?(User.find(params[:id]))
        flash[:danger] = "Please login as correct user!"
        redirect_to root_path 
      end
    end
end
