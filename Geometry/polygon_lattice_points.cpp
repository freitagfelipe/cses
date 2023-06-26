#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
template <typename T>
struct Point2D {
    T x;
    T y;
 
    Point2D() = default;
};

ll gcd(ll a, ll b) {
    if (a == 0) {
       return b; 
    }

    return gcd(b % a, a);
}
 
template <typename T>
T calculate_area(const vector<Point2D<T>> &polygon) {
	T ans {};
 
	for (int i {}; i < (int) polygon.size(); ++i) {
		Point2D<T> q {i ? polygon[i - 1] : polygon.back()};
		Point2D<T> p {polygon[i]};
 
		ans += (p.y + q.y) * (p.x - q.x);
	}
 
	return abs(ans);
}
 
template <typename T>
ll calculate_lattice_points_in_edges(const vector<Point2D<T>> &polygon) {
    ll ans {};
 
    for (int i {}; i < (int) polygon.size(); ++i) {
		Point2D<T> q {i ? polygon[i - 1] : polygon.back()};
		Point2D<T> p {polygon[i]};
 
        if (p.x == q.x) {
            ans += abs(p.y - q.y) - 1;
        } else if (p.y == q.y) {
            ans += abs(p.x - q.x) - 1;
        } else {
            ans += gcd(abs(p.x - q.x), abs(p.y - q.y)) - 1;
        }
    }
 
    return ans + polygon.size();
}
 
template <typename T>
pair<ll, ll> calculate_lattice_points(const vector<Point2D<T>> &polygon) {
    T area {calculate_area(polygon)};
    ll lattice_points_in_edge {calculate_lattice_points_in_edges(polygon)};
 
    return {(area - lattice_points_in_edge + 2) / 2, lattice_points_in_edge}; 
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
 
    auto [f, s] = calculate_lattice_points(points);
 
    cout << f << " " << s << '\n';
 
    return 0;
}