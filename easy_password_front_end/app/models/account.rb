class Account < ApplicationRecord
  # validate name, login, and password fields
  validates :name, presence: true
  validates :login, presence: true
  validates :encrypted_password, presence: true

  # encrypt password before saving
  before_save :encrypt_password

  # associated with a user object
  belongs_to :user

  private
    def encrypt_password
      crypt = ActiveSupport::MessageEncryptor.new(Rails.application.secrets.secret_key_base)
      self.encrypted_password = crypt.encrypt_and_sign(self.encrypted_password)
    end
end
