#include<bits/stdc++.h>
#define int long long  // 使用 long long 类型
using namespace std;
const int N = 205;     // 最大顶点数
const int INF = 1e18;  // 定义无穷大

// 边的结构体，表示一条有向边
struct Edge {
    int to;     // 边的终点
    int cap;    // 边的容量
    int rev;    // 反向边在邻接表里的位置
};

vector<Edge> g[N];  // 邻接表存储图
int level[N];       // 用于BFS计算层次图
int iter[N];        // 当前弧优化，记录当前遍历到的边

// BFS计算层次图（分层）
void bfs(int s) {
    // 重置层级为-1（表示未访问）
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;  // 源点层级设为0
    q.push(s);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        // 遍历u的所有邻边
        for (auto& e : g[u]) {
            // 如果边有剩余容量且终点未被访问
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[u] + 1;  // 更新层级
                q.push(e.to);               // 加入队列
            }
        }
    }
}

// DFS寻找增广路（计算阻塞流）
int dfs(int u, int t, int f) {
    if (u == t) return f;  // 到达汇点，返回流量

    // 使用当前弧优化（避免重复检查已经处理过的边）
    for (int& i = iter[u]; i < g[u].size(); i++) {
        auto& e = g[u][i];
        // 如果边有剩余容量且满足层级关系（只能从低层级流向高层级）
        if (e.cap > 0 && level[u] < level[e.to]) {
            int d = dfs(e.to, t, min(f, e.cap));  // 递归计算可增广的流量
            if (d > 0) {
                e.cap -= d;                     // 更新正向边容量
                g[e.to][e.rev].cap += d;        // 更新反向边容量
                return d;                       // 返回增广的流量
            }
        }
    }
    return 0;  // 无法增广，返回0
}

// Dinic算法计算最大流
int max_flow(int s, int t) {
    int flow = 0;  // 初始化总流量为0
    while (true) {
        bfs(s);  // 构建层次图
        if (level[t] < 0) break;  // 如果汇点不可达，退出循环

        // 重置当前弧
        memset(iter, 0, sizeof(iter));
        int f;
        // 计算阻塞流并累加
        while ((f = dfs(s, t, INF)) > 0) {
            flow += f;
        }
    }
    return flow;  // 返回最大流
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, t;
    cin >> n >> m >> s >> t;  // 输入顶点数、边数、源点、汇点

    // 建图
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        // 添加正向边（容量w）和反向边（容量0）
        g[u].push_back({v, w, (int)g[v].size()});
        g[v].push_back({u, 0, (int)g[u].size() - 1});
    }

    cout << max_flow(s, t) << endl;  // 输出最大流
    return 0;
}

这是一道顶点割的网络流，传统网络流只能处理边割，对于顶点割问题，
要将其进行顶点分裂转化为边割问题。
将每个点分为出点和入点。如果出点和入点之间的边权为无穷大，就说明该点无法被删除
对于原图，给出的两个点，我们将其形成的两个边首尾相连，形成类似于环

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 210;
const int INF = 0x3f3f3f3f;
struct edge {
    int v, cap, rev;
};
int n, m;
int s, t;
vector<edge> g[N];
int level[N], iter[N];

bool bfs() {
    fill(level, level + 2 * n + 1, -1);
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (auto& e : g[u]) {
            if (e.cap > 0 && level[e.v] < 0) {
                level[e.v] = level[u] + 1;
                q.push(e.v);
            }
        }
    }
    return level[t] != -1;
}

int dfs(int u, int flow) {
    if (u == t)
        return flow;
    for (int& i = iter[u]; i < g[u].size(); i++) {
        auto& e = g[u][i];
        if (e.cap > 0 && level[u] < level[e.v]) {
            int d = dfs(e.v, min(flow, e.cap));
            if (d > 0) {
                e.cap -= d;
                g[e.v][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int Dinic() {
    int maxflow = 0;
    while (bfs()) {
        fill(iter, iter + 2 * n + 1, 0);
        int f;
        while ((f = dfs(s, INF)) > 0) {
            maxflow += f;
        }
    }
    return maxflow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s >> t;
    for (int i = 1; i <= n; i++) {
        if (i == s || i == t) {
            g[i].emplace_back(i + n, INF, (int)g[i + n].size());
            g[i + n].emplace_back(i, 0, (int)g[i].size() - 1);
        }
        else {
            g[i].emplace_back(i + n, 1, (int)g[i + n].size());
            g[i + n].emplace_back(i, 0, (int)g[i].size() - 1);
        }
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u + n].emplace_back(v, INF, (int)g[v].size());
        g[v + n].emplace_back(u, INF, (int)g[u].size());
        g[u].emplace_back(v + n, 0, (int)g[v + n].size() - 1);
        g[v].emplace_back(u + n, 0, (int)g[u + n].size() - 1);
    }
    cout << Dinic();
    return 0;
}
