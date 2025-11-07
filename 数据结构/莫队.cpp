#include <bits/stdc++.h>
// 带修莫队模板
// 离线区间不同
using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 133333 + 10;

int n, m, sz, qs, ms, cur;
int L = 1, R = 0, nt = 0;

int a[N], cnt[1000010], ans[N];
struct Query {
    int l, r, t, id;
    bool operator<(const Query &other) const {
        if (l / sz != other.l / sz)
            return l < other.l;
        if (r / sz != other.r / sz)
            return r < other.r;
        return t < other.t;
    }
} query[N];

struct Modify {
    int pos, v;
} modify[N];

void add(int idx) {
    if (++cnt[a[idx]] == 1) {
        cur++;
    }
}

void del(int idx) {
    if (--cnt[a[idx]] == 0) {
        cur--;
    }
}

void update(int t) {
    int pos = modify[t].pos;
    int val = modify[t].v;

    if (L <= pos && pos <= R) {
        del(pos);               
        swap(a[pos], modify[t].v); 
        add(pos);                  
    } else {
        swap(a[pos], modify[t].v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    sz = pow(n, 2.0 / 3.0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        char op;
        int x, y;
        cin >> op >> x >> y;
        if (op == 'Q') {
            query[++qs] = {x, y, ms, qs};
        } else {
            modify[++ms] = {x, y};
        }
    }
    sort(query + 1, query + 1 + qs);

    for (int i = 1; i <= qs; i++) {
        int t = query[i].t, l = query[i].l, r = query[i].r;
        while (nt < t)
            update(++nt);
        while (nt > t)
            update(nt--);
        while (R < r)
            add(++R);
        while (R > r)
            del(R--);
        while (L < l)
            del(L++);
        while (L > l)
            add(--L);

        ans[query[i].id] = cur;
    }

    for (int i = 1; i <= qs; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
