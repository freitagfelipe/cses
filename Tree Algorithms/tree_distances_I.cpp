#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

#define MAXN 2 * int(1e5) + 10

vector<int> g[MAXN];
int dist[MAXN];

pii diameter_dfs(int u, int d = 0, int p = -1) {
    pii ans {u, d};

    for (int to : g[u]) {
        if (to == p) {
            continue;
        }

        pii result {diameter_dfs(to, d + 1, u)};

        if (result.second > ans.second) {
            ans = result;
        }
    }

    return ans;
}

void dist_dfs(int u, int d = 0, int p = -1) {
    dist[u] = max(dist[u], d);

    for (int to : g[u]) {
        if (to == p) {
            continue;
        }

        dist_dfs(to, d + 1, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    for (int i {}; i < n - 1; ++i) {
        int u, v;

        cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    int d1 {diameter_dfs(1).first};
    int d2 {diameter_dfs(d1).first};

    dist_dfs(d1);
    dist_dfs(d2);

    for (int i {1}; i <= n; ++i) {
        cout << dist[i] << " \n"[i == n];
    }

    return 0;
}