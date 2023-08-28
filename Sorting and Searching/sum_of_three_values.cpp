#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n, k;
 
    cin >> n >> k;
 
    vector<pii> v(n);
    unordered_map<int, int> ump;
 
    for (size_t i {}; auto &[v, idx] : v) {
        cin >> v;
 
        ump[k - v] = idx = i++;
    }
 
    sort(v.begin(), v.end());
 
    for (auto [val, idx] : ump) {
        int p1 {}, p2 {n - 1};
 
        while (p1 < p2) {
            if (v[p1].second == idx) {
                ++p1;
 
                continue;
            } else if (v[p2].second == idx) {
                --p2;
 
                continue;
            }
 
            ll sum {v[p1].first + v[p2].first};
 
            if (sum == val) {
                cout << v[p1].second + 1 << " " << v[p2].second + 1 << " " << idx + 1 << '\n';
                
                return 0;
            } else if (sum < val) {
                ++p1;
            } else {
                --p2;
            }
        }
    }
 
    cout << "IMPOSSIBLE\n";
 
    return 0;
}
