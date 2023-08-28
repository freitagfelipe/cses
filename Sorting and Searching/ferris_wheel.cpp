#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;

    cin >> n >> k;

    vector<int> v(n);

    for (int &x : v) {
        cin >> x;
    }

    sort(v.begin(), v.end());

    int p1 {}, p2 {n - 1};
    int used {};

    while (p1 <= p2) {
        ++used;

        if (v[p1] + v[p2] <= k) {
            ++p1;
            --p2;
        } else {
            --p2;
        }
    }

    cout << used << '\n';

    return 0;
}
