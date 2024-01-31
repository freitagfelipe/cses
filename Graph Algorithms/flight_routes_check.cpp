#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g, tg, same_comp;
vector<int> ts, component;
vector<bool> visited;

void ts_dfs(int u) {
	visited[u] = true;

    for (int to : g[u]) {
        if (!visited[to]) {
            ts_dfs(to);
        }
    }

    ts.push_back(u);
}

void component_dfs(int u, int c) {
	component[u] = c;
    same_comp[c].push_back(u);

    for (int to : tg[u]) {
        if (component[to] == -1) {
            component_dfs(to, c);
        }
    }
}

vector<vector<int>> scc(int n) {
	component.assign(n, -1);
	visited.assign(n, false);

	for (int i {}; i < n; ++i) {
		if (!visited[i]) {
			ts_dfs(i);
		}
	}

	reverse(ts.begin(), ts.end());

    int comp {};

    for (int v : ts) {
        if (component[v] == -1) {
			same_comp.emplace_back();
			
            component_dfs(v, comp++);
        }
    }

	vector<vector<int>> cg(comp);

	for (int i {}; i < comp; ++i) {
		for (int u : same_comp[i]) {
			for (int to : g[u]) {
				if (component[u] != component[to]) {
					cg[i].push_back(component[to]);
				}
			}
		}
	}

	for (int i {}; i < comp; ++i) {
		sort(cg[i].begin(), cg[i].end());

		cg[i].erase(unique(cg[i].begin(), cg[i].end()), cg[i].end());
	}

	return cg;
}

int main() {
    int n, m;

    cin >> n >> m;

    g.assign(n, vector<int>());
    tg.assign(n, vector<int>());

    for (int i {}; i < m; ++i) {
        int a, b;

        cin >> a >> b;

        --a;
        --b;

        g[a].push_back(b);
        tg[b].push_back(a);
    }

    auto cg {scc(n)};

    if (cg.size() == 1) {
        cout << "YES\n";

        return 0;
    }

    int fc {-1};

    for (int i {}; i < (int) cg.size(); ++i) {
        if (cg[i].size() >= 1) {
            fc = i;

            break;
        }
    }

    if (fc == -1) {
        cout << "NO\n" << same_comp[0][0] << " " << same_comp[1][0] << '\n';

        return 0;
    }

    int sc {cg[fc][0]};

    int u {same_comp[sc][0]}, v {same_comp[fc][0]};

    cout << "NO\n" << u + 1 << " " << v + 1 << '\n';

    return 0;
}