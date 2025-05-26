割点指在无向图中删除该点及其相连的边后，图的连通分量会增加，也可以说是破坏了图的连通性。

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 2e4 + 10;
int n, m;
vector<int> g[N];
set<int> dot;
int low[N], dfn[N], id;
// dfn是时间戳，low记录节点同过回边能到达的最小dfn值

void tarjan(int u, int p) {
    dfn[u] = low[u] = ++id;
    int child = 0;
    for (int v : g[u]) {
        if (!dfn[v]) {
            child++;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u] && p != 0) { // 判断割点条件
                dot.insert(u);
            }
        } else if (v != p) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (p == 0 && child > 1) {
        dot.insert(u); // 保证度只有1的点不被错误判为割点
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
        g[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i, 0);
        }
    }
    cout << dot.size() << endl;
    for (int d : dot) {
        cout << d << ' ';
    }
    return 0;
}

割边与割点十分相似，主要的区别就是在判断上
删除边后，图的连通分量增加

#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e4 + 10;
vector<int> g[N];
vector<pair<int, int>> bridges;  // 存储割边
int low[N], dfn[N], id;

void tarjan(int u, int p) {
    dfn[u] = low[u] = ++id;
    for (int v : g[u]) {
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            // 割边判断条件
            if (low[v] > dfn[u]) {//与割点判断的区别
                bridges.emplace_back(min(u, v), max(u, v));
            }
        } else if (v != p) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i, 0);
        }
    }
    
    // 输出割边（按字典序排序）
    sort(bridges.begin(), bridges.end());
    cout << bridges.size() << endl;
    for (auto [u, v] : bridges) {
        cout << u << " " << v << endl;
    }
    return 0;
}
