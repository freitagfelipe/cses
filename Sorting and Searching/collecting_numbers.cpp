#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
 
    cin >> n;

    vector<int> pos(n + 1);

    for (int i {}; i < n; ++i) {
        int x;

        cin >> x;

        pos[x] = i;
    }

    int ans {1};

    for (int i {2}; i <= n; ++i) {
        if (pos[i - 1] > pos[i]) {
            ++ans;
        }
    }

    cout << ans << '\n';
 
    return 0;
}
