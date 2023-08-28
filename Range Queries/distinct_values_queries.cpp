#include <bits/stdc++.h>
 
using namespace std;
 
typedef tuple<int, int, int> consult;
 
#define MAXN 2 * int(1e5) + 10
 
int n;
int BIT[MAXN];
 
void update(int idx, int v) {
    for (; idx <= n; idx += idx & -idx) {
        BIT[idx] += v;
    }
}
 
int query(int idx) {
    int ans {};
 
    for (; idx > 0; idx -= idx & -idx) {
        ans += BIT[idx];
    }
 
    return ans;
}
 
int range_query(int l, int r) {
    return query(r) - query(l - 1);
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
 
    int q;
 
    cin >> n >> q;
 
    vector<int> v(n);
 
    for (int &x : v) {
        cin >> x;
    }
 
    vector<consult> queries(q);
 
    for (size_t idx {}; auto &[r, l, i] : queries) {
        cin >> l >> r;
 
        i = idx++;
    }
 
    sort(queries.begin(), queries.end());
 
    int qidx {};
    unordered_map<int, int> last_viwed;
    vector<int> answers(q);
 
    for (int i {}; i < n; ++i) {
        int target {v[i]};
 
        if (last_viwed.count(target) == 1) {
            update(last_viwed[target], -1);
        }
 
        last_viwed[target] = i + 1;
 
        update(i + 1, 1);
 
        while (qidx < q && i + 1 == get<0>(queries[qidx])) {
            auto [r, l, idx] = queries[qidx];
 
            answers[idx] = range_query(l, r);
 
            ++qidx;
        }
    }
 
    for (int ans : answers) {
        cout << ans << "\n";
    }
 
    return 0;
}
