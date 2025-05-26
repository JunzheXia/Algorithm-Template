2-SAT  也可以用作判断两个点是否处于同一强连通分量中
可以解决蕴含图问题

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 2e6 + 10;
int low[N], dfn[N], scc[N], id;
stack<int> s;
vector<int> g[N];
int n, m, cnt;

void tarjan(int u) {
    low[u] = dfn[u] = ++id;
    s.push(u);
    for (int v : g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (!scc[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        scc[u] = ++cnt;
        while (s.size()) {
            int v = s.top();
            s.pop();
            scc[v] = cnt;
            if (u == v)
                break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int k = 1; k <= m; k++) {
        int i, a, j, b;
        cin >> i >> a >> j >> b;
        // 将约束 (x_i = a) ∨ (x_j = b) 转化为蕴含关系
        // 规则：如果x_i不等于a，那么x_j必须等于b
        int u = i + (a ? n : 0); // x_i为a时的节点
        int v = j + (b ? 0 : n); // x_j为¬b时的节点
        g[u].push_back(v);       // 添加边：¬(x_i=a) → (x_j=b)
        // 另一个方向
        u = j + (b ? n : 0); // x_j为b时的节点
        v = i + (a ? 0 : n); // x_i为¬a时的节点
        g[u].push_back(v);   // 添加边：¬(x_j=b) → (x_i=a)
    }
    for (int i = 1; i <= 2 * n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }
    // 检查是否存在矛盾
    for (int i = 1; i <= n; i++) {
        if (scc[i] == scc[i + n]) {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }
    cout << "POSSIBLE" << endl;
    for (int i = 1; i <= n; i++) {
        // 如果x_i的SCC编号小于¬x_i的，则x_i为真(1)，否则为假(0)
        // 因为Tarjan的SCC编号是逆拓扑序的，编号小的在拓扑序中靠后
        cout << (scc[i] < scc[i + n]) << ' ';
    }
    return 0;
}
