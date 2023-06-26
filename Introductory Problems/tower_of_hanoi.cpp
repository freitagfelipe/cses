#include <bits/stdc++.h>

using namespace std;

int fast_exponentiation(int b, int e) {
    if (e == 0) {
        return 1;
    }

    int ans {fast_exponentiation(b, e / 2)};

    ans *= ans;

    if (e & 1) {
        ans *= b;
    }

    return ans;
}

void tower_of_hanoi(int n, int start, int aux, int end) {
    if (n == 0) {
        return;
    }

    tower_of_hanoi(n - 1, start, end, aux);

    cout << start << " " << end << '\n';

    tower_of_hanoi(n - 1, aux, start, end);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    cout << fast_exponentiation(2, n) - 1 << '\n';

    tower_of_hanoi(n, 1, 2, 3);

    return 0;
}