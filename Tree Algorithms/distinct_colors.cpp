#include <bits/stdc++.h>

using namespace std;

#define MAXN int(2e5 + 10)

vector<int> g[MAXN], ans, colors;
set<int> distinct_colors[MAXN];

void dfs(int u, int p = -1) {
    distinct_colors[u].insert(colors[u]);

    for (int to : g[u]) {
        if (to == p) {
            continue;
        }

        dfs(to, u);

        if (distinct_colors[to].size() > distinct_colors[u].size()) {
            distinct_colors[u].swap(distinct_colors[to]);
        }

        for (int x : distinct_colors[to]) {
            distinct_colors[u].insert(x);
        }
    }

    ans[u] = (int) distinct_colors[u].size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    ans.assign(n, 0);
    colors.assign(n, 0);

    for (int &x : colors) {
        cin >> x;
    }

    for (int i {}; i < n - 1; ++i) {
        int u, v;

        cin >> u >> v;

        --u;
        --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(0);

    for (size_t i {}; int x : ans) {
        cout << x << " \n"[++i == ans.size()];
    }

    return 0;
}