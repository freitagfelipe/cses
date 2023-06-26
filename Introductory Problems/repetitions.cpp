#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;

    cin >> s;

    int p1 {}, p2 {}, n {(int) s.size()}, ans {1};

    while (p1 < n && p2 < n) {
        if (p2 + 1 == n || s[p1] != s.at(p2 + 1)) {
            ans = max(ans, p2 - p1 + 1); 
           
            p1 = p2 + 1;
        }

        ++p2;
    }

    cout << ans << '\n';

    return 0;
}