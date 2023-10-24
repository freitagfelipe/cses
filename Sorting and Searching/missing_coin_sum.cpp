#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    vector<int> v(n);

    for (int &x : v) {
        cin >> x;
    }

    sort(v.begin(), v.end());

    if (v[0] != 1) {
        cout << 1 << '\n';

        return 0;
    }

    ll sum {1}, ans {};

    for (int i {1}; i < n; ++i) {
        if (sum < v[i] && sum + 1 != v[i]) {
            ans = sum + 1;

            break;
        }
        
        sum += v[i];
    }

    cout << (ans == 0 ? sum + 1 : ans) << '\n';

    return 0;
}
