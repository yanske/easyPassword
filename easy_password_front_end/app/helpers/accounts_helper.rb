module AccountsHelper
    def account_description(account)
        cat = Category.find(account.category).name
        cat = cat + " | " + account.note unless account.note.empty?
        cat
    end

    def decrypt_password
    end
end
