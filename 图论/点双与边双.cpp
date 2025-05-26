一个无向图的点双连通分量是指图中没有割点的极大子图。也就是说，在点双中任意两点至少存在两条不重复路径（即没有割点）。
删除任何一点后自如任然连通。落单点也是点双。两点一边或者多边也属于点双。
点双连通之间通过割点连接， 两个点双之间共享一个割点，点双可以是边、环或更复杂的结构。
一下代码输出每个顶点u属于多少个点双。

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 1e5 + 10;
vector<int> g[N];
int low[N], dfn[N], id;
int n, m, cnt[N];
stack<int> s;
vector<vector<int>> bccs;

void tarjan(int u, int p) {
    low[u] = dfn[u] = ++id;
    s.push(u);
    for (int v : g[u]) {
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {//发现割点或BCC
                vector<int> bcc;
                while (s.size()) {
                    int x = s.top();
                    s.pop();
                    bcc.push_back(x);
                    if (x == v)
                        break;
                    bcc.push_back(u);//u是割点属于当前BCC
                    bccs.push_back(bcc);
                }
            }
        } else if (v != p) {
            low[u] = min(low[u], dfn[v]);
        }
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
            tarjan(i, -1);
        }
    }
    for (auto bcc : bccs) {
        for (int u : bcc) {
            cnt[u]++;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << cnt[i] << endl;
    }
    return 0;
}

边双是指删除任意一条边后，子图任然连通。
边双之间用割边连接，一个点可以属于且仅属于一个边双，边双内部任意两点至少存在两条边不相交的路径。
注意代码中的N要开大一点。
图中可能存在自环或者重边。
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 1e6 + 10;
int n, m;
int low[N], dfn[N], id;
vector<pair<int, int>> g[N];
vector<vector<int>> ebccs;
stack<int> s;

void tarjan(int u, int p) {
    low[u] = dfn[u] = ++id;
    s.push(u);
    for (auto [v, w] : g[u]) {
        if (w == (p ^ 1))//避免走父边
            continue;
        if (!dfn[v]) {
            tarjan(v, w);
            low[u] = min(low[u], low[v]);
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {//找到一个边双
        vector<int> ebcc;
        while (s.size()) {
            int x = s.top();
            s.pop();
            ebcc.push_back(x);
            if (x == u)
                break;
        }
        ebccs.push_back(ebcc);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v, 2 * i);//边的编号为2 * i
        g[v].emplace_back(u， 2 * i + 1);//反向边的编号为2 * i + 1
        //主要用于防止走父边
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            tarjan(i, -1);
    }
    cout << ebccs.size() << endl;
    for (auto ebcc : ebccs) {
        cout << ebcc.size() << ' ';
        for (auto v : ebcc) {
            cout << v << ' ';
        }
        cout << endl;
    }
    return 0;
}
