#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    vector<pii> v(n);

    for (auto &[f, s] : v) {
        cin >> f >> s;
    }

    sort(v.begin(), v.end(), [](const pii &a, const pii &b) {
        return a.second < b.second;
    });

    int last_end {v[0].second};
    int ans {1};

    for (int i {1}; i < n; ++i) {
        if (v[i].first >= last_end) {
            last_end = v[i].second;

            ++ans;
        }
    }

    cout << ans << '\n';

    return 0;
}
