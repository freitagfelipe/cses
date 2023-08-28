#include <bits/stdc++.h>

using namespace std;

#define MAXN int(1e5)

typedef pair<int, int> pii;

int n, m;
// MAXN is the largest possible number of nodes
vector<pii> g[MAXN];
vector<int> path, stage(MAXN);
vector<bool> used;

template <bool directed = false>
void add_edge(int u, int v) {
	int idx {(int) used.size()};

    used.emplace_back();

	g[u].emplace_back(v, idx);

	if (!directed) {
	    g[v].emplace_back(u, idx);
	}
}

void dfs(int u) {
    stack<int> s;

    s.push(u);

    while (!s.empty()) {
        int curr {s.top()};

        if (stage[curr] < (int) g[curr].size()) {
            auto [to, idx] = g[curr][stage[curr]];

            ++stage[curr];

            if (!used[idx]) {
                used[idx] = true;

                s.push(to);
            }
        } else {
            path.push_back(curr);

            s.pop();
        }
    }
}

bool directed_eulerian_path(int s, int e, bool is_cycle) {
    vector<int> in_degree(n, 0), out_degree(n, 0);

    for (int i {}; i < n; ++i) {
        out_degree[i] = g[i].size();

        for (auto [to, _] : g[i]) {
            ++in_degree[to];
        }
    }

    int odd_c {};

    for (int i {}; i < n; ++i) {
        if (is_cycle && in_degree[i] != out_degree[i]) {
            return false;
        }

        if (!is_cycle && abs(in_degree[i] - out_degree[i]) > 1) {
            return false;
        }

        odd_c += abs(in_degree[i] - out_degree[i]) == 1;
    }

    if (!is_cycle && odd_c > 2) {
        return false;
    } else if (!is_cycle && (out_degree[s] - in_degree[s] != 1 || in_degree[e] - out_degree[e] != 1)) {
        return false;
    }

	dfs(s);

	if ((int) path.size() != m + 1) {
		return false;
	}

	reverse(path.begin(), path.end());

	return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    for (int i {}; i < m; ++i) {
        int u, v;

        cin >> u >> v;

        --u;
        --v;

        add_edge<true>(u, v);
    }

    bool ans {directed_eulerian_path(0, n - 1, false)};

    if (!ans) {
        cout << "IMPOSSIBLE\n";

        return 0;
    }

    for (size_t i {}; int v : path) {
        cout << v + 1 << " \n"[++i == path.size()];
    }

    return 0;
}
