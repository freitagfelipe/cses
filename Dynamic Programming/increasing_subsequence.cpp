#include <bits/stdc++.h>

using namespace std;

size_t lis(const vector<int> &v) {
    vector<int> s;

    for (int x : v) {
        vector<int>::iterator it {lower_bound(s.begin(), s.end(), x)};

        if (it == s.end()) {
            s.push_back(x);
        } else {
            *it = x;
        }
    }

    return s.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    vector<int> v(n);

    for (int &x : v) {
        cin >> x;
    }

    cout << lis(v) << '\n';

    return 0;
}