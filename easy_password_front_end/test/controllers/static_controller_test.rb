require 'test_helper'

class StaticControllerTest < ActionDispatch::IntegrationTest
  test "should get route" do
    get root_path
    assert_response :success
  end

  test "should get contact" do
    get contact_path
    assert_response :success
  end
end
