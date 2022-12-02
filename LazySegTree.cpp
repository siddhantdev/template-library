struct SegTree {
    vi tree;
    vi vals;
    ll NE = 0;
    ll NP = -1;
    ll n;

    SegTree(int N) {
        init(N);
    }

    void init(int N) {
        n = N;
        while(__builtin_popcountll(n) != 1) ++n;
        tree.resize(2 * n, 0);
        vals.resize(2 * n, 0);
    }

    ll modify(ll lhs, ll rhs, ll len) {
        if(rhs == NP)
            return lhs;
        return rhs * len;
    }

    ll comb(ll lhs, ll rhs) {
        return lhs + rhs;
    }

    void propagate(ll k, ll x, ll y) {
        if(x == y) return;
        ll m = (x + y) / 2;
        tree[2 * k] = modify(tree[2 * k], tree[k], 1);
        vals[2 * k] = modify(vals[2 * k], tree[k], m - x + 1);
        tree[2 * k + 1] = modify(tree[2 * k + 1], tree[k], 1);
        vals[2 * k + 1] = modify(vals[2 * k + 1], tree[k], y - m);
        tree[k] = NP;
    }

    void update(ll a, ll b, ll x, ll y, ll k, ll v) {
        propagate(k, x, y);
        if(a > y || b < x) return;
        if(a <= x && y <= b) {
            tree[k] = modify(tree[k], v, 1);
            vals[k] = modify(vals[k], v, y - x + 1);
            return;
        }

        ll d = (x + y) / 2;
        update(a, b, x, d, 2 * k, v);
        update(a, b, d + 1, y, 2 * k + 1, v);
        vals[k] = comb(vals[2 * k], vals[2 * k + 1]);
    }

    void update(ll a, ll b, ll v) {
        update(a, b, 0, n - 1, 1, v);
    }

    ll query(ll a, ll b, ll x, ll y, ll k) {
        propagate(k, x, y);
        if(a > y || b < x) return NE;
        if(a <= x && y <= b) {
            return vals[k];
        }

        ll d = (x + y) / 2;
        ll m1 = query(a, b, x, d, 2 * k);
        ll m2 = query(a, b, d + 1, y, 2 * k + 1);
        return comb(m1, m2);
    }

    ll query(ll a, ll b) {
        return query(a, b, 0, n - 1, 1);
    }

    void print() {
        FOR(i, 1, 2 * n) {
            cout << i << " : " << tree[i]  << sp << vals[i] << nl;
        }
    }
};
