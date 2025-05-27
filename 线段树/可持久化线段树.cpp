单点修改和查询
更新一个节点时，只有从根到该叶子节点路径上的节点会被复制和修改。

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 5e5 + 10;
int n, m;
int a[N];
struct node {
    i64 l, r, sum;
} tr[N * 40];
int cnt, root[N];

void push_up(int ind) { tr[ind].sum = tr[tr[ind].l].sum + tr[tr[ind].r].sum; }

i64 build(int l, int r) {
    int ind = ++cnt;
    if (l == r) {
        tr[ind].sum = a[l];
        return ind;
    }
    int mid = (l + r) >> 1;
    tr[ind].l = build(l, mid);
    tr[ind].r = build(mid + 1, r);
    push_up(ind);
    return ind;
}

i64 modify(int pre, int l, int r, int x, int v) {
    int ind = ++cnt;
    tr[ind] = tr[pre];
    if (l == r) {
        tr[ind].sum = v;
        return ind;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) {
        tr[ind].l = modify(tr[pre].l, l, mid, x, v);
    } else {
        tr[ind].r = modify(tr[pre].r, mid + 1, r, x, v);
    }
    push_up(ind);
    return ind;
}

i64 query(int ind, int l, int r, int ql, int qr) {
    if (l >= ql && r <= qr) {
        return tr[ind].sum;
    }
    if (r < ql || l > qr) {
        return 0;
    }
    int mid = (l + r) >> 1;
    return query(tr[ind].l, l, mid, ql, qr) +
           query(tr[ind].r, mid + 1, r, ql, qr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    root[0] = build(1, n);
    for (int i = 1; i <= m; i++) {
        int v, op, p, c;//v是版本， p是查询或者修改下标
        cin >> v >> op >> p;
        if (op == 1) {
            cin >> c;
            root[i] = modify(root[v], 1, n, p, c);
        } else {
            cout << query(root[v], 1, n, p, p) << '\n';
            root[i] = root[v];
        }
    }
    return 0;
}


