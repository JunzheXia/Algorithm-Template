生成一颗树需要n-1条边相连， 生成k棵树要将n-k条边相连 
生成树可能于树上问题结合， 有时需要创建虚拟节点

//prim堆优化  o(mlogn)  稠密图
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e3 + 10;
const int INF = 0x3f3f3f3f;
vector<pair<int, int>> g[N]; 
int n, m;
bool vis[N]; 
int prim() {
    int ans = 0;
    memset(vis, false, sizeof vis); 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q; // 小根堆
    q.push({ 0, 1 }); // 从节点 1 开始，距离为 0  有时初始可能不是0
    int cnt = 0; // 记录已加入生成树的节点数
    while (!q.empty()) {
        auto [d, u] = q.top(); // 取出距离最小的节点
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        ans += d; // 累加边的权重
        cnt++; // 更新已加入生成树的节点数
        for (auto [v, w] : g[u]) { 
            if (!vis[v]) {
                q.push({ w, v }); 
            }
        }
    }
    return cnt == n ? ans : INF;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y, z; cin >> x >> y >> z;
        g[x].push_back({ y, z }); // 无向图，双向加边
        g[y].push_back({ x, z });
    }
	  int res = prim();
    if (res == INF) {
	  cout << "orz";
	  }
	  else cout << res;
    return 0;
}

// kruskal o(mlogm) 稀疏图
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e3 + 10;
const int INF = 0x3f3f3f3f;
struct edge
{
	int u, v, w;
	bool operator<(const edge& other)const {
		return w < other.w;
	}
};
int n, m;
vector<edge>g;
int fa[N];
int root(int x) {
	return fa[x] = fa[x] == x ? x : root(fa[x]);
}
void merge(int x, int y) {
	fa[root(x)] = root(y);
}
int kruskal() {
	sort(g.begin(), g.end());
	for (int i = 1; i <= n; i++) {
		fa[i] = i;
	}
	int ans = 0, cnt = 0;
	for (const auto& edge : g) {
		int u = edge.u, v = edge.v, w = edge.w;
		if (root(u) != root(v)) {
			merge(u, v);
			ans += w;
			cnt++;
			if (cnt == n - 1)break;//n - 1条边
		}
	}
	return cnt == n - 1 ? ans : INF;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y, z; cin >> x >> y >> z;
		g.push_back({ x,y,z });
	}
	int res = kruskal();
	if (res == INF) {
		cout << "orz";
	}
	else cout << res;
	return 0;
}
