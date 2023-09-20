#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    int ans {};

    for (int i {5}; n / i >= 1; i *= 5) {
        ans += n / i;
    }

    cout << ans << '\n';

    return 0;
}
