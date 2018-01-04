module SessionsHelper
    def login(user)
        session[:user_id] = user.id
    end

    def logout
        session.delete(:user_id)
    end

    # ensures that the user in the session still exists
    def is_logged_in?
        !session[:user_id].nil? && User.find_by(id: session[:user_id])
    end

    def current_user
        User.find_by(id: session[:user_id])
    end

    def is_current_user?(user)
        user == current_user
    end
end
