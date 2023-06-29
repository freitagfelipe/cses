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
T calculate_two_times_area(const vector<Point2D<T>> &polygon) {
	T ans {};

	for (int i {}; i < (int) polygon.size(); ++i) {
		Point2D<T> q {i ? polygon[i - 1] : polygon.back()};
		Point2D<T> p {polygon[i]};

		ans += (p.y + q.y) * (p.x - q.x);
	}

	return abs(ans);
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

    cout << calculate_two_times_area(points) << '\n';

    return 0;
}