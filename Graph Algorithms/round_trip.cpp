#include <bits/stdc++.h>

using namespace std;

#define MAXN int(1e5) + 10

int n;
vector<int> g[MAXN], parent(MAXN);
bitset<MAXN> visited;
int cycle_start {-1}, cycle_end;

bool dfs(int u, int p = -1) {
	visited[u] = true;

	for (int to : g[u]) {
		if (to == p) {
			continue;
		}

		if (visited[to]) {
			cycle_end = u;
			cycle_start = to;

			return true;
		}

		parent[to] = u;

		if (dfs(to, parent[to])) {
			return true;
		}
	}

	return false;
}

vector<int> find_cycle() {
	for (int i {}; i < n; ++i) {
		if (!visited[i] && dfs(i)) {
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

	return cycle;
}

int main() {
    int m;

    cin >> n >> m;

    for (int i {}; i < m; ++i) {
        int u, v;

        cin >> u >> v;

		--u;
		--v;

        g[u].push_back(v);
        g[v].push_back(u);
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