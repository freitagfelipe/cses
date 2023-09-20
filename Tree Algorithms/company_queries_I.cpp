#include <bits/stdc++.h>

using namespace std;

#define MAXN int(2e5) + 10

int n, lg;
vector<int> g[MAXN], depth;
vector<vector<int>> up;

void dfs(int u, int d, int p = -1) {
    up[u][0] = p;
    depth[u] = d;

    for (int i {1}; i <= lg; ++i) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }

    for (int to : g[u]) {
        if (to != p) {
            dfs(to, d + 1, u);
        }
    }
}

void build() {
    lg = ceil(log2(n));
    up.assign(n + 1, vector<int>(lg + 1));
    depth.assign(n + 1, 0);

    dfs(1, 0, 1);
}

int query(int u, int k) {
    if (u == 1 || depth[u] - k < 0) {
        return -1;
    }

    int u_depth {depth[u]};

    for (int i {lg}; i >= 0; --i) {
        if (u_depth - depth[up[u][i]] <= k) {
            u = up[u][i];
        }
    }

    return u;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int q;

    cin >> n >> q;

    for (int i {2}; i <= n; ++i) {
        int u;

        cin >> u;

        g[u].push_back(i);
        g[i].push_back(u);
    }

    build();

    while (q--) {
        int u, k;

        cin >> u >> k;

        cout << query(u, k) << '\n';
    }

    return 0;
}
