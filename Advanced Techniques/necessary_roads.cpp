#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> Edge;

int timer;
vector<vector<int>> g;
vector<int> tin, low;
vector<Edge> bridges;
vector<bool> visited;

void dfs(int u, int p = -1) {
    visited[u] = true;

    tin[u] = low[u] = ++timer;

    for (int to : g[u]) {
        if (to == p) {
            continue;
        }

        if (visited[to]) {
            low[u] = min(low[u], tin[to]);
        } else {
            dfs(to, u);

            low[u] = min(low[u], low[to]);

            if (low[to] > tin[u]) {
                bridges.emplace_back(u, to);
            }
        }
    }
}

void find_bridges(int n) {
	timer = 0;

	tin.assign(n, 0);
	low.assign(n, 0);
	visited.assign(n, false);

	for (int i {}; i < n; ++i) {
		if (!visited[i]) {
			dfs(i);
		}
	}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;

    cin >> n >> m;

    g.assign(n, vector<int>());

    for (int i {}; i < m; ++i) {
        int u, v;

        cin >> u >> v;

        --u;
        --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    find_bridges(n);

    cout << bridges.size() << '\n';

    for (auto [u, v] : bridges) {
        cout << u + 1 << " " << v + 1 << '\n';
    }

    return 0;
}