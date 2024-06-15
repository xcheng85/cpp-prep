class Cashier {
public:
    // every nth 
    Cashier(int n, int discount, vector<int>& products, vector<int>& prices):
    _n{n} {
        _discountRatio = 1.0 - (double)discount * 0.01;
        assert(products.size() == prices.size());

        for(int i = 0; i < products.size(); ++i) {
            _cache.insert(make_pair(products[i], prices[i]));
        } 
    }
    
    double getBill(vector<int> product, vector<int> amount) {
        // At most 1000 calls will be made to getBill.
        double res;
        ++_callId;
        assert(product.size() == amount.size());

        double applyedDiscountRatio = (_callId % _n == 0 ? _discountRatio : 1.0);
        for(int i = 0; i < product.size(); ++i) {
            res += (applyedDiscountRatio * _cache[product[i]] * amount[i]);
            //cout << res << endl;;
        }
        return res;
    }

private: 
    int _callId = 0;
    unordered_map<int, int> _cache;
    double _discountRatio;
    int _n;

    // product to price
    // call times for getBill, 
    // bill * ((100 - discount) / 100) 
};

/**
 * Your Cashier object will be instantiated and called as such:
 * Cashier* obj = new Cashier(n, discount, products, prices);
 * double param_1 = obj->getBill(product,amount);
 */