#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MAXN 2 * int(1e5) + 10

int v[MAXN];
ll PSA[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;

    cin >> n >> q;

    for (int i {}; i < n; ++i) {
        cin >> v[i];
    }

    PSA[0] = v[0];

    for (int i {1}; i < n; ++i) {
        PSA[i] = PSA[i - 1] + v[i];
    }

    while (q--) {
        int l, r;

        cin >> l >> r;

        --l;
        --r;

        if (l == 0) {
            cout << PSA[r] << '\n';
        } else {
            cout << PSA[r] - PSA[l - 1] << '\n';
        }
    }

    return 0;
}