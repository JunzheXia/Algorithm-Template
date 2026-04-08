#include <bits/stdc++.h>
#define int long long

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 5e3 + 10;
const int M = 5e4 + 10;
const int INF = 1e18;

struct Edge {
    int to, rev;
    int cap, cost;
};

int n, m, s, t;
vector<Edge> g[N];
int dis[N], cur[N];
bool vis[N];
int mxflow, mncost;

void addedge(int u, int v, int cap, int cost) {
    g[u].push_back({v, (int)g[v].size(), cap, cost});
    g[v].push_back({u, (int)g[u].size() - 1, 0, -cost});
}

bool spfa() {
    for (int i = s; i <= t; i++) { 
        dis[i] = INF;
        vis[i] = 0;
        cur[i] = 0;
    }
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    vis[s] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (auto &e : g[u]) {
            int v = e.to;
            if (e.cap > 0 && dis[v] > dis[u] + e.cost) {
                dis[v] = dis[u] + e.cost;
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }

    return dis[t] != INF;
}

int dfs(int u, int flow) {
    if (u == t) {
        return flow;
    }
    vis[u] = 1;
    int used = 0;
    for (int &i = cur[u]; i < (int)g[u].size(); i++) {
        auto &e = g[u][i];
        int v = e.to;
        if (!vis[v] && e.cap > 0 && dis[v] == dis[u] + e.cost) {
            int f = dfs(v, min(flow - used, e.cap));
            if (f) {
                mncost += f * e.cost;
                e.cap -= f;
                g[v][e.rev].cap += f;
                used += f;
                if (used == flow) {
                    break;
                }
            }
        }
    }
    vis[u] = 0;
    return used;
}

void dinic() {
    while (spfa()) {
        memset(vis, 0, sizeof(vis));
        int f = dfs(s, INF);
        mxflow += f;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s >> t;

    for (int i = 1; i <= m; i++) {
        int u, v, cap, cost;
        cin >> u >> v >> cap >> cost;
        addedge(u, v, cap, cost);
    }
    dinic();

    cout << mxflow << ' ' << mncost << '\n';

    return 0;
}
