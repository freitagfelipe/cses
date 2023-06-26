#include <bits/stdc++.h>

using namespace std;

#define MAXN 2 * int(1e5) + 10

int v[MAXN];
int PXA[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;

    cin >> n >> q;

    for (int i {1}; i <= n; ++i) {
        cin >> v[i];
    }

    PXA[1] = v[1];

    for (int i {2}; i <= n; ++i) {
        PXA[i] = PXA[i - 1] ^ v[i];
    }

    while (q--) {
        int l, r;

        cin >> l >> r;

        cout << (PXA[r] ^ PXA[l - 1]) << '\n';
    }

    return 0;
}