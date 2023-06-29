#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

template <typename T>
struct Point2D {
    T x;
    T y;

    Point2D() = default;
};

template <typename T>
int orientation(const Point2D<T> &a, const Point2D<T> &b, const Point2D<T> &c) {
    T result {a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)};

    if (result < 0) {
        return -1;
    } else if (result > 0) {
        return 1;
    }

    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;

    cin >> t;

    vector<Point2D<ll>> points(3);

    while (t--) {
        for (auto &[x, y] : points) {
            cin >> x >> y;
        }

        int o {orientation(points[0], points[1], points[2])};

        if (o == 0) {
            cout << "TOUCH\n";
        } else if (o > 0) {
            cout << "LEFT\n";
        } else {
            cout << "RIGHT\n";
        }
    }

    return 0;
}