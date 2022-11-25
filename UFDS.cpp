struct UFDS {
    vi link, sz;
    int n;

    UFDS(int N) {
        init(N);
    }

    void init(int N) {
        n = N;
        link = vi(n);
        iota(all(link), 0);
        sz = vi(n, 1);
    }

    ll find(ll x) {
        return (link[x] == x ? x : link[x] = find(link[x]));
    }

    void unite(ll a, ll b) {
        a = find(a);
        b = find(b);
        if(a == b) return;
        if(sz[a] < sz[b]) swap(a, b);

        sz[a] += sz[b];
        link[b] = a;
    }

    bool same(ll a, ll b){
        return (find(a) == find(b));
    }
};
