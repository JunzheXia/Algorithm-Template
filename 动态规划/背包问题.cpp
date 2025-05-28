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
