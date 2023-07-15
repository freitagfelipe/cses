#include <bits/stdc++.h>

using namespace std;

#define MAXN int(1e5) + 10

int n;
vector<int> g[MAXN];
int in_degree[MAXN];

vector<int> topological_sort() {
    for (int i {}; i < n; ++i) {
        for (int to : g[i]) {
            ++in_degree[to];
        }
    }

    queue<int> q;

    for (int i {}; i < n; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> ans;

    while (!q.empty()) {
        int curr {q.front()};

        q.pop();

        ans.push_back(curr);

        for (int to : g[curr]) {
            if (--in_degree[to] == 0) {
                q.push(to);
            }
        }
    }

    if ((int) ans.size() != n) {
        return {};
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int m;

    cin >> n >> m;

    for (int i {}; i < m; ++i) {
        int u, v;

        cin >> u >> v;

        --u;
        --v;

        g[u].push_back(v);
    }

    vector<int> ts {topological_sort()};

    if (ts.size() == 0) {
        cout << "IMPOSSIBLE\n";
    }

    for (size_t i {}; int v : ts) {
        cout << v + 1 << " \n"[++i == ts.size()];
    }

    return 0;
}