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

区间第k小值查询
每个版本维护了前i个序列的统计信息，通过比较版本root[r]和root[l-1]来得到[l, r]的统计信息
权值线段树，前缀和，线段树二分
每个节点维护的是在该个节点表示的范围中，前i个元素中有多少个落在这个区间中

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 2e5 + 10;
int a[N], root[N];
int n, m, cnt;
struct node {
    int l, r, sum;
} tr[N * 40];
vector<int> num;

int find(int x) {
    return lower_bound(num.begin(), num.end(), x) - num.begin() + 1;
}

int build(int l, int r) {
    int ind = ++cnt;
    if (l == r) {
        return ind;
    }
    int mid = (l + r) >> 1;
    tr[ind].l = build(l, mid);
    tr[ind].r = build(mid + 1, r);
    return ind;
}

int insert(int pre, int l, int r, int x) {
    int ind = ++cnt;
    tr[ind] = tr[pre];
    tr[ind].sum++;//区间元素个数加一
    if (l == r) {
        return ind;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) {
        tr[ind].l = insert(tr[pre].l, l, mid, x);
    } else {
        tr[ind].r = insert(tr[pre].r, mid + 1, r, x);
    }
    return ind;
}

int query(int u, int v, int l, int r, int k) {
    if (l == r) {
        return l;
    }
    int mid = (l + r) >> 1;
    //计算左子树中元素个数
    int sum = tr[tr[v].l].sum - tr[tr[u].l].sum;
    //第k小在左子树中
    if (k <= sum) {
        return query(tr[u].l, tr[v].l, l, mid, k);
    } else {//第k小在右子树中，同时调整k值
        return query(tr[u].r, tr[v].r, mid + 1, r, k - sum);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        num.push_back(a[i]);
    }
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    root[0] = build(1, num.size());
    for (int i = 1; i <= n; i++) {
        root[i] = insert(root[i - 1], 1, num.size(), find(a[i]));
    }
    for (int i = 1; i <= m; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        int ans = query(root[l - 1], root[r], 1, num.size(), k);
        cout << num[ans - 1] << '\n';
    }

    return 0;
}
