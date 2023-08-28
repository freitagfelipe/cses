#include <bits/stdc++.h>
 
using namespace std;
 
#define MAXN 1010
 
int PSM[MAXN][MAXN];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n, q;
 
    cin >> n >> q;
 
    for (int i {1}; i <= n; ++i) {
        for (int j {1}; j <= n; ++j) {
            char ch;
 
            cin >> ch;
 
            PSM[i][j] = PSM[i - 1][j] + PSM[i][j - 1] - PSM[i - 1][j - 1] + (ch == '*');
        }
    }
 
    while (q--) {
        int ix, iy, ex, ey;
 
        cin >> ix >> iy >> ex >> ey;
 
        int result {};
 
        result += PSM[ex][ey];
        result -= PSM[ix - 1][ey];
        result -= PSM[ex][iy - 1];
        result += PSM[ix - 1][iy - 1];
 
        cout << result << '\n';
    }
 
    return 0;
}
