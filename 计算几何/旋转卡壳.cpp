求凸包的直径的平方(

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

const int N = 5e4 + 10;

int n;
struct Point {
    double x, y;
    bool operator<(const Point &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};
vector<Point> a;
vector<Point> hull;

double cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double dist(Point a, Point b) { return hypot(a.x - b.x, a.y - b.y); }

void Andrew() {
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 &&
               cross(hull[hull.size() - 2], hull.back(), a[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(a[i]);
    }
    int p = hull.size();
    for (int i = n - 2; i >= 0; i--) {
        while (hull.size() > p &&
               cross(hull[hull.size() - 2], hull.back(), a[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(a[i]);
    }
    hull.pop_back();
}

int Diameter() {
    int p = hull.size();
    // if (p == 2) {
    //     return pow(dist(hull[0], hull[1]), 2);
    // }//不加也能过？！  p = 1 返回0
    double res = 0;
    for (int i = 0, j = 1; i < p; i++) {
        while (cross(hull[i], hull[(i + 1) % p], hull[(j + 1) % p]) >
               cross(hull[i], hull[(i + 1) % p], hull[j])) {
            j = (j + 1) % p;
        }
        res = max(res, dist(hull[i], hull[j]));
    }
    return res * res;
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
    Andrew();
    cout << Diameter();

    return 0;
}
