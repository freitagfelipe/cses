#include <bits/stdc++.h>

using namespace std;

#define MAXN int(2e5 + 10)

int n;
vector<int> g[MAXN], subtree_size;

int get_subtree_size(int u, int p = -1) {
    subtree_size[u] = 1;

    for (int to : g[u]) {
        if (to != p) {
            subtree_size[u] += get_subtree_size(to, u);
        }
    }

    return subtree_size[u];
}

int get_centroid(int u, int p = -1) {
    for (int to : g[u]) {
        if (to != p) {
            if (subtree_size[to] * 2 > n) {
                return get_centroid(to, u);
            }
        }
    }

    return u;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    for (int i {}; i < n - 1; ++i) {
        int u, v;

        cin >> u >> v;

        --u;
        --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    subtree_size.assign(n, 0);

    get_subtree_size(0);

    cout << get_centroid(0) + 1 << '\n';

    return 0;
}
