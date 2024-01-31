#include <bits/stdc++.h>

using namespace std;

#define MAXN int(2e5 + 10)

typedef long long ll;
typedef pair<int, ll> pii;

int n;
vector<int> g[MAXN], sz;
vector<ll> ans;

pii preprocessor(int u, int d, int p = -1) {
    sz[u] = 1;
    ans[u] = d;

    for (int to : g[u]) {
        if (to == p) {
            continue;
        }

        auto [csz, cans] {preprocessor(to, d + 1, u)};

        sz[u] += csz;
        ans[u] += cans;
    }

    return {sz[u], ans[u]};
}

void solver(int u, int p = -1) {
    if (p != -1) {
        ans[u] = ans[p] - sz[u] + (n - sz[u]);
    }

    for (int to : g[u]) {
        if (to == p) {
            continue;
        }

        solver(to, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    sz.assign(n, 0);
    ans.assign(n, 0);

    for (int i {}; i < n - 1; ++i) {
        int u, v;

        cin >> u >> v;

        --u;
        --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    preprocessor(0, 0);

    solver(0);

    for (int i {}; i < n; ++i) {
        cout << ans[i] << " \n"[i + 1 == n];
    }

    return 0;
}
