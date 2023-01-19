struct UFDS {
    struct state {
        ll u, v;
        ll sz_u, sz_v;
    };

    vi link, sz;
    stack<state> r;
    ll comp;
    int n;

    UFDS(int N) {
        init(N);
    }

    void init(int N) {
        n = N;
        comp = n;
        link = vi(n);
        iota(all(link), 0);
        sz = vi(n, 1);
    }

    ll find(ll x) {
        if(link[x] == x)
            return x;
        return find(link[x]);
    }

    ll unite(ll a, ll b) {
        a = find(a);
        b = find(b);
        if(a == b) return comp;
        if(sz[a] < sz[b]) swap(a, b);

        --comp;
        r.push({a, b, sz[a], sz[b]});
        sz[a] += sz[b];
        link[b] = a;
        return comp;
    }

    void check() {
        r.push({-1, -1, -1, -1});
    }

    ll rollback() {
        while(!r.empty()) {
            state curr = r.top();
            r.pop();
            if(curr.u == -1) break;
            link[curr.u] = curr.u;
            sz[curr.u] = curr.sz_u;
            link[curr.v] = curr.v;
            sz[curr.v] = curr.sz_v;
            ++comp;
        }
        return comp;
    }

    bool same(ll a, ll b){
        return (find(a) == find(b));
    }
};
