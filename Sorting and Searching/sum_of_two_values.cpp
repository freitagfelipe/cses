#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;

    cin >> n >> k;

    map<int, int> mp;

    for (int i {1}; i <= n; ++i) {
        int x;

        cin >> x;

        size_t r {mp.count(k - x)};

        if (r != 0) {
            cout << mp[k - x] << " " << i << '\n';

            return 0;
        }

        mp[x] = i;
    }

    cout << "IMPOSSIBLE\n";

    return 0;
}