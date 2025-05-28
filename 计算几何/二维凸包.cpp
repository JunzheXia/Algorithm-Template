#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 1e5 + 10;
int n;
struct Point {
    double x, y;
    // Point(double x = 0, double y = 0) : x(x), y(y) {}
    bool operator<(const Point &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};
vector<Point> a;

double cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double dist(Point a, Point b) { return hypot(a.x - b.x, a.y - b.y); }

double Andrew() {
    if (n < 2) {
        return 0.0;
    }
    sort(a.begin(), a.end());
    vector<Point> hull;
    for (int i = 0; i < n; i++) {//下凸壳
        while (hull.size() >= 2 &&
               cross(hull[hull.size() - 2], hull.back(), a[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(a[i]);
    }
    int p = hull.size();
    for (int i = n - 2; i >= 0; i--) {//上凸壳
        while (hull.size() > p &&
               cross(hull[hull.size() - 2], hull.back(), a[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(a[i]);
    }
    hull.pop_back();
    if (hull.size() < 2) {
        return 0.0;
    }
    double res = 0.0;
    for (int i = 0; i < hull.size(); i++) {
        int j = (i + 1) % hull.size();
        res += dist(hull[i], hull[j]);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        double x, y;
        cin >> x >> y;
        a.emplace_back(x, y);
    }
    cout << fixed << setprecision(2) << Andrew();

    return 0;
}
