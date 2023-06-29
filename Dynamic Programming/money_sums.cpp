#include <bits/stdc++.h>

using namespace std;

#define MAXK 100010

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    bitset<MAXK> b;
    int n;

    b[0] = true;

    cin >> n;

    int sum {};

    for (int i {}; i < n; ++i) {
        int x;

        cin >> x;

        b |= (b << x);

        sum += x;
    }

    b >>= 1;

    cout << b.count() << '\n';

    for (int i {1}; i <= sum; ++i) {
        if (b[0]) {
            cout << i << " \n"[i == sum];
        }

        b >>= 1;
    }

    return 0;
}