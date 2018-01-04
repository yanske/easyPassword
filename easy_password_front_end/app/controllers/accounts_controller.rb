class AccountsController < ApplicationController
  before_action :logged_in_user
  before_action :correct_user, only: [:show, :edit, :update, :delete]

  def new
    @account = Account.new
  end

  def create
    puts account_params
    @account = Account.new(account_params)
    if @account.save
      flash[:success] = "#{@account.name} has been added!"
      redirect_to user_path(current_user)
    else
      flash.now[:danger] = @account.errors.full_messages.join(', ')
      render 'accounts/new'
    end
  end

  def show
    @account = Account.find(params[:id])
    @password = decrypt_password(@account.encrypted_password)
  end

  def edit
    @account = Account.find(params[:format])
  end

  def update
    @account = Account.find(params[:id])
    if @account.update_attributes(account_params)
      flash[:success] = "#{@account.name} successfully updated!"
      redirect_to current_user
    else
      flash[:danger] = "Error!"
      render 'edit'
    end
  end

  def destroy
    @account = Account.find(params[:id])
    name = @account.name
    @account.delete
    flash[:success] = "#{name} successfully deleted!"
    redirect_to current_user
  end

  private 
    def logged_in_user
      unless is_logged_in?
        flash[:danger] = "Please login to access accounts!"
        redirect_to login_path
      end
    end

    def correct_user
      account = Account.find_by(id: params[:id]) || Account.find_by(id: params[:format])
      unless is_current_user?(account.user)
        flash[:danger] = "Not your account!"
        redirect_to current_user
      end
    end

    def account_params
      params.require(:account).permit(:name, :login, :encrypted_password, :category, :note).merge({:user => current_user})
    end

    def decrypt_password(password)
      crypt = ActiveSupport::MessageEncryptor.new(Rails.application.secrets.secret_key_base)
      crypt.decrypt_and_verify(password)
    end
end
