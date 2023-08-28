#include <bits/stdc++.h>

using namespace std;

vector<int> next_smaller(const vector<int> &v) {
    vector<int> ns(v.size(), -1);
    stack<int> s;

    s.push((int) v.size() - 1);

    for (int i {(int) v.size() - 2}; i >= 0; --i) {
        if (v[s.top()] > v[i]) {
            while (!s.empty() && v[s.top()] > v[i]) {
                ns[s.top()] = i;

                s.pop();
            }
        }

        s.push(i);
    }

    return ns;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    vector<int> v(n);

    for (int &x : v) {
        cin >> x;
    }

    vector<int> ns {next_smaller(v)};

    for (size_t i {}; int idx : ns) {
        cout << idx + 1 << " \n"[++i == ns.size()];
    }

    return 0;
}
