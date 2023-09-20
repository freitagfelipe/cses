#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
ll DP[19][10][2][2][2][2];
 
ll solver(int idx, int last_digit, bool has_started, bool has_ans, bool can_low, bool can_high, const string &lower, const string &upper) {
    if (idx == (int) lower.size()) {
        return has_ans && has_started;
    }
 
    if (DP[idx][last_digit][has_started][has_ans][can_low][can_high] != -1) {
        return DP[idx][last_digit][has_started][has_ans][can_low][can_high];
    }
 
    int lw {can_low ? 0 : lower[idx] - '0'};
    int up {can_high ? 9 : upper[idx] - '0'};
    ll ans {};
 
    for (int d {lw}; d <= up; ++d) {
        bool has_ans_now {has_started ? last_digit != d && has_ans : true};
 
        ans += solver(idx + 1, d, d != 0 || has_started, has_ans_now, can_low | (d != lw), can_high | (d != up), lower, upper);
    }
 
    return DP[idx][last_digit][has_started][has_ans][can_low][can_high] = ans;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
 
    memset(DP, -1, sizeof(DP));
 
    ll a, b;
 
    cin >> a >> b;
 
    string lower {to_string(a)}, upper {to_string(b)};
 
    while (lower.size() < upper.size()) {
        lower = '0' + lower;
    }
 
    cout << solver(0, 0, false, true, false, false, lower, upper) + (a == 0) << '\n';
 
    return 0;
}
