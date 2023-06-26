#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MAXN 2 * int(1e5) + 10

int n;
int v[MAXN];
ll BIT[MAXN];

void update(int idx, int x) {
    int delta {x - v[idx]};
    v[idx] = x;

    for (; idx <= n; idx += idx & -idx) {
        BIT[idx] += delta;
    }
}

ll query(int idx) {
    ll ans {};

    for (; idx > 0; idx -= idx & -idx) {
        ans += BIT[idx];
    }

    return ans;
}

ll range_query(int l, int r) {
    return query(r) - query(l - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int q;

    cin >> n >> q;

    for (int i {1}; i <= n; ++i) {
        int x;

        cin >> x;

        update(i, x);
    }

    while (q--) {
        int op;

        cin >> op;

        if (op == 1) {
            int idx, u;

            cin >> idx >> u;

            update(idx, u);
        } else {
            int l, r;

            cin >> l >> r;

            cout << range_query(l, r) << '\n';
        }
    }

    return 0;
}