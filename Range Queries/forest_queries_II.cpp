#include <bits/stdc++.h>
 
using namespace std;
 
#define MAXN 1010
 
int n;
int BIT[MAXN][MAXN];
 
void update(int idx, int idy, int x) {
    for (int i {idx}; i <= n; i += i & -i) {
        for (int y {idy}; y <= n; y += y & -y) {
            BIT[i][y] += x;
        }
    }
}
 
int query(int idx, int idy) {
    int ans {};
 
    for (int i {idx}; i > 0; i -= i & -i) {
        for (int y {idy}; y > 0; y -= y & -y) {
            ans += BIT[i][y];
        }
    }
 
    return ans;
}
 
int range_query(int ix, int iy, int ex, int ey) {
    int ans {};
 
    ans += query(ex, ey);
    ans -= query(ex, iy - 1);
    ans -= query(ix - 1, ey);
    ans += query(ix - 1, iy - 1);
 
    return ans;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
 
    int q;
 
    cin >> n >> q;
 
    vector<vector<bool>> state(n + 1, vector<bool>(n + 1));
 
    for (int i {1}; i <= n; ++i) {
        for (int j {1}; j <= n; ++j) {
            char ch;
 
            cin >> ch;
 
            update(i, j, ch == '*');
 
            state[i][j] = ch == '*';
        }
    }
 
    while (q--) {
        int op;
 
        cin >> op;
 
        if (op == 1) {
            int x, y;
 
            cin >> x >> y;
 
            update(x, y, state[x][y] ? -1 : 1);
 
            state[x][y] = !state[x][y];
        } else {
            int ix, iy, ex, ey;
 
            cin >> ix >> iy >> ex >> ey;
 
            cout << range_query(ix, iy, ex, ey) << '\n';
        }
    }
 
    return 0;
}
