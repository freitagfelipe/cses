#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n;
    
    cin >> n;
 
    vector<int> v(n);
 
    for (int &x : v) {
        cin >> x;
    }
 
    sort(v.begin(), v.end());
 
    int target {v[(v.size() - 1) / 2]};
    long long int ans {};
 
    for (int x : v) {
        ans += abs(target - x);
    }
 
    cout << ans << '\n';
 
    return 0;
}
