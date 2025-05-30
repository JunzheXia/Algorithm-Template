石子合并  O(n ^ 3)

int n; cin >> n;
memset(dp, 0x3f, sizeof(dp));  
for (int i = 1; i <= n; i++) {
    cin >> a[i];
     pre[i] = pre[i - 1] + a[i];
     dp[i][i] = 0; 
}

for (int len = 2; len <= n; len++) { //枚举区间长度
    for (int i = 1; i <= n - len + 1; i++) {//枚举起点
        int j = i + len - 1; 
        for (int k = i; k < j; k++) { //枚举分割点
            dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + pre[j] - pre[i - 1]);
        }
     }
 }
 cout << dp[1][n];

如果是环形的情况，可以破环成链
环形石子合并

#include <bits/stdc++.h>
using namespace std;
const int N = 410; // 2倍空间
int dp_min[N][N], dp_max[N][N], sum[N], a[N];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i + n] = a[i]; // 破环成链
    }
    // 预处理前缀和
    for (int i = 1; i <= 2 * n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }
    // 初始化DP
    memset(dp_min, 0x3f, sizeof(dp_min));
    memset(dp_max, 0, sizeof(dp_max));
    for (int i = 1; i <= 2 * n; i++) dp_min[i][i] = dp_max[i][i] = 0;
    // 区间DP
    for (int len = 2; len <= n; len++) {          // 枚举区间长度（最大为n）
        for (int i = 1; i + len - 1 <= 2 * n; i++) { // 枚举起点
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                dp_min[i][j] = min(dp_min[i][j], dp_min[i][k] + dp_min[k + 1][j] + sum[j] - sum[i - 1]);
                dp_max[i][j] = max(dp_max[i][j], dp_max[i][k] + dp_max[k + 1][j] + sum[j] - sum[i - 1]);
            }
        }
    }
    // 在所有长度为n的区间中找最优解
    int ans_min = 1e9, ans_max = 0;
    for (int i = 1; i <= n; i++) {
        ans_min = min(ans_min, dp_min[i][i + n - 1]);
        ans_max = max(ans_max, dp_max[i][i + n - 1]);
    }
    cout << ans_min << endl << ans_max << endl;
    return 0;
}

四边形不等式优化
最小代价满足四边形不等式， 时间复杂度为O(n ^ 2)
最大代价不满足四边形不等式，时间复杂度为O(n ^ 3)

#include <bits/stdc++.h>
using namespace std;
const int N = 410; // 2倍空间
int dp_min[N][N], dp_max[N][N], s[N][N], sum[N], a[N];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i + n] = a[i]; // 破环成链
    }
    // 前缀和
    for (int i = 1; i <= 2 * n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }
    // 初始化
    memset(dp_min, 0x3f, sizeof(dp_min));
    memset(dp_max, 0, sizeof(dp_max));
    for (int i = 1; i <= 2 * n; i++) {
        dp_min[i][i] = dp_max[i][i] = 0;
        s[i][i] = i; // 初始最优分割点是自身
    }
    // 区间DP + 四边形不等式优化
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= 2 * n; i++) {
            int j = i + len - 1;
            // 优化：k的枚举范围 [s[i][j-1], s[i+1][j]]
            int start_k = s[i][j-1], end_k = (i+1 <= j) ? s[i+1][j] : j-1;
            for (int k = start_k; k <= end_k; k++) {
                int cost = dp_min[i][k] + dp_min[k+1][j] + sum[j] - sum[i-1];
                if (cost < dp_min[i][j]) {
                    dp_min[i][j] = cost;
                    s[i][j] = k; // 更新最优分割点
                }
            }
            // 最大代价（通常不满足四边形不等式，仍需暴力枚举）
            for (int k = i; k < j; k++) {
                dp_max[i][j] = max(dp_max[i][j], dp_max[i][k] + dp_max[k+1][j] + sum[j] - sum[i-1]);
            }
        }
    }
    // 在所有长度为n的区间中找最优解
    int ans_min = 1e9, ans_max = 0;
    for (int i = 1; i <= n; i++) {
        ans_min = min(ans_min, dp_min[i][i + n - 1]);
        ans_max = max(ans_max, dp_max[i][i + n - 1]);
    }
    cout << ans_min << endl << ans_max << endl;
    return 0;
}
