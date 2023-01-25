struct BIT {
    ll n;
    vi tree;

    BIT(ll N) {
        n = N;
        tree.resize(n + 1, 0);
    }

    void add(ll x, ll k) {
        while(k <= n) {
            tree[k] += x;
            k += (k&-k);
        }
    }

    ll sum(ll k) {
        ll s = 0;
        while(k >= 1) {
            s += tree[k];
            k -= (k&-k);
        }
        return s;
    }
};
