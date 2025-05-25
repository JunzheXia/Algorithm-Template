单点修改，查询某个区间的最大子段和

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5 + 10;
const int INF = 0x3f3f3f3f;
int a[N];
struct node {
    int l, r;
    int sum, maxx, rmax, lmax;
//maxx 是最大子段和， rmax 是最大后缀和， lmax 是最大前缀和
} tree[N << 2];

void push_up(int ind) {
    tree[ind].sum = tree[ind << 1].sum + tree[ind << 1 | 1].sum;
    tree[ind].lmax = max(
        tree[ind << 1].lmax,                          // 左子树的前缀和
        tree[ind << 1].sum + tree[ind << 1 | 1].lmax  // 左子树整体 + 右子树前缀
    );
    tree[ind].rmax = max(
        tree[ind << 1 | 1].rmax,                      // 右子树的后缀和
        tree[ind << 1 | 1].sum + tree[ind << 1].rmax  // 右子树整体 + 左子树后缀
    );
    tree[ind].maxx = max({
        tree[ind << 1].maxx,                          // 左子树的最大子段和
        tree[ind << 1 | 1].maxx,                      // 右子树的最大子段和
        tree[ind << 1].rmax + tree[ind << 1 | 1].lmax  // 跨越左右的最大子段和
    });
}

void build(int ind, int l, int r) {
    tree[ind].l = l, tree[ind].r = r;
    if (l == r) {
        tree[ind].sum = tree[ind].maxx = tree[ind].lmax = tree[ind].rmax = a[l];
        return;
    }
    int mid = l + r >> 1;
    build(ind << 1, l, mid);
    build(ind << 1 | 1, mid + 1, r);
    push_up(ind);
}

void modify(int ind, int pos, int v) {
    if (tree[ind].l == tree[ind].r) {
        tree[ind].sum = tree[ind].rmax = tree[ind].lmax = tree[ind].maxx = v;
        return;
    }
    int mid = tree[ind].l + tree[ind].r >> 1;
    if (pos <= mid)
        update(ind << 1, pos, v);
    else
        update(ind << 1 | 1, pos, v);
    push_up(ind);
}

node query(int ind, int l, int r) {
    if (tree[ind].l >= l && tree[ind].r <= r) {
        return tree[ind];  // 当前区间完全包含在查询区间内
    }
    int mid = tree[ind].l + tree[ind].r >> 1;
    if (r <= mid) return query(ind << 1, l, r);      // 完全在左子树
    if (l > mid) return query(ind << 1 | 1, l, r);  // 完全在右子树
    // 跨越左右子树，需要合并结果
    node left = query(ind << 1, l, r);
    node right = query(ind << 1 | 1, l, r);
    node res;
    res.sum = left.sum + right.sum;
    res.lmax = max(left.lmax, left.sum + right.lmax);
    res.rmax = max(right.rmax, right.sum + left.rmax);
    res.maxx = max({ left.maxx, right.maxx, left.rmax + right.lmax });
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, 1, n);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            cin >> x >> y;
            if (x > y)
                swap(x, y);
            node res = query(1, x, y);
            cout << res.maxx << endl;
        }
        else {
            int x, y;
            cin >> x >> y;
            modify(1, x, y);
        }
    }
    return 0;
}
