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

template <typename T>
bool intersect_aux(T a, T b, T c, T d) {
    if (a > b) {
        swap(a, b);
    }

    if (c > d) {
        swap(c, d);
    }

    return max(a, c) <= min(b, d);
}

template <typename T>
bool intersect(const Point2D<T> &a, const Point2D<T> &b, const Point2D<T> &c, const Point2D<T> &d) {
    if (orientation(c, a, d) == 0 && orientation(c, b, d) == 0) {
        return intersect_aux(a.x, b.x, c.x, d.x) && intersect_aux(a.y, b.y, c.y, d.y);
    }

    bool first_condition(orientation(a, b, c) != orientation(a, b, d));
    bool second_condition(orientation(c, d, a) != orientation(c, d, b));

    return first_condition && second_condition;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;

    cin >> t;    

    vector<Point2D<ll>> points(4);

    while (t--) {
        for (auto &[x, y] : points) {
            cin >> x >> y;
        }

        intersect(points[0], points[1], points[2], points[3]) ? cout << "YES\n" : cout << "NO\n";
    }

    return 0;
}