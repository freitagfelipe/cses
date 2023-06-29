#include <bits/stdc++.h>

using namespace std;

#define MAXN 2 * int(1e5) + 10

vector<int> g[MAXN];
int subordinates_count[MAXN];

int dfs(int u, int p = -1) {
    for (int to : g[u]) {
        if (to != p) {
            subordinates_count[u] += dfs(to, u);
        }
    }

    return subordinates_count[u] + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    for (int i {2}; i <= n; ++i) {
        int u;
        
        cin >> u;

        g[u].push_back(i);
        g[i].push_back(u);
    }

    dfs(1);

    for (int i {1}; i <= n; ++i) {
        cout << subordinates_count[i] << " \n"[i == n];
    }

    return 0;
}