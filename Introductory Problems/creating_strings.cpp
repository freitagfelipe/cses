#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

int factorial(int n) {
    int f {1};

    for (int i {n}; i > 0; --i) {
        f *= i;
    }

    return f;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;

    cin >> s;

    vector<int> v(26);

    for (char ch : s) {
        ++v[ch - 'a'];
    }

    int repeated {1};

    for (int x : v) {
        if (x == 0) {
            continue;
        }

        repeated *= factorial(x);
    }

    cout << factorial((int) s.size()) / repeated << '\n';

    sort(s.begin(), s.end());

    cout << s << '\n';

    while (next_permutation(s.begin(), s.end())) {
        cout << s << '\n';
    }

    return 0;
}
