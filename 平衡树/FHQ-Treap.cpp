#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 2e5 + 10;
const int INF = 1e9;

struct Node {
    int l, r;
    int val, pri, sz;
} tr[N];

int n, idx, root;

int add(int val) {
    tr[++idx] = {0, 0, val, rand(), 1};
    return idx;
}

void pushup(int u) { tr[u].sz = 1 + tr[tr[u].l].sz + tr[tr[u].r].sz; }

void split(int u, int val, int &L, int &R) {
    if (!u) {
        L = R = 0;
        return;
    }

    if (tr[u].val <= val) {
        L = u;
        split(tr[u].r, val, tr[L].r, R);
        pushup(L);
    } else {
        R = u;
        split(tr[u].l, val, L, tr[R].l);
        pushup(R);
    }
}

int merge(int L, int R) {
    if (!L || !R) {
        return L + R;
    }
    if (tr[L].pri > tr[R].pri) {
        tr[L].r = merge(tr[L].r, R);
        pushup(L);
        return L;
    } else {
        tr[R].l = merge(L, tr[R].l);
        pushup(R);
        return R;
    }
}

void insert(int val) {
    int L, R;
    split(root, val, L, R);
    root = merge(merge(L, add(val)), R);
}

void erase(int val) {
    int L, M, R;
    split(root, val, L, R);
    split(L, val - 1, L, M);
    M = merge(tr[M].l, tr[M].r);
    root = merge(merge(L, M), R);
}

int getrank(int val) {
    int L, R;
    split(root, val - 1, L, R);
    int ans = tr[L].sz + 1;
    root = merge(L, R);
    return ans;
}

int kth(int u, int k) {
    if (k <= tr[tr[u].l].sz) {
        return kth(tr[u].l, k);
    }
    if (k <= tr[tr[u].l].sz + 1) {
        return tr[u].val;
    }
    return kth(tr[u].r, k - tr[tr[u].l].sz - 1);
}

int prev(int val) {
    int L, R;
    split(root, val - 1, L, R);
    int ans = -INF;
    if (L) {
        int u = L;
        while (tr[u].r) {
            u = tr[u].r;
        }
        ans = tr[u].val;
    }
    root = merge(L, R);
    return ans;
}

int next(int val) {
    int L, R;
    split(root, val, L, R);
    int ans = INF;
    if (R) {
        int u = R;
        while (tr[u].l) {
            u = tr[u].l;
        }
        ans = tr[u].val;
    }
    root = merge(L, R);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    while (n--) {
        int op, x, res;
        cin >> op >> x;
        if (op == 1) {
            insert(x);
        } else if (op == 2) {
            erase(x);
        } else if (op == 3) {
            res = getrank(x);
        } else if (op == 4) {
            res = kth(root, x);
        } else if (op == 5) {
            res = prev(x);
        } else {
            res = next(x);
        }

        if (op > 2) {
            cout << res << '\n';
        }
    }

    return 0;
}
