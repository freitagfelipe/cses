#include <bits/stdc++.h>

using namespace std;

#define MAXN 2 * int(1e5) + 10

int n, l, timer {};
vector<int> g[MAXN], tin(MAXN), tout(MAXN);
vector<vector<int>> up;

void dfs(int u, int p) {
    tin[u] = ++timer;

    up[u][0] = p;

    for (int i {1}; i <= l; ++i) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }

    for (int to : g[u]) {
        if (to != p) {
            dfs(to, u);
        }
    }

    tout[u] = ++timer;
}

void build(int root) {
    l = ceil(log2(n));

    up.assign(n, vector<int>(l + 1));

    dfs(root, root);
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) {
        return u;
    } else if (is_ancestor(v, u)) {
        return v;
    }

    for (int i {l}; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v)) {
            u = up[u][i];
        }
    }

    return up[u][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int q;

    cin >> n >> q;

    for (int i {1}; i < n; ++i) {
        int emp;
        
        cin >> emp;

        --emp;

        g[emp].push_back(i);
        g[i].push_back(emp);
    }

    build(0);

    while (q--) {
        int u, v;

        cin >> u >> v;

        --u;
        --v;

        cout << lca(u, v) + 1 << '\n';
    }

    return 0;
}