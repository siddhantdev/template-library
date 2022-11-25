struct SegTree {
    vi tree;
    ll id;
    ll n;

    SegTree(int N) {
        init(N, 0);
    }

    SegTree(int N, int x) {
        init(N, x);
    }

    void init(int N, int x) {
        id = x;
        n = N;
        while(__builtin_popcountll(n) != 1) ++n;
        tree.resize(2 * n, id);
    }

    void update(ll x, ll k) {
        k += n;
        tree[k] = x;

        for(k /= 2; k >= 1; k /= 2) {
            tree[k] = comb(tree[2 * k], tree[2 * k + 1]);
        }
    }

    ll query(int a, int b, int x, int y, int k) {
        if(a > y || b < x) return id;
        if(a <= x && y <= b) return tree[k];

        int d = (x + y) / 2;
        return comb(query(a, b, x, d, 2 * k), query(a, b, d + 1, y, 2 * k + 1));
    }

    ll query(int a, int b) {
        return query(a, b, 0, n - 1, 1);
    }

    ll comb(ll lhs, ll rhs) {
        return lhs + rhs;
    }

    void print() {
        FOR(i, 1, 2 * n) {
            cout << i << " : " << tree[i] << nl;
        }
    }
};
