#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool ok(ll t, ll p, const vector<ll> &v) {
    ll can_do {};
    
    for (ll x : v) {
        can_do += t / x;
    }
    
    return can_do >= p;
}

int main() {
    ll n, p;
    
    cin >> n >> p;
    
    vector<ll> v(n);
    
    for (ll &x : v) {
        cin >> x;
    }
    
    ll lo {1}, hi {1};
    
    while (!ok(hi, p, v)) {
        hi *= 2;
    }
    
    ll ans {};
    
    while (lo <= hi) {
        ll mid {(lo + hi) / 2};
        
        if (ok(mid, p, v)) {
            ans = mid;
            
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    
    cout << ans << '\n';
    
    return 0;
}