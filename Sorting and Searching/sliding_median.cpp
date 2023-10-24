#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef pair<int, int> pii;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;

    cin >> n >> k;

    ordered_set<pii> os;

    vector<int> v(n);
    vector<int> ans;

    for (int i {}; i < n; ++i) {
        int x;

        cin >> x;

        os.insert({x, i});
        v[i] = x;

        if (i >= k) {
            os.erase(os.lower_bound({v[i - k], 0}));
        }

        if (i >= k - 1) {
            ans.push_back(os.find_by_order((k - 1) / 2)->first);
        }
    }

    for (size_t i {}; int x : ans) {
        cout << x << " \n"[++i == ans.size()];
    }

    return 0;
}
