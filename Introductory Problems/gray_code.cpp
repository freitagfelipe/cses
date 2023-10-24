#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    string s;

    for (int i {}; i < n; ++i) {
        s += '0';
    }

    vector<vector<string>> dp(n);

    dp[0].push_back("0");
    dp[0].push_back("1");

    for (int i {1}; i < n; ++i) {
        for (string &x : dp[i - 1]) {
            dp[i].push_back('0' + x);
        }

        reverse(dp[i - 1].begin(), dp[i - 1].end());

        for (string &x : dp[i - 1]) {
            dp[i].push_back('1' + x);
        }
    }

    for (string x : dp.back()) {
        cout << x << '\n';
    }

    return 0;
}
