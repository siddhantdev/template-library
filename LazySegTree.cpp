struct node {
    ll lazy, val;

    node() {
        lazy = val = 0;
    }

    node(ll x) {
        lazy = 0;
        val = x;
    }
};

struct SegTree {
    vector<node> tree;
    node id;
    ll n;

    SegTree(int N) {
        n = N;
        while(__builtin_popcountll(n) != 1)
            ++n;
        id = node(0);
        tree.resize(2 * n, id);
    }

    node modify(node x, ll v, ll len) {
        x.val += v * len;
        x.lazy += v;
        return x;
    }

    node merge(node a, node b) {
        node res;
        res.val = a.val + b.val;
        return res;
    }

    void prop(ll k, ll x, ll y) {
        if(x == y) {
            tree[k].lazy = 0;
            return;
        }

        tree[2 * k] = modify(tree[2 * k], tree[k].lazy, (y - x + 1) / 2);
        tree[2 * k + 1] = modify(tree[2 * k + 1], tree[k].lazy, (y - x + 1) / 2);
        tree[k].lazy = 0;
    }

    void update(ll a, ll b, ll x, ll y, ll k, ll v) {
        prop(k, x, y);
        if(x > b || y < a)
            return;
        if(a <= x && y <= b) {
            tree[k] = modify(tree[k], v, y - x + 1);
            return;
        }

        ll d = (x + y) / 2;
        update(a, b, x, d, 2 * k, v);
        update(a, b, d + 1, y, 2 * k + 1, v);
        tree[k] = merge(tree[2 * k], tree[2 * k + 1]);
    }

    void update(ll a, ll b, ll v) {
        update(a, b, 0, n - 1, 1, v);
    }

    node query(ll a, ll b, ll x, ll y, ll k) {
        prop(k, x, y);
        if(x > b || y < a) return id;
        if(a <= x && y <= b) return tree[k];

        ll d = (x + y) / 2;
        node q1 = query(a, b, x, d, 2 * k);
        node q2 = query(a, b, d + 1, y, 2 * k + 1);
        return merge(q1, q2);
    }

    node query(ll a, ll b) {
        return query(a, b, 0, n - 1, 1);
    }
};
