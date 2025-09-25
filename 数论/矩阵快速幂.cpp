矩阵乘法o(n^3) 快速幂 logk


#include <bits/stdc++.h>
#define int long long

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int MOD = 1e9 + 7;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    auto multiply = [&](vector<vector<int>> a,
                        vector<vector<int>> b) -> vector<vector<int>> {
        vector<vector<int>> c(n + 1, vector<int>(n + 1));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= n; k++) {
                    c[i][j] = (c[i][j] + a[i][k] * b[k][j] % MOD) % MOD;
                }
            }
        }
        return c;
    };

    auto matrixpow = [&](vector<vector<int>> a, int k) -> vector<vector<int>> {
        vector<vector<int>> res(n + 1, vector<int>(n + 1));
        for (int i = 1; i <= n; i++) {
            res[i][i] = 1;
        }
        while (k) {
            if (k & 1) {
                res = multiply(res, a);
            }
            a = multiply(a, a);
            k >>= 1;
        }
        return res;
    };

    vector<vector<int>> ans = matrixpow(a, k);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}
