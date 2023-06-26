#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    long long int ans {};
    int n, last_n;

    cin >> n >> last_n;

    for (int i {1}; i < n; ++i) {
        int x;

        cin >> x;

        if (last_n > x) {
            ans += last_n - x;

            x = last_n;
        }

        last_n = x;        
    }

    cout << ans << '\n';

    return 0;
}