实数域三分  凸函数

const double eps = 1e-7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    double l, r;
    cin >> n >> l >> r;
    vector<double> a(n + 1);
    for (int i = 0; i <= n; i++) {
        cin >> a[i];
    }

    auto check = [&](double x) -> double {
        double res = 0.0;
        double p = 1.0;
        for (int i = n; i >= 0; i--) {
            res += a[i] * p;
            p *= x;
        }
        return res;
    };

    while (r - l > eps) {
        double lmid = l + (r - l) / 3;
        double rmid = r - (r - l) / 3;

        if (check(lmid) < check(rmid)) {
            l = lmid;
        } else {
            r = rmid;
        }
    }

    cout << fixed << setprecision(10) << (l + r) / 2 << endl;

    return 0;
}
