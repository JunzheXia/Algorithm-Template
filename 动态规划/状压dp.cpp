在 N×N 的棋盘上放置K 个国王，要求它们互不攻击（即任意两个国王不能相邻，包括上下左右和四个对角线方向）。求合法的摆放方案数。


#include <bits/stdc++.h>
#define int long long

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

int cnt[1 << 10], ok[1 << 10];
// cnt表示第i种状态的国王数量， ok表示第i种合法状态
int dp[10][1 << 10][1 << 10];
// dp[i][j][k] 表示：
//   - 前i行已经处理完
//   - 第i行采用了第j种合法状态（ok[j]）
//   - 已经放置了k个国王
//   时的方案数

// 棋盘大小  国王数量  合法状态数
int n, k, tot;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 0; i < (1 << n); i++) { // 枚举所有可能的状态
        if (!(i & (i << 1))) {           // 检查是否有相邻的1，即是否是合法状态
            ok[tot] = i;
            cnt[tot] = __builtin_popcount(i); // 计算该状态国王的数量
            tot++;
        }
    }

    // 初始化
    for (int i = 0; i < tot; i++) { // 遍历所有合法状态
        if (cnt[i] <= k) {          // 超过k说明不合法
            dp[0][i][cnt[i]] = 1;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < tot; j++) {     // 枚举当前行状态
            for (int u = 0; u < tot; u++) { // 枚举上一行状态
                // 检查两行状态是否冲突：
                // 1. 正上方不能有国王（ok[j] & ok[u]）
                // 2. 左上方不能有国王（ok[j] & (ok[u] << 1)）
                // 3. 右上方不能有国王（ok[j] & (ok[u] >> 1)）
                if ((ok[u] | (ok[u] << 1) | (ok[u] >> 1)) & ok[j]) {
                    continue; // 冲突则跳过
                }
                // 枚举以及放置的国王数m
                for (int m = 0; m + cnt[j] <= k; m++) {
                    // 状态转移：
                    // 当前行采用状态j，新增cnt[j]个国王
                    // 方案数累加上一行采用状态u、放置m个国王的方案数
                    dp[i][j][m + cnt[j]] += dp[i - 1][u][m];
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < tot; i++) {//统计答案
        ans += dp[n - 1][i][k];
    }
    cout << ans << endl;

    return 0;
}
