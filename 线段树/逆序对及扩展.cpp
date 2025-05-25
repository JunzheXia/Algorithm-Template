逆序对

#include <bits/stdc++.h>
#define int long long
using namespace std;
using ll = long long;
const int N = 5e5 + 10;
int n;
struct Node {
    int val, ind;
} a[N];
int c[N]; // 离散化后的新索引
struct SegmentTree {
    int l, r, sum;
} tree[N * 4];
void build(int ind, int l, int r) {
    tree[ind].l = l;
    tree[ind].r = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(ind << 1, l, mid);
    build(ind << 1 | 1, mid + 1, r);
}
void update(int ind, int x) {
    if (tree[ind].l == tree[ind].r) {
        tree[ind].sum += 1;
        return;
    }
    int mid = (tree[ind].l + tree[ind].r) >> 1;
    if (x <= mid) update(ind << 1, x);
    else update(ind << 1 | 1, x);
    tree[ind].sum = tree[ind << 1].sum + tree[ind << 1 | 1].sum;
}
int query(int ind, int l, int r) {
    if (tree[ind].l >= l && tree[ind].r <= r) {
        return tree[ind].sum;
    }
    if (tree[ind].r < l || tree[ind].l > r) return 0;
    return query(ind << 1, l, r) + query(ind << 1 | 1, l, r);
}
bool cmp(Node a, Node b) {
    if (a.val == b.val) return a.ind < b.ind;
    else return a.val < b.val;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].val;
        a[i].ind = i;
    }
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= n; i++) {
        c[a[i].ind] = i;
    }
    build(1, 1, n);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += query(1, c[i] + 1, n);
        update(1, c[i]);
    }
    cout << ans << endl;
    return 0;
}

逆序对我们只需要 计算比离散化后比当前元素的的个数
那么如何求三元偏序呢，只需要在求比当前元素大的基础上，
多求一次比当前元素小的个数

#include <bits/stdc++.h>
#define int long long
using namespace std;
using ll = long long;
const int N = 5e5 + 10;
int n;
struct Node {
    int val, ind;
} a[N];
int c[N], L[N], R[N];
struct SegmentTree {
    int l, r, sum;
} tree[N * 4];

void build(int ind, int l, int r) {
    tree[ind].l = l;
    tree[ind].r = r;
    tree[ind].sum = 0;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(ind << 1, l, mid);
    build(ind << 1 | 1, mid + 1, r);
    tree[ind].sum = tree[ind << 1].sum + tree[ind << 1 | 1].sum;
}

void update(int ind, int pos) {
    if (tree[ind].l == tree[ind].r) {
        tree[ind].sum += 1;
        return;
    }
    int mid = (tree[ind].l + tree[ind].r) >> 1;
    if (pos <= mid)
        update(ind << 1, pos);
    else
        update(ind << 1 | 1, pos);
    tree[ind].sum = tree[ind << 1].sum + tree[ind << 1 | 1].sum;
}

int query(int ind, int l, int r) {
    if (tree[ind].l >= l && tree[ind].r <= r)
        return tree[ind].sum;
    if (tree[ind].r < l || tree[ind].l > r)
        return 0;
    return query(ind << 1, l, r) + query(ind << 1 | 1, l, r);
}

bool cmp(Node a, Node b) {
    if (a.val == b.val)
        return a.ind < b.ind;
    return a.val < b.val;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].val;
        a[i].ind = i;
    }
    sort(a + 1, a + 1 + n, cmp);
///与二元偏序不同，三元偏序两个元素相等也会对结果
///产生影响，所以离散化的方式也要改变
///不能再向之前那样即使是同一个元素，索引却不一样
///相同元素索引应该一样
    int rank = 1;
    c[a[1].ind] = 1;
    for (int i = 2; i <= n; i++) {
        if (a[i].val != a[i - 1].val)
           rank++;
       c[a[i].ind] = rank;
   }

   build(1, 1, n);
   for (int i = 1; i <= n; i++) {
       L[i] = query(1, 1, c[i] - 1);
       update(1, c[i]);
   }
///这里正序没有问题，与逆序相反
///再次进行build是为了清空之前的影响
   build(1, 1, n);
   for (int i = n; i >= 1; i--) {
       R[i] = query(1, c[i] + 1, n);
       update(1, c[i]);
   }
///该次循环需要逆序遍历，如果正序那就成求逆序了，
   ll ans = 0;
   for (int i = 1; i <= n; i++)
       ans += 1LL * L[i] * R[i];
   cout << ans << endl;
   return 0;
}
