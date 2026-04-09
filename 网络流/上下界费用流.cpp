注意加上强制流的费用

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 1e3;
const int INF = 1e9;

struct Edge {
    int to, rev;
    int cap, cost;
};

int n, s, t;
vector<Edge> g[N];
int dis[N], cur[N], d[N];
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    s = 0, t = n + 2;

    for (int i = 1; i <= n; i++) {
        int k, u, w;
        cin >> k;
        while (k--) {
            cin >> u >> w;
            d[i]--, d[u]++;
            mncost += w;
            addedge(i, u, INF, w);
        }
    }

    for (int i = 2; i <= n; i++) {
        addedge(i, n + 1, INF, 0);
    }
    addedge(n + 1, 1, INF, 0);

    for (int i = 1; i <= n; i++) {
        if (d[i] > 0) {
            addedge(0, i, d[i], 0);
        } else if (d[i] < 0) {
            addedge(i, n + 2, -d[i], 0);
        }
    }

    dinic();

    cout << mncost << '\n';

    return 0;
}
