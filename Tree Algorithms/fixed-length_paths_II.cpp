#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
#define MAXN int(2e5 + 10)
 
int n, kmin, kmax;
vector<int> g[MAXN], dists;
int subtree_size[MAXN], BIT[MAXN];
bool is_removed[MAXN];
 
int range_query(int l, int r) {
    int ans {};

    for (; r > 0; r -= r & -r) {
        ans += BIT[r];
    }

    if (l != 0) {
        for (--l; l > 0; l -= l & -l) {
            ans -= BIT[l];
        }
    } else {
        ans += 1;
    }

    return ans;
}
 
void update(int idx, int x) {
    for (; idx <= kmax; idx += idx & -idx) {
        BIT[idx] += x;
    }
}

void reset(int limit) {
    for (int i {1}; i <= kmax; ++i) {
        BIT[i] = 0;
    }
}
 
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
 
int dfs(int u, int p, int d) {
    if (d > kmax) {
        return d - 1;
    }

    int max_dist {d};

    ++dists[d];

    for (int to : g[u]) {
        if (to == p || is_removed[to]) {
            continue;
        }

        max_dist = max(max_dist, dfs(to, u, d + 1));
    }

    return max_dist;
}

ll centroid_decomposition(int u) {
    int subtree_size {get_subtree_size(u)};
    int centroid {get_centroid(u, subtree_size)};

    is_removed[centroid] = true;

    ll ans {};
    int max_dist {};
    int last_max_dist {};

    for (int to : g[centroid]) {
        if (!is_removed[to]) {
            max_dist = max(max_dist, dfs(to, centroid, 1));

            for (int d {1}; d <= max_dist; ++d) {
                ans += 1LL * dists[d] * range_query(max(0, kmin - d), kmax - d);
            }

            for (int d {1}; d <= max_dist; ++d) {
                update(d, dists[d]);

                dists[d] = 0;
            }

            last_max_dist = max(last_max_dist, max_dist);

            max_dist = 0;
        }
    }

    for (int i {1}; i <= last_max_dist; ++i) {
        update(i, -range_query(i, i));
    }

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

    cin >> n >> kmin >> kmax;

    if (kmin > kmax) {
        swap(kmin, kmax);
    }

    dists.assign(n + 1, 0);

    for (int i {}; i < n - 1; ++i) {
        int u, v;

        cin >> u >> v;

        --u;
        --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    ll ans {centroid_decomposition(0)};

    cout << ans << '\n';

    return 0;
}
