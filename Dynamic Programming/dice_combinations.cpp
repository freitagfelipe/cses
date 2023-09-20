#include <bits/stdc++.h>

using namespace std;

#define MOD int(1e9 + 7)

int main() {
    int n;

    cin >> n;

    vector<int> dp(n + 1);

    dp[0] = 1;

    for (int i {1}; i <= n; ++i) {
        for (int j {1}; j <= 6 && i - j >= 0; ++j) {
            dp[i] += dp[i - j];

            dp[i] %= MOD;
        }
    }

    cout << dp[n] << '\n';

    return 0;
}
