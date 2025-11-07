#include <bits/stdc++.h>
//询问字数有多少种不同颜色  重链剖分
using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 1e5 + 10;

vector<int> g[N];
int sz[N], a[N], cnt[N], ans[N], son[N];
int n, m, sum;

void dfs1(int u, int p) {
    sz[u] = 1;
    int mx = 0;
    for (int v : g[u]) {
        if (v == p) {
            continue;
        }
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[v] > mx) {
            mx = sz[v];
            son[u] = v;
        }
    }
}

void add(int u, int p, int val) {
    if (val == 1) {
        if (++cnt[a[u]] == 1) {
            sum++;
        }
    } else {
        if (--cnt[a[u]] == 0) {
            sum--;
        }
    }
    for (int v : g[u]) {
        if (v == p) {
            continue;
        }
        add(v, u, val);
    }
}

void dfs2(int u, int p, int keep) {
    for (int v : g[u]) {
        if (v == p || v == son[u]) {
            continue;
        }
        dfs2(v, u, 0);
    }
    if (son[u]) {
        dfs2(son[u], u, 1);
    }
    if (++cnt[a[u]] == 1) {
        sum++;
    }
    for (int v : g[u]) {
        if (v == p || v == son[u]) {
            continue;
        }
        add(v, u, 1);
    }
    ans[u] = sum;
    if (!keep) {
        if (--cnt[a[u]] == 0) {
            sum--;
        }
        for (int v : g[u]) {
            if (v == p)
                continue;
            add(v, u, -1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cin >> m;

    dfs1(1, 0);
    dfs2(1, 0, 1);

    for (int i = 1; i <= m; i++) {
        int u;
        cin >> u;
        cout << ans[u] << '\n';
    }

    return 0;
}
