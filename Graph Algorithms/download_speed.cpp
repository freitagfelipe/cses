#include <bits/stdc++.h>

using namespace std;

#define INF LONG_LONG_MAX
#define MAXN 510

typedef long long ll;
typedef pair<int, ll> pil;

int n;
vector<int> g[MAXN];
vector<vector<ll>> capacity;

ll bfs(int s, int t, vector<int>& p) {
    fill(p.begin(), p.end(), -1);

    p[s] = -2;

    queue<pil> q;

    q.push({s, INF});

    while (!q.empty()) {
        auto [curr, flow] {q.front()};
        
        q.pop();

        for (int to : g[curr]) {
            if (p[to] == -1 && capacity[curr][to]) {
                p[to] = curr;

                ll new_flow {min(flow, capacity[curr][to])};

                if (to == t) {
                    return new_flow;
                }

                q.push({to, new_flow});
            }
        }
    }

    return 0;
}

ll max_flow(int s, int t) {
    ll flow {};
    ll new_flow {};
    vector<int> p(n + 1);

    while ((new_flow = bfs(s, t, p))) {
        flow += new_flow;

        int curr {t};

        while (curr != s) {
            int prev {p[curr]};

            capacity[prev][curr] -= new_flow;
            capacity[curr][prev] += new_flow;

            curr = prev;
        }
    }

    return flow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int m;

    cin >> n >> m;

    capacity.assign(n + 1, vector<ll>(n + 1));

    for (int i {}; i < m; ++i) {
        int u, v, c;

        cin >> u >> v >> c;

        g[u].push_back(v);
        g[v].push_back(u);
        capacity[u][v] += c;
    }

    cout << max_flow(1, n) << '\n';

    return 0;
}
