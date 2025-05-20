//Dijkstra实现 复杂度mlogn  但是Dijkstra只能在正权边时用
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int INF = 1e9;
const int N = 2e5 + 10;
vector<pair<int, int>> g[N];
vector<int> dis(N, INF);
vector<bool> vis(N);
int n, m, s;

void Dijkstra() {
    dis[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>q;
    q.push({0, s});
    while (q.size()) {
        auto [w, u] = q.top();
        q.pop();
        if (vis[u])
            continue;
        vis[u] = 1;
        for (auto [v, w] : g[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push({dis[v], v});
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
    }
    Dijkstra();
    for (int i = 1; i <= n; i++) {
        cout << dis[i] << ' ';
    }
    return 0;
}
//SPFA  时间复杂度一般m，最多mn  SPFA可以用在负权图上
//SPFA容易超时
//此外SPFA可以求是否存在负环
//cnt[u]记录从起点到u经过的边数，如果不存在负环那么最短结果n - 1条边，如果 >= n 那么就是存再负环
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int INF = 1e9;
const int N = 1e5 + 10;
int n, m, s;
vector<pair<int, int>> g[N];
vector<int> dis(N, INF), cnt(N);
vector<bool> vis(N);

void spfa() {
    queue<int> q;
    dis[s] = 0, vis[s] = 1, q.push(s);
    while (q.size()) {
        int u = q.front();
        vis[u] = 0, q.pop();
        for (auto [v, w] : g[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if(cnt[v] >= n){
                    return;
                }//加上这一句检测负环
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
    }
    spfa();
    for (int i = 1; i <= n; i++) {
        cout << dis[i] << ' ';
    }
    return 0;
}
