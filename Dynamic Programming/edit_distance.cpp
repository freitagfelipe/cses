#include <bits/stdc++.h>

using namespace std;

int edit_distance(const string &a, const string &b) {
    vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1));

    for (int i {}; i <= (int) a.size(); ++i) {
        dp[i][0] = i;
    }

    for (int i {}; i <= (int) b.size(); ++i) {
        dp[0][i] = i;
    }

    for (int i {}; i < (int) a.size(); ++i) {
        for (int j {}; j < (int) b.size(); ++j) {
            int cost {};

            if (a[i] != b[j]) {
                cost = 1;
            }

            dp[i + 1][j + 1] = min({dp[i][j] + cost, dp[i + 1][j] + 1, dp[i][j + 1] + 1});
        }
    }

    return dp[a.size()][b.size()];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string a, b;

    cin >> a >> b;

    cout << edit_distance(a, b) << '\n';

    return 0;
}