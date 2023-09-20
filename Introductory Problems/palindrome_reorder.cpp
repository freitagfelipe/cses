#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;

    cin >> s;

    unordered_map<char, int> ump;

    for (char ch : s) {
        ++ump[ch];
    }

    int odd_c {};

    for (auto [ch, f] : ump) {
        if (f & 1) {
            ++odd_c;
        }
    }

    if (odd_c > 1) {
        cout << "NO SOLUTION\n";

        return 0;
    }

    string a, b;
    char odd_ch {};
    int freq_odd_ch {};

    for (auto &[ch, f] : ump) {
        if (f & 1) {
            odd_ch = ch;
            freq_odd_ch = f;

            continue;
        }

        while (f > 0) {
            a.push_back(ch);

            if (f >= 2) {
                b.push_back(ch);
            } 

            f -= 2;
        }
    }

    while (freq_odd_ch--) {
        b.push_back(odd_ch);
    }

    reverse(b.begin(), b.end());

    cout << a << b << '\n';

    return 0;
}
