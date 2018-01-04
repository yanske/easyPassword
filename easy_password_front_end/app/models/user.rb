class User < ApplicationRecord
    # valid inputs
    validates :first_name, presence: true
    validates :last_name, presence: true
    validates :email, presence: true, uniqueness: {case_sensitive: false}, format: {with: /\A[\w+\-.]+@[a-z\d\-.]+\.[a-z]+\z/i}
    validates :password, presence: true, length: {minimum: 6}

    # lowercase email
    before_save {self.email.downcase!}

    # used for password digest
    has_secure_password

    # define account relation
    has_many :accounts, dependent: :destroy
end
