#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;
    
    for (int i {}; i < n; ++i) {
        int ci, cj;

        cin >> ci >> cj;

        ll diagonal_pos {max(ci, cj)};
        ll diagonal_value {diagonal_pos == 1 ? 1 : diagonal_pos * diagonal_pos - (diagonal_pos - 1)};

        if (ci == diagonal_pos) {
            cout << (diagonal_pos & 1 ? diagonal_value - (diagonal_pos - cj) : diagonal_value + (diagonal_pos - cj)) << '\n';
        } else {
            cout << (diagonal_pos & 1 ? diagonal_value + (diagonal_pos - ci) : diagonal_value - (diagonal_pos - ci)) << '\n';
        }
    }

    return 0;
}
