//Flord  要注意题目是有向图还是无向图，也可以构建分层图

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int INF = 1e9;
const int N = 110;
const int M = 1e5 + 10;
int n, m;
vector<vector<int>> dis(N, vector<int>(N));
vector<int> a(M);
i64 ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> dis[i][j];
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    for (int i = 1; i < m; i++) {
        ans += dis[a[i]][a[i + 1]];
    }
    cout << ans;
    return 0;
}
