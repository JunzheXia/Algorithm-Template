struct DSU {
    vector<int> f;
    DSU() {}
    DSU(int n) { init(n); }

    void init(int n) {
        f.resize(n);
        iota(f.begin(), f.end(), 0);
    }

    int find(int x) { return f[x] = f[x] == x ? x : find(f[x]); }

    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) {
            return 0;
        }
        f[y] = x;
        return 1;
    }
};
