#include <bits/stdc++.h>
#define int long long

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 5e6 + 10;
const int M = 4e7;
const int INF = 2147483647;

struct Node {
    int l, r;
    int val, pri, sz;
} tr[N];

int n, m, idx;
int a[N], sg[M];

int add(int val) {
    tr[++idx] = {0, 0, val, rand(), 1};
    return idx;
}

void push_up(int u) { tr[u].sz = 1 + tr[tr[u].l].sz + tr[tr[u].r].sz; }

void split(int u, int val, int &L, int &R) {
    if (!u) {
        L = R = 0;
        return;
    }
    if (tr[u].val <= val) {
        L = u;
        split(tr[u].r, val, tr[L].r, R);
        push_up(L);
    } else {
        R = u;
        split(tr[u].l, val, L, tr[R].l);
        push_up(R);
    }
}

int merge(int L, int R) {
    if (!L || !R) {
        return L + R;
    }
    if (tr[L].pri > tr[R].pri) {
        tr[L].r = merge(tr[L].r, R);
        push_up(L);
        return L;
    } else {
        tr[R].l = merge(L, tr[R].l);
        push_up(R);
        return R;
    }
}

void insert(int &root, int val) {
    int L, R;
    split(root, val, L, R);
    root = merge(merge(L, add(val)), R);
}

void erase(int &root, int val) {
    int L, M, R;
    split(root, val, L, R);
    split(L, val - 1, L, M);
    M = merge(tr[M].l, tr[M].r);
    root = merge(merge(L, M), R);
}

int leq(int root, int val) {
    int L, R;
    split(root, val, L, R);
    int res = tr[L].sz;
    root = merge(L, R);
    return res;
}

int les(int root, int val) {
    int L, R;
    split(root, val - 1, L, R);
    int res = tr[L].sz;
    root = merge(L, R);
    return res;
}

int prev(int root, int val) {
    int L, R;
    split(root, val - 1, L, R);
    int res = -INF;
    if (L) {
        int u = L;
        while (tr[u].r) {
            u = tr[u].r;
        }
        res = tr[u].val;
    }
    root = merge(L, R);
    return res;
}

int next(int root, int val) {
    int L, R;
    split(root, val, L, R);
    int res = INF;
    if (R) {
        int u = R;
        while (tr[u].l) {
            u = tr[u].l;
        }
        res = tr[u].val;
    }
    root = merge(L, R);
    return res;
}

void build(int u, int l, int r) {
    for (int i = l; i <= r; i++) {
        insert(sg[u], a[i]);
    }
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
}

void modify(int u, int l, int r, int pos, int val) {
    erase(sg[u], a[pos]);
    insert(sg[u], val);
    if (l == r) {
        a[pos] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) {
        modify(u << 1, l, mid, pos, val);
    } else {
        modify(u << 1 | 1, mid + 1, r, pos, val);
    }
}

int query_leq(int u, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        return leq(sg[u], val);
    }
    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid) {
        res += query_leq(u << 1, l, mid, ql, qr, val);
    }
    if (qr > mid) {
        res += query_leq(u << 1 | 1, mid + 1, r, ql, qr, val);
    }
    return res;
}

int query_les(int u, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        return les(sg[u], val);
    }
    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid) {
        res += query_les(u << 1, l, mid, ql, qr, val);
    }
    if (qr > mid) {
        res += query_les(u << 1 | 1, mid + 1, r, ql, qr, val);
    }
    return res;
}

int query_kth(int ql, int qr, int k) {
    int l = -INF, r = INF, ans = -INF;
    while (l <= r) {
        int mid = l + ((r - l) >> 1);
        int cnt = query_leq(1, 1, n, ql, qr, mid);
        if (cnt >= k) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

int query_prev(int ql, int qr, int val) {
    int l = -INF, r = val - 1, ans = -INF;
    while (l <= r) {
        int mid = l + ((r - l) >> 1);
        int cnt = query_leq(1, 1, n, ql, qr, val - 1) -
                  query_leq(1, 1, n, ql, qr, mid - 1);
        if (cnt > 0) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}

int query_next(int ql, int qr, int val) {
    int l = val + 1, r = INF, ans = INF;
    while (l <= r) {
        int mid = l + ((r - l) >> 1);
        int cnt =
            query_leq(1, 1, n, ql, qr, mid) - query_leq(1, 1, n, ql, qr, val);
        if (cnt > 0) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    build(1, 1, n);

    while (m--) {
        int op, l, r, pos, k, x;
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> x;
            int cnt = query_les(1, 1, n, l, r, x);
            cout << cnt + 1 << '\n';
        } else if (op == 2) {
            cin >> l >> r >> k;
            cout << query_kth(l, r, k) << '\n';
        } else if (op == 3) {
            cin >> pos >> x;
            modify(1, 1, n, pos, x);
            a[pos] = x;
        } else if (op == 4) {
            cin >> l >> r >> x;
            cout << query_prev(l, r, x) << '\n';
        } else {
            cin >> l >> r >> x;
            cout << query_next(l, r, x) << '\n';
        }
    }

    return 0;
}
