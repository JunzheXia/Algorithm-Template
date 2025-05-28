01背包
for (int i = 1; i <= n; i++) {
    int w, v;
    cin >> w >> v;
    for (int j = 0; j <= W; j++) {
        if (j >= w) {
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w] + v);
        } else {
            dp[i][j] = dp[i - 1][j];
        }
    }
}

第i个物品是由第i - 1个物品转移过来的,
且后续前面的状态不需要了 因此可以将二维方程压缩成一维

for (int i = 1; i <= n; i++) {
    int w, v;
    cin >> w >> v;
    for (int j = W; j >= w; j--) {
        dp[j] = max(dp[j], dp[j - w] + v);
    }
}

完全背包  无限次数
for (int i = 1; i <= n; i++) {
    int w, v;
    cin >> w >> v;
    for (int j = w; j <= W; j++) {
        dp[j] = max(dp[j], dp[j - w] + v);
    }
}

多重背包
每一个物品最多可以拿给定的s次
转化为01背包
for (int i = 1; i <= n; i++) {
    int w, v, s;
    cin >> w >> v >> s;
    while (s--) {
        for (int j = W; j >= w; j--) {
            dp[j] = max(dp[j], dp[j - w] + v);
        }
    }
}
二进制优化 O(n * W * logs)
for (int i = 1; i <= n; i++) {
    int w, v, s;
    cin >> w >> v >> s;
    for (int k = 1; k <= s; s -= k, k *= 2) {
        for (int j = W; j >= k * w; j--) {
            dp[j] = max(dp[j], dp[j - k * w] + k * v);
        }
        for (int j = W; j >= s * w; j--) {
            dp[j] = max(dp[j], dp[j - s * w] + s * v);
        }
    }
}
单调队列优化 O(n * W)
for (int i = 1; i <= n; i++) {
    int w, v, s;
    cin >> w >> v >> s;
    memcpy(g, f, sizeof(f)); // 备份上一轮的状态
    for (int j = 0; j < w; j++) { // 按同余类分组
        int hh = 0, tt = -1;
        for (int k = j; k <= W; k += w) { // 处理当前同余类
            // 维护滑动窗口大小不超过 s 个物品
            if (hh <= tt && q[hh] < k - s * w)
                hh++;
            // 单调队列维护最大值：队尾不如当前k优则弹出
            while (hh <= tt && 
                   g[q[tt]] + (k - q[tt]) / w * v <= g[k])
                tt--;
            q[++tt] = k; // 插入当前k
            // 状态转移
            if (hh <= tt)
                f[k] = max(f[k], g[q[hh]] + (k - q[hh]) / w * v);
        }
    }
}

混合背包只需要分类按上述方法讨论即可

二维背包
限制条件由一个变为两个，那么再多一维即可
for (int i = 1; i <= n; i++) {
    int v, m, w;
    cin >> v >> m >> w;
    for (int j = W; j >= w; j--) {
        for (int k = M; k >= m; k--) {
            dp[j][k] = max(dp[j][k], dp[j - w][k - m] + v);
        }
    }
}

分组背包
每组物品有若干个，同一组的物品最多选一个
for (int i = 1; i <= n; i++) {
    int s;
    cin >> s;
    vector<pair<int, int>> a;
    while (s--) {
        int w, v;
        cin >> w >> v;
        a.emplace_back(w, v);
    }
    for (int j = W; j >= 0; j--) {
        for (auto [w, v] : a) {
            if (j >= w) {
                dp[j] = max(dp[j], dp[j - w] + v);
            }
        }
    }
}

树上背包  O(n * w ^ 2) w是每个点要枚举的容量
每个点依赖其父亲， 只有父亲购买，才可以购买该点
#include<bits/stdc++.h>

using namespace std;
const int N = 1e2 + 10;
int f[N][N]， w[N]， v[N];//f[u][j]表示以u为根的子树，容量j时的最大价值
vector<int>g[N];
int n, W;

void dfs(int u) {
    for (int i = w[u]; i <= W; i++) {
        f[u][i] = v[u];
    }
    for (auto v : g[u]) {
        dfs(v);
        //分组背包，倒叙枚举容量
        for (int i = W; i >= w[u]; i--) {
            //枚举分配给子树的容量，至少留w[u]给u
            for (int j = 0; j <= i - w[u]; j++) {
                f[u][i] = max(f[u][i], f[u][i - j] + f[v][j]);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> W;
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> w[i] >> v[i] >> p;
        g[p].push_back(i);
    }
    dfs(0);
    cout << f[0][W];
}

背包问题求方案数
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int MOD = 1e9 + 7, N = 1010;
i64 n, W, cnt[N], f[N], w, v;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> W;
    for (int i = 0; i <= W; i++) {
        cnt[i] = 1;//不装任何东西就是一种方案
    }
    for (int i = 1; i <= n; i++) {
        cin >> w >> v;
        for (int j = W; j >= w; j--) {
            if (f[j] < f[j - w] + v) {
                f[j] = f[j - w] + v;
                cnt[j] = cnt[j - w];
            } else if (f[j] == f[j - w] + v) {
                cnt[j] = (cnt[j] + cnt[j - w]) % MOD;
            }
        }
    }
    cout << cnt[W];
    return 0;
}
