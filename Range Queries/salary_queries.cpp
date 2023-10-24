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

    int n, q;

    cin >> n >> q;

    vector<int> v(n);

    ordered_set<pii> os;

    for (size_t i {}; int &x : v) {
        cin >> x;

        os.insert({x, ++i});
    }

    while (q--) {
        char op;

        cin >> op;

        if (op == '!') {
            int k, x;

            cin >> k >> x;

            auto it {os.lower_bound({v[k - 1], k})};
            auto [val, idx] {*it};

            os.erase(it);

            os.insert({v[k - 1] = x, idx});
        } else {
            int a, b;

            cin >> a >> b;

            cout << os.order_of_key({b + 1, 0}) -  os.order_of_key({a, 0}) << '\n';
        }
    }

    return 0;
}
