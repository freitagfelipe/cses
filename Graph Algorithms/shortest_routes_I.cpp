#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

#define MAXN int(1e5) + 10
#define INF LONG_LONG_MAX

int n;
ll dist[MAXN];
vector<pll> g[MAXN];
bitset<MAXN> marked;

void dijkstra(int s) {
    for (int i {}; i < n; ++i) {
        dist[i] = INF;
    }

    priority_queue<pll, vector<pll>, greater<pll>> pq;

    dist[s] = 0;

    pq.push({0, s});

    while (!pq.empty()) {
        ll curr {pq.top().second};

        pq.pop();

        if (marked[curr]) {
            continue;
        }

        marked[curr] = true;

        for (auto [w, to] : g[curr]) {
            if (dist[curr] + w < dist[to]) {
                dist[to] = dist[curr] + w;

                pq.push({dist[to], to});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int m;

    cin >> n >> m;

    for (int i {}; i < m; ++i) {
        int u, v, w;

        cin >> u >> v >> w;

        --u;
        --v;

        g[u].emplace_back(w, v);
    }

    dijkstra(0);

    for (int i {}; i < n; ++i) {
        cout << dist[i] << " \n"[i + 1 == n];
    }

    return 0;
}