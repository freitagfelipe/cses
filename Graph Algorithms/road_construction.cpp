#include <bits/stdc++.h>

using namespace std;

#define MAXN int(1e5) + 10

int p[MAXN], h[MAXN];
int weight[MAXN];

int find(int x) {
    if (p[x] == x) {
        return x;
    }

    return p[x] = find(p[x]);
}

pair<int, bool> join(int x, int y) {
    x = find(x);
    y = find(y);

    if (x == y) {
        return {0, false};
    }

    if (h[x] < h[y]) {
        swap(x, y);
    }

    p[y] = x;
    weight[x] += weight[y];

    if (h[x] == h[y]) {
        ++h[x];
    }

    return {weight[x], true};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t;

    cin >> n >> t;

    for (int i {1}; i <= n; ++i) {
        p[i] = i;
        h[i] = 0;
        weight[i] = 1;
    }

    int num_of_comps {n}, largest {1};

    while (t--) {
        int u, v;

        cin >> u >> v;

        auto [s, b] = join(u, v);

        if (b) {
            --num_of_comps;
            largest = max(largest, s);
        }

        cout << num_of_comps << " " << largest << '\n';
    }

    return 0;
}