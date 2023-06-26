#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MAXN 510
#define INF LONG_LONG_MAX

ll DP[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;

    cin >> n >> m >> q;

    for (int i {1}; i <= n; ++i) {
        for (int j {1}; j <= n; ++j) {
            if (i == j) {
                DP[i][j] = 0;
            } else {
                DP[i][j] = INF;
            }
        }
    }

    for (int i {}; i < m; ++i) {
        ll u, v, w;

        cin >> u >> v >> w;

        DP[u][v] = min(DP[u][v], w);
        DP[v][u] = min(DP[v][u], w);
    }

    for (int k {1}; k <= n; ++k) {
        for (int i {1}; i <= n; ++i) {
            for (int j {1}; j <= n; ++j) {
                if (DP[i][k] < INF && DP[k][j] < INF) {
                    DP[i][j] = min(DP[i][j], DP[i][k] + DP[k][j]);
                }
            }
        }
    }

    while (q--) {
        int u, v;

        cin >> u >> v;

        if (DP[u][v] == INF) {
            cout << -1 << '\n';
        } else {
            cout << DP[u][v] << '\n';
        }
    }

    return 0;
}