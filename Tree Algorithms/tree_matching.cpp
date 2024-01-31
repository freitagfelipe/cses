#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;

pair<int, bool> dfs(int u, int p) {
    if (g[u].size() == 1 && p != -1) {
        return {0, false};
    }

    int ans {};
    bool used {};

    for (int to : g[u]) {
        if (to == p) {
            continue;
        }

        auto [c_ans, b] {dfs(to, u)};

        ans += c_ans;

        if (!b && !used) {
            used = true;

            ans += 1;
        }
    }

    return {ans, used};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    g.assign(n, vector<int>());

    for (int i {}; i < n - 1; ++i) {
        int u, v;

        cin >> u >> v;

        --u;
        --v;
        
        g[u].push_back(v);
        g[v].push_back(u);
    }

    cout << dfs(0, -1).first << '\n';

    return 0;
}
