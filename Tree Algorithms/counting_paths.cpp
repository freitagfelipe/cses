#include <bits/stdc++.h>

using namespace std;

#define MAXN int(2e5 + 10)

int n;
vector<int> g[MAXN], p, depth, heavy, head, pos, sz;
int curr_pos;
int BIT[MAXN];

void update(int idx, int x) {
    for (; idx <= n; idx += idx & -idx) {
        BIT[idx] += x;
    }
}

void range_update(int l, int r, int x) {
    update(l, x);
    update(r + 1, -x);
}

int point_query(int idx) {
    int ans {};

    for (; idx > 0; idx -= idx & -idx) {
        ans += BIT[idx];
    }

    return ans;
}

int dfs(int u) {
    sz[u] = 1;
    int max_to_size {};

    for (int to : g[u]) {
        if (to != p[u]) {
            p[to] = u;
            depth[to] = depth[u] + 1;
            
            int to_size {dfs(to)};

            sz[u] += to_size;

            if (to_size > max_to_size) {
                max_to_size = to_size;
                heavy[u] = to;
            }
        }
    }

    return sz[u];
}

void decompose(int u, int h) {
    head[u] = h;
    pos[u] = ++curr_pos;

    if (heavy[u] != -1) {
        decompose(heavy[u], h);
    }

    for (int to : g[u]) {
        if (to != p[u] && to != heavy[u]) {
            decompose(to, to);
        }
    }
}

// The graph must be 0-indexed
// The positions of each vertex will be 1-indexed for future data structure uses
void build(int root, int n) {
    p.assign(n, -1);
    heavy.assign(n, -1);
    depth.assign(n, 0);
    head.assign(n, 0);
    pos.assign(n, 0);
    sz.assign(n, 0);

    curr_pos = 0;

    dfs(root);
    decompose(root, root);
}

void update_path(int u, int v, int x) {
    if (pos[u] < pos[v]) {
        swap(u, v);
    }

    if (head[u] == head[v]) {
        range_update(pos[v], pos[u], x);

        return;
    }

    range_update(pos[head[u]], pos[u], x);
    
    update_path(p[head[u]], v, x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int m;

    cin >> n >> m;

    for (int i {}; i < n - 1; ++i) {
        int u, v;

        cin >> u >> v;

        --u;
        --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    build(0, n);

    while (m--) {
        int u, v;

        cin >> u >> v;

        --u;
        --v;

        update_path(u, v, 1);

    }

    for (int i {}; i < n; ++i) {
        cout << point_query(pos[i]) << " \n"[i + 1 == n];
    }

    return 0;
}
