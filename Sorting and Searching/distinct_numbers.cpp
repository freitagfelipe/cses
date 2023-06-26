#include <bits/stdc++.h>

using namespace std;

#define MAXN int(1e9) + 10

bitset<MAXN> bit;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    for (int i {}; i < n; ++i) {
        int x;

        cin >> x;

        bit[x] = true;
    }

    cout << bit.count() << '\n';

    return 0;
}