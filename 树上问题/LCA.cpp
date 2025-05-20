最近公共祖先，有根节点。可以求树上两点的简单路径。
//要注意，该代码默认根是1，如果根不是1，自行修改
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 1e5 + 10;
int n;
vector<int> dep(N);
vector<int> g[N];
vector<vector<int>> fa(N, vector<int>(25));

void dfs(int u, int p) {
    dep[u] = dep[p] + 1;
    fa[u][0] = p;
    for (int i = 1; i <= 20; i++) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for (const auto &v : g[u]) {
        if (v == p)
            continue;
        dfs(v, u);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = 20; i >= 0; i--) {
        if (dep[fa[u][i]] >= dep[v]) {
            u = fa[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = 20; i >= 0; i--) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
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
    dfs(1, 0);
    cout << lca(6, 7);
    return 0;
}
