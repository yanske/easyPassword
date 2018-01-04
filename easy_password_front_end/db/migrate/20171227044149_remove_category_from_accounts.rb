class RemoveCategoryFromAccounts < ActiveRecord::Migration[5.1]
  def change
    remove_column :accounts, :category, :integer
  end
end
