#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    long long int n;

    cin >> n;

    while (n != 1) {
        cout << n << " ";

        if (n & 1) {
            n *= 3;

            ++n;
        } else {
            n /= 2;
        }
    }

    cout << 1 << '\n';

    return 0;
}