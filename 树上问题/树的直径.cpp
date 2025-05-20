const int N = 1e5 + 10;
vector<int> g[N];
vector<int> dep(N, -1);
vector<int> pa(N);

void bfs(int s) {
    int root = 0;
    queue<int> q;
    q.push(s);
    dep[s] = 0;
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (dep[v] == -1) {
                q.push(v);
                dep[v] = dep[u] + 1;
                if (dep[v] > dep[root]) {
                    root = v;
                }
            }
        }
    }
    while (q.size())
        q.pop();
    fill(dep.begin(), dep.end(), -1);
    q.push(root);
    dep[root] = 0;
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (dep[v] == -1) {
                q.push(v);
                dep[v] = dep[u] + 1;
                pa[v] = u;
                if (dep[v] > dep[root]) {
                    root = v;
                }
            }
        }
    }
    vector<int> path;
    for (int i = root; i != 0; i = pa[i]) {
        path.push_back(i);
    }
}
///以上是BFS实现，下面是DFS实现
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 1e5 + 10;
vector<int> g[N];
vector<int> dep(N, -1);
vector<int> pa(N);
int root = 0;

void dfs(int u, int p) {
    dep[u] = dep[p] + 1;
    pa[u] = p;
    for (int v : g[u]) {
        if (dep[v] == -1) {
            dfs(v, u);
            if (dep[v] > dep[root]) {
                root = v;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    fill(dep.begin(), dep.end(), -1);
    fill(pa.begin(), pa.end(), 0);
    dfs(root, 0);
    vector<int> path;
    for (int i = root; i != 0; i = pa[i]) {
        path.push_back(i);
    }
    return 0;
}
