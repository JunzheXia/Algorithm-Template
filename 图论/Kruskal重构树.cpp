kruskal重构树可能于与树上问题结合，这也是常考的地方，是一颗二叉树。
有时要注意合并的顺序

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define INF 0x7fffffff
using ll = long long;
const int N = 6e5 + 10;
int n, m, cnt;
struct node {
    int u, v, w;
    bool operator<(const node& other) const { return w < other.w; }
    //const不能少
};
int fa[N], val[N];
vector<node> g;
vector<vector<int>> tree;
int f[N][21], dep[N];
int root(int x) { return fa[x] = fa[x] == x ? x : root(fa[x]); }
void kruskal() {
    sort(g.begin(), g.end());
    for (int i = 1; i <= 2 * n; i++) {
        fa[i] = i;
    }
    cnt = n;
    tree.resize(2 * n + 1);
    //2*n+1就够了
    for (const auto& edge : g) {
        int u = edge.u, v = edge.v, w = edge.w;
        int fu = root(u), fv = root(v);
        if (fv != fu) {
            //可以画图模拟
            cnt++;
            val[cnt] = w;
            tree[cnt].push_back(fv);
            tree[cnt].push_back(fu);
            fa[fv] = fa[fu] = cnt;
        }
    }
}
void dfs(int u, int p) {
    dep[u] = dep[p] + 1;
    f[u][0] = p;
    for (int i = 1; i <= 19; i++) {
        f[u][i] = f[f[u][i - 1]][i - 1];
    }
    for (int v : tree[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
}
int lca(int u, int v) {
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    for (int i = 19; i >= 0; i--) {
        if (dep[f[u][i]] >= dep[v]) {
            u = f[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = 19; i >= 0; i--) {
        if (f[u][i] != f[v][i]) {
            u = f[u][i], v = f[v][i];
        }
    }
    return f[u][0];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.push_back({ u, v, w });
    }
    kruskal();
    //主要防止可能有多个连通分量
    for (int i = cnt; i >= 1; i--) {
        if (fa[i] == i) {
            dfs(i, 0);
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        if (root(u) != root(v)) {
            cout << "impossible" << endl;
        }
        else if (u == v) {
            cout << 0 << endl;
        }
        else
            cout << val[lca(u, v)] << endl;
    }
    return 0;
}
