#include <bits/stdc++.h>

using namespace std;

#define MAXN int(1e5) + 10

int n;
vector<int> g[MAXN], p(MAXN, -1), path;
bitset<MAXN> visited;

void bfs(int s) {
    queue<int> q;

    p[s] = s;

    q.push(s);

    while (!q.empty()) {
        int c {q.front()};

        q.pop();

        for (int to : g[c]) {
            if (p[to] != -1) {
                continue;
            }

            p[to] = c;

            q.push(to);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int m;

    cin >> n >> m;    

    for (int i {}; i < m; ++i) {
        int u, v;

        cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    bfs(1);

    if (p[n] == -1) {
        cout << "IMPOSSIBLE\n";

        return 0;
    }

    path.push_back(n);

    while (p[path.back()] != path.back()) {
        path.push_back(p[path.back()]);
    }

    cout << path.size() << '\n';

    reverse(path.begin(), path.end());

    for (size_t i {}; int v : path) {
        cout << v << " \n"[++i == path.size()];
    }

    return 0;
}
