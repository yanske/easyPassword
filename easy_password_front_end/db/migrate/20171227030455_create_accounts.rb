class CreateAccounts < ActiveRecord::Migration[5.1]
  def change
    create_table :accounts do |t|
      t.string :login
      t.string :encrypted_password
      t.integer :category
      t.text :note
      t.references :user, foreign_key: true

      t.timestamps
    end
    add_index :accounts, :login
  end
end
