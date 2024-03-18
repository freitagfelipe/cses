#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool ok(ll target, int k, const vector<ll> &v) {
    ll current_sum {};

    --k;

    for (ll x : v) {
        if (x > target) {
            return false;
        }

        if (current_sum + x > target) {
            --k;

            current_sum = x;
        } else {
            current_sum += x;
        }
    }

    return k >= 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;

    cin >> n >> k;

    vector<ll> v(n);

    for (ll &x : v) {
        cin >> x;
    }

    ll lo {1}, hi {1};

    while (!ok(hi, k, v)) {
        hi *= 2;
    }

    ll ans {};

    while (lo <= hi) {
        ll mid {(hi - lo) / 2 + lo};

        if (ok(mid, k, v)) {
            ans = mid;

            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    cout << ans << '\n';

    return 0;
}