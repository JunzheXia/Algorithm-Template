树的重心定义：如果在树中选择某个节点并删除，这棵树将分为若干棵子树，统计子树节点数并记录最大值。
取遍树上所有节点，使此最大值取到最小的节点被称为整个树的重心。
1、树中所有的点到某一点的距离和中，到重心的距离和是最小的，如有两个重心，则这两距离相等，这是最重要的性质。下面的例题将用到本性质。

2、树的重心可能不唯一，但至多有两个重心。如若一颗树有两个重心，则这两个重心相邻。

3、以树的重心为根时，所有子树的大小都不超过树的大小的一半。

4、两棵树相连得到一颗新的树，这棵树的重心在原来两棵树的重心之间的简单路径上。

5、在一颗树上添加或删除一个节点，重心最多移动一条边的距离。

//这是无权的实现，如果有点权sum[u]赋值为点权，cnt记录权重和即可，点权可以看作该点连了子节点。
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 120;
const int INF = 1e9;

int n;
vector<int> g[N];
vector<int> sum(N), maxv(N);

void dfs(int u, int p) {
    int mx = 0;
    sum[u] = 1;
    for (const auto &v : g[u]) {
        if (v == p)
            continue;
        dfs(v, u);
        sum[u] += sum[v];
        if (sum[v] > mx)
            mx = sum[v];
    }
    if (n - sum[u] > mx)
        mx = n - sum[u];
    maxv[u] = mx;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    int id = 0, ans = n;
    for (int i = 1; i <= n; i++) {
        if (maxv[i] < ans) {
            ans = maxv[i];
            id = i;
        }
    }
    cout << id << ' ' << ans;
    return 0;
}
