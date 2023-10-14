#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
template <typename T>
struct Point2D {
    T x;
    T y;
 
    Point2D() = default;
 
    Point2D(T x, T y) {
        this->x = x;
        this->y = y;
    }
 
    bool operator==(const Point2D &t) const {
        return this->x == t.x && this->y == t.y;
    }
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

template <typename T>
bool collinear(const Point2D<T> &a, const Point2D<T> &b, const Point2D<T> &c) {
    return orientation(a, b, c) == 0;
}

template <typename T>
bool ccw(const Point2D<T> &a, const Point2D<T> &b, const Point2D<T> &c, bool include_collinear = false) {
    int result {orientation(a, b, c)};

	return result > 0 || (include_collinear && result == 0);
}
 
template <typename T>
int point_in_polygon(const vector<Point2D<T>> &points, const Point2D<T> &t) {
    int n {(int) points.size()};
    int w {};
 
    for (int i {}; i < n; ++i) {
        if (points[i] == t) {
            return 1;
        }
 
        int ne {i + 1 == n ? 0 : i + 1};

        if (points[i].y == t.y && points[ne].y == t.y) {
            if (min(points[i].x, points[ne].x) <= t.x && t.x <= max(points[i].x, points[ne].x)) {
                return 1;
            }
        } else {
            bool below {points[i].y  < t.y};

            if (below != (points[ne].y < t.y)) {
                if (collinear(points[i], t, points[ne])) {
                    return 1;
                }

                if (below == ccw(points[i], t, points[ne])) {
                    w += below ? 1 : -1;
                }
            }
        }
    }

    return w == 0 ? -1 : 0;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n, q;
 
    cin >> n >> q;
 
    vector<Point2D<ll>> points(n);
 
    for (auto &[x, y] : points) {
        cin >> x >> y;
    }
 
    while (q--) {
        int x, y;
 
        cin >> x >> y;
 
        int ans {point_in_polygon(points, Point2D<ll>(x, y))};
 
        if (ans == 0) {
            cout << "INSIDE\n";
        } else if (ans == 1) {
            cout << "BOUNDARY\n";
        } else {
            cout << "OUTSIDE\n";
        }
    }
 
    return 0;
}
