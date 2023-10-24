#include <bits/stdc++.h>

using namespace std;

vector<int> kmp(const string &s) {
    vector<int> pi(s.size());

    for (int i {1}, j {}; i < (int) s.size(); ++i) {
        while (j > 0 && s[i] != s[j]) {
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

    string s;

    cin >> s;

    auto pi {kmp(s)};

    int j {pi[s.size() - 1]};

    vector<int> ans;

    while (j > 0) {
        ans.push_back(j);

        j = pi[j - 1];
    }

    for (int i {(int) ans.size() - 1}; i >= 0; --i) {
        cout << ans[i] << " \n"[i - 1 == -1];
    }

    return 0;
}
