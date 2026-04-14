#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 1e5 + 10;

struct Node {
    int l, r;
    int val, pri, sz;
    bool rev;
} tr[N];

int n, m, idx, root;

void push_up(int u) { tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + 1; }

void push_down(int u) {
    if (tr[u].rev) {
        swap(tr[u].l, tr[u].r);
        if (tr[u].l) {
            tr[tr[u].l].rev ^= 1;
        }
        if (tr[u].r) {
            tr[tr[u].r].rev ^= 1;
        }
        tr[u].rev = 0;
    }
}

int add(int val) {
    tr[++idx] = {0, 0, val, rand(), 1, 0};
    return idx;
}

void split(int u, int k, int &L, int &R) {
    if (!u) {
        L = R = 0;
        return;
    }
    push_down(u);
    if (tr[tr[u].l].sz >= k) {
        R = u;
        split(tr[u].l, k, L, tr[R].l);
        push_up(R);
    } else {
        L = u;
        split(tr[u].r, k - tr[tr[u].l].sz - 1, tr[L].r, R);
        push_up(L);
    }
}

int merge(int L, int R) {
    if (!L || !R) {
        return L + R;
    }

    if (tr[L].pri > tr[R].pri) {
        push_down(L);
        tr[L].r = merge(tr[L].r, R);
        push_up(L);
        return L;
    } else {
        push_down(R);
        tr[R].l = merge(L, tr[R].l);
        push_up(R);
        return R;
    }
}

void reverse(int l, int r) {
    int A, B, C;
    split(root, r, A, C);
    split(A, l - 1, A, B);
    tr[B].rev ^= 1;
    root = merge(merge(A, B), C);
}

void dfs(int u) {
    if (!u) {
        return;
    }
    push_down(u);
    dfs(tr[u].l);
    cout << tr[u].val << ' ';
    dfs(tr[u].r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        root = merge(root, add(i));
    }

    while (m--) {
        int l, r;
        cin >> l >> r;
        reverse(l, r);
    }

    dfs(root);

    return 0;
}
