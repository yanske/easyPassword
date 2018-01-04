require 'test_helper'

class UsersControllerTest < ActionDispatch::IntegrationTest
  def setup
    @user = users(:one)
  end
  
  test "should get new" do
    get signup_path
    assert_response :success
  end

  test "should redirect show if not logged in" do
    get user_path(@user)
    
    assert_redirected_to login_path
    follow_redirect!

    assert_select 'div.alert', count: 1
  end
end
