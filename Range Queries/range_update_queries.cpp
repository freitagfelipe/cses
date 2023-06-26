#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MAXN 2 * int(1e5) + 10

int n;
ll BIT[MAXN];

void update(int i, int v) {
    for (; i <= n; i += i & -i) {
        BIT[i] += v;
    }
}

ll query(int i) {
    ll ans {};

    for (; i > 0; i -= i & -i) {
        ans += BIT[i];
    }

    return ans;
}

void range_update(int l, int r, int v) {
    update(l, v);
    update(r + 1, -v);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int q;

    cin >> n >> q;

    for (int i {1}; i <= n; ++i) {
        int x;

        cin >> x;

        range_update(i, i, x);
    }

    while (q--) {
        int op;

        cin >> op;

        if (op == 1) {
            int l, r, v;

            cin >> l >> r >> v;

            range_update(l, r, v);
        } else {
            int t;

            cin >> t;

            cout << query(t) << '\n';
        }
    }

    return 0;
}