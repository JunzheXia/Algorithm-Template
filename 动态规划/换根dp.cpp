#include <bits/stdc++.h>
#define int long long

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 1e5 + 10;
int n;
int c[N], siz[N], f[N];
// siz是以u为根子树大小（c数组） f是所有点到u的距离
vector<pair<int, int>> g[N];
int ans = LLONG_MAX;

void dfs1(int u, int p) {
    siz[u] = c[u];
    for (auto [v, w] : g[u]) {
        if (v == p)
            continue;
        dfs1(v, u);
        siz[u] += siz[v];
        f[u] += f[v] + siz[v] * w;
    }
}

void dfs2(int u, int p) {
    ans = min(ans, f[u]);
    for (auto [v, w] : g[u]) {
        if (v == p)
            continue;
        // 换根公式：
        // 当根从u换到v时：
        // 1. 原u的子树v部分距离减少siz[v]*w
        // 2. 其他部分（siz[1]-siz[v]）距离增加w
        f[v] = f[u] - siz[v] * w + (siz[1] - siz[v]) * w;
        dfs2(v, u);
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    cout << ans;

    return 0;
}
