#include <bits/stdc++.h>

using namespace std;

vector<int> kmp(const string &s) {
    int n {(int) s.size()};
    vector<int> pi(n);

    for (int i {1}, j {}; i < n; ++i) {
        if (i > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }

        if (s[i] == s[j]) {
            ++j;
        }

        pi[i] = j;
    }

    return pi;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string t, s;

    cin >> t >> s;

    s += "#";

    vector<int> pi {kmp(s)};
    int ans {};

    for (int i {}, j {}; i < (int) t.size(); ++i) {
        while (j > 0 && t[i] != s[j]) {
            j = pi[j - 1];
        }

        if (t[i] == s[j]) {
            ++j;
        }

        if (j == (int) s.size() - 1) {
            ++ans;
        }
    }

    cout << ans << '\n';

    return 0;
}