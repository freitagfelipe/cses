#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long int n, sum {};

    cin >> n;

    for (int i {}; i < n - 1; ++i) {
        int x;

        cin >> x;

        sum += x;
    }

    cout << (n * (n + 1)) / 2 - sum << '\n';

    return 0;
}