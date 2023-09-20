#include <bits/stdc++.h>

using namespace std;

pair<vector<int>, vector<int>> solver(int n) {
    vector<int> f, s;

    int p1 {1}, p2 {n & 1 ? n - 1 : n};
    bool pf {true};

    for (int i {}; i < n / 2; ++i) {
        (pf ? f : s).push_back(p1++);
        (pf ? f : s).push_back(p2--);

        pf = !pf;
    }

    if (n & 1) {
        s.push_back(n);
    }

    return {f, s};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    if (((n * n + n) / 2) & 1) {
        cout << "NO\n";

        return 0;
    }

    cout << "YES\n";

    auto [f, s] {solver(n)};

    cout << f.size() << '\n';

    for (size_t i {}; int x : f) {
        cout << x << " \n"[++i == f.size()];
    }

    cout << s.size() << '\n';

    for (size_t i {}; int x : s) {
        cout << x << " \n"[++i == s.size()];
    }

    return 0;
}
