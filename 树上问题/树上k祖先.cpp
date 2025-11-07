// 长链剖分
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

const int N = 5e5 + 10;

int n, q, root, cnt;
vector<int> g[N];
int dep[N], fa[N][21], son[N], top[N], h[N];
int U[N], D[N], id[N], Log[N];
u32 s;

u32 get() {
    s ^= s << 13;
    s ^= s >> 17;
    s ^= s << 5;
    return s;
}

void dfs1(int u) {
    for (int i = 1; i <= 20; i++) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for (int v : g[u]) {
        dep[v] = h[v] = dep[u] + 1;
        dfs1(v);
        if (h[v] > h[u]) {
            h[u] = h[v];
            son[u] = v;
        }
    }
}

void dfs2(int u, int p) {
    id[u] = ++cnt;
    D[cnt] = u;
    U[cnt] = p;

    if (son[u]) {
        top[son[u]] = top[u];
        dfs2(son[u], fa[p][0]);
    }
    for (int v : g[u]) {
        if (v == son[u])
            continue;
        top[v] = v;
        dfs2(v, v);
    }
}

int ka(int u, int k) {
    if (!k)
        return u;
    u = fa[u][Log[k]];
    k -= (1 << Log[k]);
    k -= dep[u] - dep[top[u]];
    u = top[u];
    if (k >= 0)
        return U[id[u] + k];
    return D[id[u] - k];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Log[0] = -1;
    for (int i = 1; i < N; i++) {
        Log[i] = Log[i >> 1] + 1;
    }

    cin >> n >> q >> s;
    for (int i = 1; i <= n; i++) {
        int u;
        cin >> u;
        fa[i][0] = u;
        if (u == 0) {
            root = i;
        } else {
            g[u].push_back(i);
        }
    }

    dep[root] = 1;
    dfs1(root);
    top[root] = root;
    dfs2(root, root);

    i64 ans = 0, last = 0;
    for (int i = 1; i <= q; i++) {
        int x = (get() ^ last) % n + 1;
        int k = (get() ^ last) % dep[x];
        last = ka(x, k);
        ans ^= i * 1LL * last;
    }
    cout << ans;

    return 0;
}
