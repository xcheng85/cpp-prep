class Bank {
public:
    Bank(vector<long long>& balance) : _balance(balance) {}

    bool transfer(int account1, int account2, long long money) {
        if (account1 > _balance.size() || account2 > _balance.size())
            return false;
        if (_balance[account1 - 1] < money) {
            return false;
        }
        _balance[account1 - 1] -= money;
        _balance[account2 - 1] += money;
        return true;
    }

    bool deposit(int account, long long money) {
        if (account > _balance.size())
            return false;
        _balance[account - 1] += money;
        return true;
    }

    bool withdraw(int account, long long money) {
        if (account > _balance.size())
            return false;
        if (_balance[account - 1] < money) {
            return false;
        }
        _balance[account - 1] -= money;
        return true;
    }

private:
    vector<long long>& _balance;
};

/**
 * Your Bank object will be instantiated and called as such:
 * Bank* obj = new Bank(balance);
 * bool param_1 = obj->transfer(account1,account2,money);
 * bool param_2 = obj->deposit(account,money);
 * bool param_3 = obj->withdraw(account,money);
 */