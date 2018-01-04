require 'test_helper'

class UserSignupTest < ActionDispatch::IntegrationTest
  test "valid user signup" do
    # validate signup page
    get signup_path
    assert_select 'form[id="new_user"]', count: 1

    # validate post request
    assert_difference 'User.count', 1 do
      post signup_path, params: {
        user: {
          first_name: "Yan",
          last_name: "Ke",
          email: "yan@ke.com",
          password: "123456",
          password_confirmation: "123456"
        }
      }
    end

    follow_redirect!
    assert is_logged_in?
    assert_template 'users/show'
  end

  test "invalid user signup" do
    get signup_path
    assert_select 'form[id="new_user"]', count: 1

    # validate post request
    assert_no_difference 'User.count' do
      post signup_path, params: {
        user: {
          first_name: "Yan",
          last_name: "Ke",
          email: "",
          password: "123456",
          password_confirmation: "123456"
        }
      }
    end

    assert_template 'users/new'
    assert_select 'div.user-errors', count: 1
  end
end
