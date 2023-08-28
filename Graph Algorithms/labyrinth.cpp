#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

#define MAXN 1010

int n, m;
char mat[MAXN][MAXN];
int di[] = {1, -1, 0, 0};
int dj[] = {0, 0, 1, -1};
vector<char> path;
vector<vector<int>> dist(MAXN, vector<int>(MAXN, -1));
pii start, finish;

bool is_valid(int i, int j) {
    if (i < 0 || j < 0 || i >= n || j >= m || mat[i][j] == '#' || dist[i][j] != -1) {
        return false;
    }

    return true;
}

bool bfs(int i, int j) {
    queue<pii> q;

    q.push({i, j});

    dist[i][j] = 0;

    while (!q.empty()) {
        auto [ci, cj] {q.front()};

        q.pop();

        if (make_pair(ci, cj) == finish) {
            return true;
        }

        for (int k {}; k < 4; ++k) {
            int ni {ci + di[k]};
            int nj {cj + dj[k]};

            if (is_valid(ni, nj)) {
                q.push({ni, nj});

                dist[ni][nj] = dist[ci][cj] + 1;
            }
        }
    }

    return false;
}

void make_path() {
    pii current {finish};

    while (current != start) {
        auto [ci, cj] {current};

        int k_move {};

        for (int k {}; k < 4; ++k) {
            int ni {ci + di[k]};
            int nj {cj + dj[k]};

            if (ni < 0 || nj < 0 || ni >= n || nj >= m) {
                continue;
            }

            if (dist[ci][cj] - dist[ni][nj] == 1) {
                current = {ni, nj};
                k_move = k;

                break;
            }
        }
        
        if (k_move == 0) {
            path.push_back('U');
        } else if (k_move == 1) {
            path.push_back('D');
        } else if (k_move == 2) {
            path.push_back('L');
        } else {
            path.push_back('R');
        }
    }

    reverse(path.begin(), path.end());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    
    for (int i {}; i < n; ++i) {
        for (int j {}; j < m; ++j) {
            cin >> mat[i][j];

            if (mat[i][j] == 'A') {
                start = {i, j};
            } else if (mat[i][j] == 'B') {
                finish = {i, j};
            }
        }
    }

    bool ans {bfs(start.first, start.second)};

    if (!ans) {
        cout << "NO\n";

        return 0;
    }

    make_path();

    cout << "YES\n" << path.size() << '\n';

    for (char ch : path) {
        cout << ch;
    }

    cout << '\n';

    return 0;
}
