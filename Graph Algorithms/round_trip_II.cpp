#include <bits/stdc++.h>

using namespace std;

#define MAXN int(1e5) + 10

int n;
vector<int> g[MAXN], parent(MAXN);
vector<char> color(MAXN);
int cycle_start {-1}, cycle_end;

bool dfs(int u) {
	color[u] = 1;

	for (int to : g[u]) {
		if (color[to] == 0) {
			parent[to] = u;

			if (dfs(to)) {
				return true;
			}
		} else if (color[to] == 1) {
			cycle_end = u;
			cycle_start = to;

			return true;
		}
	}

	color[u] = 2;

	return false;
}

vector<int> find_cycle() {
	for (int i {}; i < n; ++i) {
		if (color[i] == 0 && dfs(i)) {
			break;
		}
	}


	if (cycle_start == -1) {
		return {};
	}

	vector<int> cycle;

	cycle.push_back(cycle_start);

	for (int v {cycle_end}; v != cycle_start; v = parent[v]) {
		cycle.push_back(v);
	}

	cycle.push_back(cycle_start);

	reverse(cycle.begin(), cycle.end());

	return cycle;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int m;

    cin >> n >> m;

    for (int i {}; i < m; ++i) {
        int u, v;

        cin >> u >> v;

        --u;
        --v;

        g[u].push_back(v);
    }

    vector<int> cycle {find_cycle()};

    if (cycle.size() == 0) {
        cout << "IMPOSSIBLE\n";

        return 0;
    }

    cout << cycle.size() << '\n';

    for (size_t i {}; int v : cycle) {
        cout << v + 1 << " \n"[++i == cycle.size()];
    }

    return 0;
}