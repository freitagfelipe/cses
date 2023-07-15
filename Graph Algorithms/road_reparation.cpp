#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MAXN int(1e5) + 10

struct Edge {
    int u;
    int v;
    int w;

    Edge(int u, int v, int w) {
        this->u = u;
        this->v = v;
        this->w = w;
    }

    bool operator<(const Edge &e) const {
        return this->w < e.w;
    }
};

int n;
int p[MAXN], h[MAXN];
vector<Edge> edges;

int find(int x) {
    if (p[x] == x) {
        return x;
    }

    return p[x] = find(p[x]);
}

void join(int x, int y) {
    x = find(x);
    y = find(y);

    if (x == y) {
        return;
    }

    if (h[x] < h[y]) {
        swap(x, y);
    }

    p[y] = x;

    if (h[x] == h[y]) {
        ++h[x];
    }
}

pair<ll, bool> kruskal() {
    int edges_count {};
    ll cost {};

    for (int i {1}; i <= n; ++i) {
        p[i] = i;
    }

    sort(edges.begin(), edges.end());

    for (auto [u, v, w] : edges) {
        if (find(u) != find(v)) {
            join(u, v);

            cost += w;
            ++edges_count;
        }
    }

    return {cost, edges_count == n - 1};
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

    auto [cost, b] = kruskal();

    if (!b) {
        cout << "IMPOSSIBLE\n";

        return 0;
    }

    cout << cost << '\n';

    return 0;
}