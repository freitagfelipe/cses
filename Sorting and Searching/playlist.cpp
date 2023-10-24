#include <bits/stdc++.h>

using namespace std;

#define MAXN int(1e9 + 1)

bitset<MAXN> used;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    vector<int> v(n);

    for (int &x : v) {
        cin >> x;
    }

    int p1 {}, p2 {}, ans {};

    while (p1 < n && p2 < n) {
        while (used[v[p2]]) {
            used[v[p1++]] = false;
        }

        ans = max(ans, p2 - p1 + 1);
        used[v[p2++]] = true;
    }

    cout << ans << '\n';

    return 0;
}
