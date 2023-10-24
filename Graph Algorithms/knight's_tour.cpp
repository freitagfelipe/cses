#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int di[] {-2, -2, 2, 2, 1, -1, 1, -1};
int dj[] {1, -1, 1, -1, -2, -2, 2, 2};
int ans[8][8];

bool is_valid_cell(int i, int j) {
    if (i < 0 || i >= 8 || j < 0 || j >= 8 || ans[i][j] != 0) {
        return false;
    }
    
    return true;
}

int degree(pii cell) {
    auto [i, j] {cell};
    int d {};

    for (int k {}; k < 8; ++k) {
        d += is_valid_cell(i + di[k], j + dj[k]);
    }

    return d;
}

bool solver(int i, int j, int counter = 1) {
    ans[i][j] = counter;

    if (counter == 64) {
        return true;
    }

    vector<pii> jumps;

    for (int k {}; k < 8; ++k) {
        int ni {i + di[k]};
        int nj {j + dj[k]};

        if (is_valid_cell(ni, nj)) {
            jumps.emplace_back(ni, nj);
        }
    }

    sort(jumps.begin(), jumps.end(), [](const pii &a, const pii &b) {
        return degree(a) < degree(b);
    });

    bool has_ans {};

    for (auto [ni, nj] : jumps) {
        has_ans |= solver(ni, nj, counter + 1);

        if (has_ans) {
            break;
        }
    }

    if (!has_ans) {
        ans[i][j] = 0;
    }

    return has_ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int x, y;

    cin >> x >> y;

    solver(y - 1, x - 1);

    for (int i {}; i < 8; ++i) {
        for (int j {}; j < 8; ++j) {
            cout << ans[i][j] << " \n"[j + 1 == 8];
        }
    }

    return 0;
}
