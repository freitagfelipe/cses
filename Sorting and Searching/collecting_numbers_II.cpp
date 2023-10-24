#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;

    cin >> n >> q;

    vector<int> v(n), pos(n + 1);

    for (size_t i {}; int &x : v) {
        cin >> x;

        pos[x] = i++;
    }

    int ans {1};

    for (int i {1}; i <= n; ++i) {
        if (pos[i - 1] > pos[i]) {
            ++ans;
        }
    }

    while (q--) {
        int a, b;

        cin >> a >> b;

        --a;
        --b;

        set<pii> s;

        if (v[a] + 1 <= n) {
            s.emplace(v[a], v[a] + 1);
        }

        if (v[a] - 1 >= 1) {
            s.emplace(v[a] - 1, v[a]);
        }

        if (v[b] + 1 <= n) {
            s.emplace(v[b], v[b] + 1);
        }

        if (v[b] - 1 >= 1) {
            s.emplace(v[b] - 1, v[b]);
        }

        for (auto [f, s] : s) {
            if (pos[f] > pos[s]) {
                --ans;
            }
        }

        swap(pos[v[a]], pos[v[b]]);
        swap(v[a], v[b]);

        for (auto [f, s] : s) {
            if (pos[f] > pos[s]) {
                ++ans;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
