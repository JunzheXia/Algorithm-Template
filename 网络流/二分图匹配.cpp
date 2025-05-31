#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e3 + 10;  // 定义最大顶点数

// 定义匹配数组，match[i]表示右侧第i个点当前匹配的左侧点
int match[N];  
// 定义访问标记数组，用于DFS中的临时标记
bool vis[N];   
// 定义邻接矩阵，mp[i][j]表示左侧第i个点和右侧第j个点是否有边
bool mp[N][N]; 
int n, m, e, ans;  // n:左侧点数量，m:右侧点数量，e:边数，ans:最大匹配数

// DFS函数，尝试为左侧点x寻找增广路
bool dfs(int x) {
    // 遍历右侧所有点
    for (int i = 1; i <= m; i++) {
        // 如果有边且右侧点i未被访问
        if (mp[x][i] && !vis[i]) {
            vis[i] = 1;  // 标记为已访问
            // 如果右侧点i未被匹配，或者能为当前匹配的左侧点找到新的匹配
            if (match[i] == 0 || dfs(match[i])) {
                match[i] = x;  // 更新匹配关系
                return true;   // 返回匹配成功
            }
        }
    }
    return false;  // 找不到增广路，返回匹配失败
}

// 匈牙利算法主函数
void Hungary() {
    // 遍历左侧所有点
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));  // 每次DFS前清空访问标记
        if (dfs(i)) ans++;  // 如果找到增广路，匹配数加1
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    // 输入左侧点数、右侧点数、边数
    cin >> n >> m >> e;
    
    // 输入边信息并构建邻接矩阵
    for (int i = 1; i <= e; i++) {
        int u, v; cin >> u >> v;
        mp[u][v] = 1;  // 无向图需要双向标记，这里是有向的二分图
    }
    
    Hungary();  // 执行匈牙利算法
    
    cout << ans;  // 输出最大匹配数
    return 0;
}
