#include <bits/stdc++.h>

using namespace std;

#define MAXN int(2e5 + 10)

typedef long long ll;

int k;
vector<int> g[MAXN], subtree_size, dists;
bitset<MAXN> is_removed;

int get_subtree_size(int u, int p = -1) {
    subtree_size[u] = 1;

    for (int to : g[u]) {
        if (to != p && !is_removed[to]) {
            subtree_size[u] += get_subtree_size(to, u);
        }
    }

    return subtree_size[u];
}
 
int get_centroid(int u, int tree_size, int p = -1) {
    for (int to : g[u]) {
        if (to == p || is_removed[to]) {
            continue;
        }

        if (subtree_size[to] * 2 > tree_size) {
			return get_centroid(to, tree_size, u);
        }
    }

    return u;
}
 
int dfs(int u, int p, int d, bool filling, ll &ans, vector<int> &dists) {
    int max_dist {d};

    if (d > k) {
        return max_dist;
    }

    if (filling) {
        ++dists[d];
    } else {
        ans += dists[k - d];
    }

    for (int to : g[u]) {
        if (to == p || is_removed[to]) {
            continue;
        }

        max_dist = max(max_dist, dfs(to, u, d + 1, filling, ans, dists));
    }

    return max_dist;
}

ll centroid_decomposition(int u) {
    int centroid {get_centroid(u, get_subtree_size(u))};

    is_removed[centroid] = true;

    ll ans {};
    int max_dist {};

    dists[0] = 1;

    for (int to : g[centroid]) {
        if (!is_removed[to]) {
            max_dist = max(max_dist, dfs(to, -1, 1, false, ans, dists));
            max_dist = max(max_dist, dfs(to, -1, 1, true, ans, dists));
        }
    }

    fill(dists.begin(), dists.begin() + max_dist + 1, 0);

    for (int to : g[centroid]) {
        if (is_removed[to]) {
            continue;
        }

        ans += centroid_decomposition(to);
    }

    return ans;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n >> k;

    for (int i {}; i < n - 1; ++i) {
        int u, v;

        cin >> u >> v;

        --u;
        --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    subtree_size.assign(n, 0);
    dists.assign(k + 1, 0);

    ll ans {centroid_decomposition(0)};

    cout << ans << '\n';

    return 0;
}
