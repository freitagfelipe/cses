#include <bits/stdc++.h>

using namespace std;

#define MAXN int(1e5) + 10

vector<int> g[MAXN], color(MAXN, -1);

bool dfs(int u, int c = 0) {
    color[u] = c;

    for (int to : g[u]) {
        if (color[to] == -1 && !dfs(to, 1 - c)) {
            return false;
        } else if (color[to] == c) {
            return false;
        }
    }

    return true;
}

bool solver(int n) {
    for (int i {1}; i <= n; ++i) {
        if (color[i] == -1 && !dfs(i)) {
            return false;
        }
    }

    return true;
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

    bool ans {solver(n)};

    if (!ans) {
        cout << "IMPOSSIBLE\n";

        return 0;
    }

    for (int i {1}; i <= n; ++i) {
        cout << color[i] + 1 << " \n"[i == n];
    }


    return 0;
}
