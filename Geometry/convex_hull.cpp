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

    bool operator<(const Point2D &t) const {
        if (this->x == t.x) {
            return this->y < t.y;
        }

        return this->x < t.x;
    }
};
 
template <typename T>
bool point_in_segment(const Point2D<T> &a, const Point2D<T> &b, const Point2D<T> &c) {
	if (cross(b - a, c - a) != 0) {
		return false;
	}
 
	if (min(a.x, b.x) > c.x || c.x > max(a.x, b.x)) {
		return false;
	} else if (min(a.y, b.y) > c.y || c.y > max(a.y, b.y)) {
		return false;
	}
 
	return true;
}
 
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
bool ccw(const Point2D<T> &a, const Point2D<T> &b, const Point2D<T> &c, bool include_collinear = false) {
    int result {orientation(a, b, c)};

	return result > 0 || (include_collinear && result == 0);
}

template <typename T>
bool cw(const Point2D<T> &a, const Point2D<T> &b, const Point2D<T> &c, bool include_collinear = false) {
    int result {orientation(a, b, c)};
 
    return result < 0 || (include_collinear && result == 0);
}
 
template <typename T>
vector<Point2D<T>> monotone_chain(vector<Point2D<T>> &points, bool include_collinear = false) {
	sort(points.begin(), points.end());

	vector<Point2D<T>> up, down;

    Point2D<T> p1 {points[0]}, p2 {points.back()};

    int n {(int) points.size()};
    up.push_back(p1);
    down.push_back(p1);

    for (int i {1}; i < n; ++i) {
        if (i == n - 1 || cw(p1, points[i], p2, include_collinear)) {
            while (up.size() >= 2 
                && !cw(up[up.size() - 2], up.back(), points[i], include_collinear)
            ) {
                up.pop_back();
            }

            up.push_back(points[i]);
        }

        if (i == n - 1 || ccw(p1, points[i], p2, include_collinear)) {
            while (down.size() >= 2
                && !ccw(down[down.size() - 2], down.back(), points[i], include_collinear)
            ) {
                down.pop_back();
            }

            down.push_back(points[i]);
        }
    }

	if (include_collinear && up.size() == points.size()) {
		reverse(up.begin(), up.end());

		return up;
	}

	vector<Point2D<T>> convex_hull {move(up)};

	for (int i {(int) down.size() - 2}; i > 0; --i) {
		convex_hull.push_back(down[i]);
	}

	return convex_hull;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    vector<Point2D<ll>> points(n);

    for (auto &[x, y] : points) {
        cin >> x >> y;
    }

    vector<Point2D<ll>> convex_hull {monotone_chain(points, true)};

    cout << convex_hull.size() << '\n';

    for (auto [x, y] : convex_hull) {
        cout << x << " " << y << '\n';
    }

    return 0;
}