存在问题，等待修改( cf2192E

有向图

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 1e5 + 10;
vector<int> g[N];
int n, m, sc, ec;
int in[N], out[N];
bool pd = 1;
vector<int> path;

void dfs(int u) {
    while (!g[u].empty()) {
        int v = g[u].back();
        g[u].pop_back();
        dfs(v);
    }
    path.push_back(u);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        out[u]++, in[v]++;
    }
    int s = 1;
    for (int i = 1; i <= n; i++) {
        if (out[i] == in[i])
            continue;
        pd = 0;
        if (out[i] - in[i] == 1) {
            s = i;
            sc++;
        }
        else if (in[i] - out[i] == 1) {
            ec++;
        }
        else if (in[i] != out[i]) {
            cout << "No\n";
            return 0;
        }
    }
    if (!pd && !(sc == ec && sc == 1)) {
        cout << "No\n";
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        sort(g[i].begin(), g[i].end(), greater<int>());
    }
    // 欧拉路径情况
    if (sc == 0 && ec == 0) {
        for (int i = 1; i <= n; i++) {
            if (out[i] > 0) {
                s = i;
                break;
            }
        }
    }
    dfs(s);
    reverse(path.begin(), path.end());
    for (int u : path) {
        cout << u << ' ';
    }
    cout << '\n';

    return 0;
}


无向图
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 510;
int m;
vector<int> g[N];
int deg[N];
vector<int> path;

void dfs(int u) {
    while (g[u].size()) {
        int v = g[u].back();
        g[u].pop_back();
        for (auto it = g[v].begin(); it != g[v].end(); it++) {
            if (*it == u) {
                g[v].erase(it);
                break;
            }
        }
        dfs(v);
    }
    path.push_back(u);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        deg[v]++;
        deg[u]++;
    }
    int s = 0, cnt = 0;
    for (int i = 1; i <= N; i++) {
        if (deg[i] & 1) {
            cnt++;
            if (!s) {
                s = i;
            }
        }
    }
    if (!s) {
        for (int i = 1; i <= N; i++) {
            if (deg[i]) {
                s = i;
                break;
            }
        }
    }
    for (int i = 1; i < N; i++) {
        sort(g[i].begin(), g[i].end(), greater<int>());
    }
    dfs(s);
    reverse(path.begin(), path.end());
    for (int v : path) {
        cout << v << '\n';
    }
    return 0;
}
