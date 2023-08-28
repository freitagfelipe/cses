#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

#define MAXN int(1e5) + 10

vector<int> g[MAXN];
bitset<MAXN> visited;
vector<pii> comps;

void dfs(int u, int c) {
    visited[u] = true;
    
    if (comps.size() == 0 || comps.back().first != c) {
        comps.emplace_back(c, u);
    }

    for (int to : g[u]) {
        if (!visited[to]) {
            dfs(to, c);
        }
    }
}

int cc(int n) {
    int comp {};

    for (int i {1}; i <= n; ++i) {
        if (!visited[i]) {
            dfs(i, comp);

            ++comp;
        }
    }

    return comp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;

    cin >> n >> m;

    for (int i {}; i < m; ++i) {
        int u, v;

        cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    cout << cc(n) - 1 << '\n';

    for (int i {1}; i < (int) comps.size(); ++i) {
        cout << comps[i - 1].second << " " << comps[i].second << '\n';
    }

    return 0;
}
