#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int P = 998244353;
const int G = 3;

i64 qpow(i64 a, i64 b) {
    i64 res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % P;
        }
        a = a * a % P;
        b >>= 1;
    }
    return res;
}

i64 Inv(i64 x) { return qpow(x, P - 2); }

void ntt(vector<i64> &a, int inv) {
    int n = a.size();
    for (int i = 0, j = 0; i < n; i++) {
        if (i < j)
            swap(a[i], a[j]); 
        for (int k = n >> 1; (j ^= k) < k; k >>= 1)
            ;
    }

    for (int len = 2; len <= n; len <<= 1) {
        i64 wlen = qpow(G, (P - 1) / len);
        if (inv == -1) {
            wlen = Inv(wlen);
        }

        for (int i = 0; i < n; i += len) {
            i64 w = 1;
            for (int j = 0; j < len / 2; j++) {
                i64 u = a[i + j];
                i64 v = w * a[i + j + len / 2] % P;
                a[i + j] = (u + v) % P;
                a[i + j + len / 2] = (u - v + P) % P;
                w = w * wlen % P;
            }
        }
    }

    if (inv == -1) {
        i64 inv_n = Inv(n);
        for (int i = 0; i < n; i++) {
            a[i] = a[i] * inv_n % P;
        }
    }
}

vector<i64> mul(vector<i64> a, vector<i64> b, int n) {
    int m = 1;
    while (m < a.size() + b.size() - 1) { 
        m <<= 1;
    }

    a.resize(m);
    b.resize(m);

    ntt(a, 1);
    ntt(b, 1);

    for (int i = 0; i < m; i++) {
        a[i] = a[i] * b[i] % P;
    }

    ntt(a, -1);
    a.resize(n);
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<i64> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<i64> b = {Inv(a[0])};
    int cur = 1;
    while (cur < n) {
        int aim = min(2 * cur, n);
        vector<i64> t = mul(b, b, aim);
        vector<i64> pre = a;
        pre.resize(aim); 
        vector<i64> na = mul(pre, t, aim);
        vector<i64> nb = b;
        nb.resize(aim);

        for (int i = 0; i < aim; i++) {
            if (i < cur) {
                nb[i] = nb[i] * 2 % P;
            } else {
                nb[i] = 0;
            }
        }

        b.resize(aim);
        for (int i = 0; i < aim; i++) {
            b[i] = (nb[i] - na[i] + P) % P;
        }
        cur = aim;
    }

    for (int i = 0; i < n; i++) {
        cout << b[i] << " \n"[i == n - 1]; 
    }

    return 0;
}
