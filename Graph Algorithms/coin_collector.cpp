#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<int>> g, tg, same_comp;
vector<ll> coins, comp_to_value;
vector<int> ts, comps;
vector<bool> visited;

void ts_dfs(int u) {
    visited[u] = true;

    for (int to : g[u]) {
        if (visited[to]) {
            continue;
        }

        ts_dfs(to);
    }

    ts.push_back(u);
}

void comp_dfs(int u, int comp) {
    comps[u] = comp;
    same_comp[comp].push_back(u);
    comp_to_value[comp] += coins[u];

    for (int to : tg[u]) {
        if (comps[to] != -1) {
            continue;
        }

        comp_dfs(to, comp);
    }
}

vector<vector<int>> scc(int n) {
    for (int i {}; i < n; ++i) {
        if (!visited[i]) {
            ts_dfs(i);
        }
    }

    reverse(ts.begin(), ts.end());

    int comps_count {};

    for (int u : ts) {
        if (comps[u] == -1) {
            same_comp.emplace_back();
            comp_to_value.emplace_back();

            comp_dfs(u, comps_count++);
        }
    }

    vector<vector<int>> cg(comps_count);

    for (int i {}; i < comps_count; ++i) {
        for (int u : same_comp[i]) {
            for (int to : g[u]) {
                if (comps[u] != comps[to]) {
                    cg[i].push_back(comps[to]);
                }
            }
        }
    }

    for (vector<int> &l : cg) {
        sort(l.begin(), l.end());

        l.erase(unique(l.begin(), l.end()), l.end());
    }

    return cg;
}

ll dfs(int u, vector<ll> &calc, vector<vector<int>> &cg) {
    if (calc[u] != 0) {
        return calc[u];
    }

    ll ans {};

    for (int to : cg[u]) {
        ans = max(ans, dfs(to, calc, cg));
    }

    return calc[u] = ans + comp_to_value[u];
}

void setup(int n) {
    g.assign(n, vector<int>());
    tg.assign(n, vector<int>());
    coins.assign(n, 0);
    visited.assign(n, false);
    comps.assign(n, -1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;

    cin >> n >> m;

    setup(n);

    for (ll &x : coins) {
        cin >> x;
    }

    for (int i {}; i < m; ++i) {
        int u, v;

        cin >> u >> v;

        --u;
        --v;

        g[u].push_back(v);
        tg[v].push_back(u);
    }

    vector<vector<int>> cg {scc(n)};
    vector<ll> calc(cg.size());

    ll ans {};

    for (int comp {}; comp < (int) cg.size(); ++comp) {
        ans = max(ans, dfs(comp, calc, cg));
    }

    cout << ans << '\n';

    return 0;
}