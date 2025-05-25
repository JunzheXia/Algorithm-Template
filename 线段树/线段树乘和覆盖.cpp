优先级： 覆盖 > 乘 > 加法
处理覆盖标记要把别的标记情空
void push_down(int ind) {
    if (tr[ind].cover != INF) {  // 先处理覆盖
        tr[ind<<1].sum = tr[ind].cover * (tr[ind<<1].r - tr[ind<<1].l + 1);
        tr[ind<<1|1].sum = tr[ind].cover * (tr[ind<<1|1].r - tr[ind<<1|1].l + 1);
        tr[ind<<1].cover = tr[ind].cover;  // 子节点继承 cover
        tr[ind<<1|1].cover = tr[ind].cover;
        tr[ind<<1].add = 0;  // 覆盖会清空 add 和 mul
        tr[ind<<1|1].add = 0;
        tr[ind<<1].mul = 1;
        tr[ind<<1|1].mul = 1;
        tr[ind].cover = INF;  // 清除当前节点的 cover
    }
    if (tr[ind].mul != 1) {  // 再处理乘法
        tr[ind<<1].sum *= tr[ind].mul;
        tr[ind<<1|1].sum *= tr[ind].mul;
        tr[ind<<1].add *= tr[ind].mul;  // 乘法会影响 add
        tr[ind<<1|1].add *= tr[ind].mul;
        tr[ind<<1].mul *= tr[ind].mul;
        tr[ind<<1|1].mul *= tr[ind].mul;
        tr[ind].mul = 1;  // 清除当前节点的 mul
    }
    if (tr[ind].add != 0) {  // 最后处理加法
        tr[ind<<1].sum += tr[ind].add * (tr[ind<<1].r - tr[ind<<1].l + 1);
        tr[ind<<1|1].sum += tr[ind].add * (tr[ind<<1|1].r - tr[ind<<1|1].l + 1);
        tr[ind<<1].add += tr[ind].add;
        tr[ind<<1|1].add += tr[ind].add;
        tr[ind].add = 0;  // 清除当前节点的 add
    }
}

    
支持乘和加的区间修改，以及查询
#include<bits/stdc++.h>
#define int long long
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
int n, q, M;
int a[N];
struct node
{
    int l, r, sum, lazy1, lazy2;//两个懒标记 分别记录加法和乘法
}tree[N * 4];
void push_up(int ind) {
    tree[ind].sum = (tree[ind * 2].sum + tree[ind * 2 + 1].sum) % M;
}
void push_down(int ind) {
    // 先处理乘法标记  还要更新加法标记
    if (tree[ind].lazy2 != 1) {
        tree[ind << 1].sum = (tree[ind << 1].sum * tree[ind].lazy2) % M;
        tree[ind << 1 | 1].sum = (tree[ind << 1 | 1].sum * tree[ind].lazy2) % M;
        tree[ind << 1].lazy1 = (tree[ind << 1].lazy1 * tree[ind].lazy2) % M;
        tree[ind << 1 | 1].lazy1 = (tree[ind << 1 | 1].lazy1 * tree[ind].lazy2) % M;
        tree[ind << 1].lazy2 = (tree[ind << 1].lazy2 * tree[ind].lazy2) % M;
        tree[ind << 1 | 1].lazy2 = (tree[ind << 1 | 1].lazy2 * tree[ind].lazy2) % M;
        tree[ind].lazy2 = 1;
    }
    // 再处理加法标记
    if (tree[ind].lazy1) {
        tree[ind << 1].sum = (tree[ind << 1].sum + tree[ind].lazy1 * (tree[ind << 1].r - tree[ind << 1].l + 1)) % M;
        tree[ind << 1 | 1].sum = (tree[ind << 1 | 1].sum + tree[ind].lazy1 * (tree[ind << 1 | 1].r - tree[ind << 1 | 1].l + 1)) % M;
        tree[ind << 1].lazy1 = (tree[ind << 1].lazy1 + tree[ind].lazy1) % M;
        tree[ind << 1 | 1].lazy1 = (tree[ind << 1 | 1].lazy1 + tree[ind].lazy1) % M;
        tree[ind].lazy1 = 0;
    }
}
void build(int ind, int l, int r) {
    tree[ind].l = l; tree[ind].r = r;
    tree[ind].lazy1 = 0;
    tree[ind].lazy2 = 1;
    if (l == r) {
        tree[ind].sum = a[l] % M;
        return;
    }
    int mid = (l + r) >> 1;
    build(ind * 2, l, mid);
    build(ind * 2 + 1, mid + 1, r);
    push_up(ind);
}
void modify1(int ind, int l, int r, int k) { // 加法
    if (tree[ind].l >= l && tree[ind].r <= r) {
        tree[ind].sum = (tree[ind].sum + k * (tree[ind].r - tree[ind].l + 1)) % M;
        tree[ind].lazy1 = (tree[ind].lazy1 + k) % M;
        return;
    }
    push_down(ind);
    int mid = (tree[ind].l + tree[ind].r) >> 1;
    if (l <= mid) modify1(ind << 1, l, r, k);
    if (r > mid) modify1(ind << 1 | 1, l, r, k);
    push_up(ind);
}
void modify2(int ind, int l, int r, int k) { // 乘法
    if (tree[ind].l >= l && tree[ind].r <= r) {
        tree[ind].sum = (tree[ind].sum * k) % M;
        tree[ind].lazy1 = (tree[ind].lazy1 * k) % M;
        tree[ind].lazy2 = (tree[ind].lazy2 * k) % M;
        return;
    }
    push_down(ind);
    int mid = (tree[ind].l + tree[ind].r) >> 1;
    if (l <= mid) modify2(ind << 1, l, r, k);
    if (r > mid) modify2(ind << 1 | 1, l, r, k);
    push_up(ind);
}
int query(int ind, int l, int r) {
    if (tree[ind].l >= l && tree[ind].r <= r) {
        return tree[ind].sum % M;
    }
    if (tree[ind].l > r || tree[ind].r < l) return 0;
    push_down(ind);
    int s = 0;
    int mid = (tree[ind].l + tree[ind].r) >> 1;
    if (l <= mid) s = (s + query(ind << 1, l, r)) % M;
    if (r > mid) s = (s + query(ind << 1 | 1, l, r)) % M;
    return s;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> q >> M;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n);
    while (q--) {
        int op; cin >> op;
        int x, y, k;
        if (op == 1) {
            cin >> x >> y >> k;
            modify2(1, x, y, k);
        }
        else if (op == 2) {
            cin >> x >> y >> k;
            modify1(1, x, y, k);
        }
        else {
            cin >> x >> y;
            cout << query(1, x, y) % M << endl;
        }
    }
    return 0;
}
