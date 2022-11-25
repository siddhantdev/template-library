struct Edge {
    ll x, y, w;
    ll id;

    bool operator<(const Edge& other) const {
        return w > other.w;
    }

    void print() {
        cout << id << sp << x << sp << y << sp << w << nl;
    }
};
