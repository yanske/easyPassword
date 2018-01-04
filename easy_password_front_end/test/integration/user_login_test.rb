require 'test_helper'

class UserLoginTest < ActionDispatch::IntegrationTest
  def setup
    @user = User.new(
      first_name: "Yan",
      last_name: "Ke",
      email: "test@1.com",
      password: "123456",
      password_confirmation: "123456"
    )

    @user.save
  end

  test "valid login" do
    get login_path
    post login_path, params: {
      session: {
        email: "test@1.com",
        password: "123456"
      }
    }

    assert is_logged_in?
    assert_redirected_to user_path(@user)
    follow_redirect!
    assert_template 'users/show'
  end

  test "invalid login" do
    post login_path, params: {
      session: {
        email: "test@1.com",
        password: "12345"
      }
    }

    assert_not is_logged_in?
  end
end
