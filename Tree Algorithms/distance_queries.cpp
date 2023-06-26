#include <bits/stdc++.h>
 
using namespace std;
 
#define MAXN int(1e5 * 2 + 10)
 
int n, l, timer {};
vector<int> g[MAXN], tin(MAXN), tout(MAXN), dist(MAXN);
vector<vector<int>> up;
 
void dfs(int u, int p, int d = 0) {
    dist[u] = d;
    tin[u] = ++timer;
    up[u][0] = p;
 
    for (int i {1}; i <= l; ++i) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
 
    for (int to : g[u]) {
        if (to != p) {
            dfs(to, u, d + 1);
        }
    }
 
    tout[u] = ++timer;
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
 
void build(int root) {
    l = ceil(log2(n));
 
    up.assign(n, vector<int>(l + 1));
 
    dfs(root, root);
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
 
    int q;
 
    cin >> n >> q;
 
    for (int i {}; i < n - 1; ++i) {
        int v, u;
 
        cin >> v >> u;
 
        --v;
        --u;
 
        g[v].push_back(u);
        g[u].push_back(v);
    }
 
    build(0);
 
    while (q--) {
        int v, u;
 
        cin >> v >> u;
 
        --v;
        --u;
 
        cout << dist[v] + dist[u] - 2 * dist[lca(u, v)] << '\n';
    }
 
    return 0;
}