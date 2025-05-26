#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 1e4 + 10;
int n, m;
vector<int> g[N], ng[N]; // 原图和缩点后的图
int a[N], low[N], dfn[N], id;
int sd[N], ind[N], dp[N];
bool vis[N];
stack<int> s;

void tarjan(int u) {
    low[u] = dfn[u] = ++id;
    vis[u] = 1;
    s.push(u);
    for (int v : g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {//发现强连通分量根
        while (s.size()) {
            int v = s.top();
            s.pop();
            vis[v] = 0;
            sd[v] = u;//缩点到u
            if (u == v)
                break;
            a[u] += a[v];//合并权值
        }
    }
}

int topo() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (sd[i] == i && !ind[i]) {
            q.push(i);
            dp[i] = a[i];
        }
    }
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int v : ng[u]) {
            dp[v] = max(dp[v], dp[u] + a[v]);
            if (--ind[v] == 0)
                q.push(v);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[i]);
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v); // 有向图
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            tarjan(i);
    }
    for (int u = 1; u <= n; u++) {
        for (int v : g[u]) {
            if (sd[u] != sd[v]) {
                ng[sd[u]].push_back(sd[v]);
                ind[sd[v]]++;
            }
        }
    }
    cout << topo(); // 拓扑排序+动态规划求最长路径
    return 0;
}
