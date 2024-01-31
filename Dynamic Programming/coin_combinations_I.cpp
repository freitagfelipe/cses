#include <bits/stdc++.h>

using namespace std;

#define MOD int(1e9 + 7)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;

    cin >> n >> x;

    vector<int> coins(n);

    for (int &c : coins) {
        cin >> c;
    }

    vector<int> dp(x + 1);

    dp[0] = 1;

    for (int i {1}; i <= x; ++i) {
        for (int c : coins) {
            if (i - c < 0) {
                continue;
            }

            dp[i] += dp[i - c];
            dp[i] %= MOD;
        }
    }

    cout << dp[x] << '\n';

    return 0;
}
