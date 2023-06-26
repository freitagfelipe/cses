#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll fast_exponentiation(ll b, ll e, int m) {
    if (e == 0) {
        return 1 % m; 
    }

    ll answer {fast_exponentiation(b, e / 2, m)};

    answer = (answer * answer) % m;

    if (e & 1) {
        answer *= b;
    }

    return answer % m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int q;

    cin >> q;

    while (q--) {
        int b, e;

        cin >> b >> e;
        
        cout << fast_exponentiation(b, e, int(1e9 + 7)) << '\n';
    }

    return 0;
}