#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MAXN 2 * int(1e5) + 10

ll v[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    for (int i {}; i < n; ++i) {
        cin >> v[i];
    }

    ll ans {v[0]}, sum {v[0]};

    for (int i {1}; i < n; ++i) {
        sum = max(v[i], sum + v[i]);

        ans = max(ans, sum);
    }

    cout << ans << '\n';

    return 0;
}