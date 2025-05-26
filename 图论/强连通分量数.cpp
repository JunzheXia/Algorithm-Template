该代码计算的是点数大于2的强连通分量数
强连通分量一般在有向图中求
  
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 1e4 + 10;
int n, m;
vector<int> g[N];
int dfn[N], low[N], id;
bool vis[N];
stack<int> s;
int ans;

void tarjan(int u) {
    dfn[u] = low[u] = ++id;
    s.push(u);
    vis[u] = 1;
    for (int v : g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        int cnt = 0;
        while (s.size()) {
            int v = s.top();
            s.pop();
            vis[v] = 0;
            cnt++;
            if (v == u)
                break;
        }
        if (cnt >= 2)//计算点数大于2的强连通分量数
            ans++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }
    cout << ans;
    return 0;
}
