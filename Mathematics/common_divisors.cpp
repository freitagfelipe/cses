#include <bits/stdc++.h>

using namespace std;

#define MAXN int(1e6) + 10

int occ_nums[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    for (int i {}; i < n; ++i) {
        int x;

        cin >> x;

        ++occ_nums[x];
    }

    for (int gcd {MAXN}; gcd > 0; --gcd) {
        int div {};

        for (int j {gcd}; j <= MAXN; j += gcd) {
            div += occ_nums[j];

            if (div >= 2) {
                break;
            }
        }

        if (div >= 2) {
            cout << gcd << '\n';

            break;
        }
    }

    return 0;
}