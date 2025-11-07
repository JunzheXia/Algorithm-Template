using cp = complex<double>;

const double PI = acos(-1.0);

void fft(vector<cp> &a, int inv) {
    int n = a.size();
    for (int i = 0, j = 0; i < n; i++) {
        if (i < j)
            swap(a[i], a[j]);
        for (int k = n >> 1; (j ^= k) < k; k >>= 1)
            ;
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * inv;
        cp wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cp w(1);
            for (int j = 0; j < len / 2; j++) {
                cp u = a[i + j], v = w * a[i + j + len / 2];
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (inv == -1)
        for (auto &x : a)
            x /= n;
}

vector<int> mul(vector<cp> a, vector<cp> b) {
    int n = 1, m = a.size() + b.size() - 1;
    while (n < m)
        n <<= 1;
    a.resize(n);
    b.resize(n);

    fft(a, 1);
    fft(b, 1);

    for (int i = 0; i < n; i++)
        a[i] *= b[i];
    fft(a, -1);

    vector<int> res;
    for (int i = 0; i < m; i++) {
        int num = (int)(a[i].real() + 0.5);
        res.push_back(num);
    }

    return res;
}
