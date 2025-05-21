//两点的简单路径修改， 简单路径查询 ， 子树修改， 子树查询

#include <bits/stdc++.h>
#define int long long

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 1e5 + 10;
int n, m, s, M;
vector<int> g[N];
int a[N], dep[N], son[N], siz[N];
int cnt, id[N], w[N], top[N], fa[N];
struct node {
    int l, r, sum, lz;
} tr[N << 2];

void dfs1(int u, int p) {
    dep[u] = dep[p] + 1;
    fa[u] = p;
    siz[u] = 1;
    int mx = -1; // 找重儿子
    for (auto v : g[u]) {
        if (v == p)
            continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > mx) {
            son[u] = v, mx = siz[v];
        }
    }
}
//dfs1处理了树的深度，子树大小，轻儿子，重儿子
void dfs2(int u, int tp) {
    id[u] = ++cnt;//记录dfs序
    w[cnt] = a[u];//记录权值
    top[u] = tp;//记录链顶
    if (!son[u])//没有重儿子（叶子节点）
        return;
    dfs2(son[u], tp);
    for (auto v : g[u]) {
        if (v == fa[u] || v == son[u])//跳过父节点和重儿子
            continue;
        dfs2(v, v);//轻儿子作为新链顶点
    }
}

void push_up(int ind) { tr[ind].sum = tr[ind << 1].sum + tr[ind << 1 | 1].sum; }

void build(int ind, int l, int r) {
    tr[ind].l = l, tr[ind].r = r;
    if (l == r) {
        tr[ind].sum = w[l];
        return;
    }
    int mid = l + r >> 1;
    build(ind << 1, l, mid);
    build(ind << 1 | 1, mid + 1, r);
    push_up(ind);
}

void push_down(int ind) {
    if (tr[ind].lz) {
        tr[ind << 1].sum += tr[ind].lz * (tr[ind << 1].r - tr[ind << 1].l + 1);
        tr[ind << 1 | 1].sum +=
            tr[ind].lz * (tr[ind << 1 | 1].r - tr[ind << 1 | 1].l + 1);
        tr[ind << 1].lz += tr[ind].lz;
        tr[ind << 1 | 1].lz += tr[ind].lz;
        tr[ind].lz = 0;
    }
}

void modify(int ind, int l, int r, int k) {
    if (tr[ind].l >= l && tr[ind].r <= r) {
        tr[ind].sum += k * (tr[ind].r - tr[ind].l + 1);
        tr[ind].lz += k;
        return;
    }
    push_down(ind);
    int mid = (tr[ind].l + tr[ind].r) >> 1;
    if (l <= mid)
        modify(ind << 1, l, r, k);
    if (r > mid)
        modify(ind << 1 | 1, l, r, k);
    push_up(ind);
}

int query(int ind, int l, int r) {
    if (tr[ind].l >= l && tr[ind].r <= r) {
        return tr[ind].sum;
    }
    if (tr[ind].l > r || tr[ind].r < l) {
        return 0;
    }
    push_down(ind);
    int res = 0;
    int mid = (tr[ind].l + tr[ind].r) >> 1;
    if (l <= mid) {
        res += query(ind << 1, l, r);
    }
    if (r > mid) {
        res += query(ind << 1 | 1, l, r);
    }
    return res;
}
//结合图国过程更清晰
void update(int u, int v, int k) {
    while (top[u] != top[v]) {//不在同一条重链上，那就先处理深度大的链
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        modify(1, id[top[u]], id[u], k);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v])
        swap(u, v);
    modify(1, id[v], id[u], k);
}
//过程几乎同上
int get(int u, int v) {
    int res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(v, u);
        res += query(1, id[top[u]], id[u]);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v])
        swap(u, v);
    res += query(1, id[v], id[u]);
    return res;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s >> M;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(s, 0);
    dfs2(s, s);
    build(1, 1, n);
    while (m--) {
        int op, x, y, z;
        cin >> op;
        if (op == 1) {
            cin >> x >> y >> z;
            update(x, y, z);
        }
        if (op == 2) {
            cin >> x >> y;
            cout << get(x, y) % M << "\n";
        }
        if (op == 3) {
            cin >> x >> z;
            modify(1, id[x], id[x] + siz[x] - 1, z);
        }
        if (op == 4) {
            cin >> x;
            cout << query(1, id[x], id[x] + siz[x] - 1) % M << "\n";
        }
    }
    return 0;
}
