#include <bits/stdc++.h>

using namespace std;

int timer;
vector<vector<int>> g;
vector<int> tin, low;
vector<bool> visited, is_articulation_point;

void dfs(int u, int p = -1) {
    visited[u] = true;

    tin[u] = low[u] = ++timer;

    int children {};

    for (int to : g[u]) {
        if (to == p) {
            continue;
        }

        if (visited[to]) {
            low[u] = min(low[u], tin[to]);
        } else {
            dfs(to, u);

            low[u] = min(low[u], low[to]);

            if (low[to] >= tin[u] && p != -1) {
                is_articulation_point[u] = true;
            }

            ++children;
        }
    }

    if (p == -1 && children > 1) {
        is_articulation_point[u] = true;
    }
}

void find_articulation_points(int n) {
	timer = 0;

	tin.assign(n, 0);
	low.assign(n, 0);
	visited.assign(n, false);
	is_articulation_point.assign(n, false);

	for (int i {}; i < n; ++i) {
		if (!visited[i]) {
			dfs(i);
		}
	}
}

int main() {
    int n, m;

    cin >> n >> m;

    g.assign(n, vector<int>());

    for (int i {}; i < m; ++i) {
        int a, b;

        cin >> a >> b;

        --a;
        --b;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    find_articulation_points(n);

    vector<int> ans;

    for (int i {}; i < n; ++i) {
        if (is_articulation_point[i]) {
            ans.push_back(i + 1);
        }
    }

    cout << ans.size() << '\n';

    for (int i {}; i < (int) ans.size(); ++i) {
        cout << ans[i] << " \n"[i + 1 == (int) ans.size()];
    }

    return 0;
}