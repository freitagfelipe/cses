#include <bits/stdc++.h>

using namespace std;

typedef pair<bool, vector<int>> pbvi;
typedef long long ll;

#define MAXN 2510

struct Edge {
    int u;
    int v;
    ll w;
};

int n;
ll dist[MAXN];
vector<Edge> edges;

pbvi bellman_ford() {
	vector<int> p(n + 1);
	int x {-1};

    for (int i {}; i < n; ++i) {
        x = -1;

        for (auto [u, v, w] : edges) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                p[v] = u;
                x = v;
            }
        }
    }

	if (x == -1) {
		return {false, {}};
	}

	for (int i {}; i < n; ++i) {
		x = p[x];
	}

	vector<int> cycle;

	for (int u {x};; u = p[u]) {
		cycle.push_back(u);

		if (u == x && cycle.size() > 1) {
			break;
		}
	}

	reverse(cycle.begin(), cycle.end());

	return {true, cycle};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int m;

    cin >> n >> m;

    for (int i {}; i < m; ++i) {
        int u, v, w;

        cin >> u >> v >> w;

        edges.emplace_back(u, v, w);
    }

    auto [b, v] {bellman_ford()};

    if (!b) {
        cout << "NO\n";

        return 0;
    }

    cout << "YES\n";

    for (size_t i {}; int u : v) {
        cout << u << " \n"[++i == v.size()];
    }

    return 0;
}
