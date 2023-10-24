#include <bits/stdc++.h>

using namespace std;

#define MOD int(1e9 + 7)

typedef long long ll;

pair<ll, ll> fibonacci(ll n, ll m) {
    if (n == 0) {
        return {0, 1};
    }

    auto [f, s] {fibonacci(n >> 1, m)};

    ll c {(f * (2 * s - f + m)) % m};
    ll d {((f * f) % m + (s * s) % m) % m};

    if (n & 1) {
        return {d, (c + d) % m};
    }

    return {c, d};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;

    cin >> n;

    cout << fibonacci(n, MOD).first << '\n';

    return 0;
}
