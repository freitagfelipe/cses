#include <bits/stdc++.h>

using namespace std;

#define MAXN int(2e5 + 10)

typedef long long ll;

vector<int> g[MAXN];
ll BIT[MAXN];
int n, timer;

void update(int idx, ll x) {
    for (; idx <= n; idx += idx & -idx) {
        BIT[idx] += x;
    }
}

ll query(int idx) {
    ll sum {};

    for (; idx > 0; idx -= idx & -idx) {
        sum += BIT[idx];
    }

    return sum;
}

ll range_query(int l, int r) {
    return query(r) - query(l - 1);
}

template <bool is_path_query>
void dfs(int u, int p, vector<int> &start, vector<int> &end) {
    start[u] = ++timer;

    for (int to : g[u]) {
        if (to == p) {
            continue;
        }

        dfs<is_path_query>(to, u, start, end);
    }

    if (is_path_query) {
        ++timer;
    }

    end[u] = timer;
}

template <bool is_path_query = false>
tuple<vector<int>, vector<int>> get_euler_tour(int s) {
    vector<int> start(n), end(n);

    dfs<is_path_query>(s, -1, start, end);

    return {start, end};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int q;

    cin >> n >> q;

    vector<int> v(n);

    for (int &x : v) {
        cin >> x;
    }

    for (int i {}; i < n - 1; ++i) {
        int u, v;

        cin >> u >> v;

        --u;
        --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    auto [start, end] {get_euler_tour(0)};

    for (size_t i {}; int x : v) {
        update(start[i++], x);
    }

    while (q--) {
        int op;

        cin >> op;

        if (op == 1) {
            int u, x;

            cin >> u >> x;

            update(start[u - 1], x - v[u - 1]);

            v[u - 1] = x;
        } else {
            int u;

            cin >> u;

            cout << range_query(start[u - 1], end[u - 1]) << '\n';
        }
    }

    return 0;
}
