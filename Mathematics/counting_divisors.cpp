#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll count_divisors(int x) {
    int ans {1};

    for (int i {2}; i * i <= x; ++i) {
        int exp {};

        while (x % i == 0) {
            ++exp;

            x /= i;
        }

        ans *= (exp + 1);
    }

    if (x > 1) {
        ans *= 2;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;

    cin >> t;

    while (t--) {
        int x;

        cin >> x;

        cout << count_divisors(x) << '\n';
    }

    return 0;
}