#include <bits/stdc++.h>

using namespace std;

#define MAXN 1010

int n, m;
string g[MAXN];
int di[] = {-1, 1, 0, 0};
int dj[] = {0, 0, 1, -1};

bool is_valid(int i, int j) {
    if (i < 0 || j < 0) {
        return false;
    } else if (i >= n || j >= m) {
        return false;
    } else if (g[i][j] != '.') {
        return false;
    }

    return true;
}

void dfs(int i, int j) {
    g[i][j] = '!';

    for (int k {}; k < 4; ++k) {
        int ni {i + di[k]}, nj {j + dj[k]};

        if (is_valid(ni, nj)) {
            dfs(ni, nj);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    for (int i {}; i < n; ++i) {
        cin >> g[i];
    }

    int comp {};

    for (int i {}; i < n; ++i) {
        for (int j {}; j < m; ++j) {
            if (g[i][j] == '.') {
                dfs(i, j);

                ++comp;
            }
        }
    }

    cout << comp << '\n';

    return 0;
}