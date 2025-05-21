//  询问是否有等于k的路径   k较小时可以用桶优化   答案离线处理
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define INF 0x3f3f3f3f
using ll = long long;
const int N = 1e4 + 10;
const int NK = 1e7 + 10;
int n, m, root, sum;
int siz[N], maxv[N];
bool vis[N], ans[N], cnt[NK];
vector<pair<int, int>> g[N];
vector<int> dis, q;
void getroot(int u, int f) {
    maxv[u] = 0, siz[u] = 1;
    for (const auto &[v, w] : g[u]) {
        if (vis[v] || v == f)
            continue;
        getroot(v, u);
        siz[u] += siz[v];
        maxv[u] = max(maxv[u], siz[v]);
    }
    maxv[u] = max(maxv[u], sum - siz[u]);
    if (maxv[u] < maxv[root])
        root = u;
}
void getdis(int u, int f, int d) {
    if (d > NK)
        return;
    dis.push_back(d);
    for (const auto &[v, w] : g[u]) {
        if (vis[v] || v == f)
            continue;
        getdis(v, u, d + w);
    }
}
void calc(int u) {
    vector<int> tot;
    cnt[0] = 1;
    for (const auto &[v, w] : g[u]) {
        if (vis[v])
            continue;
        dis.clear();
        getdis(v, u, w);
        for (int i = 0; i < m; i++) {
            if (ans[i])
                continue;
            for (int d : dis) {
                if (d > q[i])
                    continue;
                if (cnt[q[i] - d]) {
                    ans[i] = 1;
                    break;
                }
            }
        }
        for (int d : dis) {
            if (d > NK)
                continue;
            if (!cnt[d]) {
                cnt[d] = 1;
                tot.push_back(d);
            }
        }
    }
    for (auto d : tot) {
        cnt[d] = 0;
    }
}
void work(int u) {
    vis[u] = 1;
    calc(u);
    for (const auto &[v, w] : g[u]) {
        if (vis[v])
            continue;
        sum = siz[v];
        root = 0, maxv[root] = INF;
        getroot(v, 0);
        work(root);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    q.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> q[i];
    }
    sum = n;
    root = 0, maxv[root] = INF;
    getroot(1, 0);
    work(root);
    for (int i = 0; i < m; i++) {
        cout << (ans[i] ? "AYE" : "NAY") << endl;
    }
    return 0;
}

//利用容斥原理求
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define INF 0x3f3f3f3f
using ll = long long;
const int N = 2e4 + 10;
int n, root, sum;
ll ans;
vector<pair<int, int>> g[N];
int maxv[N], siz[N];
vector<int> dis;
bool vis[N];
int cnt[3];
void getroot(int u, int f) {
    siz[u] = 1, maxv[u] = 0;
    for (const auto& [v, w] : g[u]) {
        if (vis[v] || v == f)
            continue;
        getroot(v, u);
        siz[u] += siz[v];
        maxv[u] = max(maxv[u], siz[v]);
    }
    maxv[u] = max(maxv[u], sum - siz[u]);
    if (maxv[u] < maxv[root]) {
        root = u;
    }
}

void getdis(int u, int f, int d) {
    dis.push_back(d);
    for (const auto& [v, w] : g[u]) {
        if (vis[v] || v == f)
            continue;
        getdis(v, u, d + w);
    }
}

ll calc(int u, int d) {
    dis.clear();
    getdis(u, 0, d);
    memset(cnt, 0, sizeof(cnt));
    for (int x : dis) {
        cnt[x % 3]++;
    }
    return 1LL * cnt[0] * cnt[0] + 2LL * cnt[1] * cnt[2];
}

void solve(int u) {
    vis[u] = 1;
    ans += calc(u, 0);
    for (const auto& [v, w] : g[u]) {
        if (vis[v])
            continue;
        ans -= calc(v, w);
        sum = siz[v];
        root = 0, maxv[0] = INF;
        getroot(v, u);
        solve(root);
    }
}

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    sum = n;
    root = 0, maxv[0] = INF;
    getroot(1, 0);
    solve(root);
    ll tot = 1LL * n * n;
    ll t = gcd(ans, tot);
    cout << ans / t << "/" << tot / t << endl;
    return 0;
}

//  该算法的一般变化主要在dis和calc函数上，根据需要修改即可
int calc(int u, int d) {
	dis.clear();
	getdis(u, 0, 0);
	sort(dis.begin(), dis.end());
	int res = 0;
	for (int l = 0, r = dis.size() - 1; l < r;) {//双指针计算答案
		if (dis[l] + dis[r] < k) {
			res += r - l;
			l++;
		}
		else r--;
	}
	return res;
}
