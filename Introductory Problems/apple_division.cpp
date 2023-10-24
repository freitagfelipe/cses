#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll ans {-1}, all_sum;

void solver(int idx, ll sum_a, ll sum_b, const vector<int> &v) {
    if (idx == (int) v.size()) {
        ans = ans == -1 ? abs(sum_a - sum_b) : min(ans, abs(sum_a - sum_b));

        return;
    }

    solver(idx + 1, sum_a + v[idx], sum_b, v);
    solver(idx + 1, sum_a, sum_b + v[idx], v);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    vector<int> v(n);

    for (int &x : v) {
        cin >> x;

        all_sum += x;
    }

    solver(0, 0, 0, v);

    cout << ans << '\n';

    return 0;
}
