#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
template <typename T>
struct Point2D {
    T x;
    T y;
 
    Point2D() {
        this->x = 0;
        this->y = 0;
    }
 
	bool operator<(const Point2D &t) const {
		return this->x < t.x;
	}
};
 
template <typename T>
double distance_between_points(const Point2D<T> &a, const Point2D<T> &b) {
	T dx {a.x - b.x};
	T dy {a.y - b.y};
 
	return sqrt(dx * dx + dy * dy);
}
 
template <typename T>
using ptt = pair<T, T>;
 
template <typename T>
ll find_minimum_distance(vector<Point2D<T>> points) {
	typedef ptt<T> ptt;
 
	int n {(int) points.size()};

	sort(points.begin(), points.end());
 
	int fp {}, p1 {}, p2 {1};
	set<ptt> active_points;
 
	double ans {distance_between_points(points[0], points[1])};
 
	for (int i {}; i < n; ++i) {
		while (fp < i && points[i].x - points[fp].x >= ans) {
			active_points.erase({points[fp].y, fp});
 
			++fp;
		}
 
		auto it {active_points.lower_bound({points[i].y - ans, 0})};

		while (it != active_points.end() && it->first < points[i].y + ans) {
			double d {distance_between_points(points[i], points[it->second])};

			if (d < ans) {
				ans = d;

				p1 = it->second;
				p2 = i;
			}

			++it;
		}
 
		active_points.insert({points[i].y, i});
	}

	auto [x1, y1] = points[p1];
	auto [x2, y2] = points[p2];

	T dx {x2 - x1}, dy {y2 - y1};
 
	return dx * dx + dy * dy;
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
 
    cout << find_minimum_distance(points) << '\n';
 
    return 0;
}