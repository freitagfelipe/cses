#include <bits/stdc++.h>

using namespace std;

enum Type { START, END };

typedef tuple<int, Type, int> Event;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    vector<Event> events;

    for (int i {}; i < n; ++i) {
        int start, end;

        cin >> start >> end;

        events.emplace_back(start, START, i);
        events.emplace_back(end, END, i);
    }

    sort(events.begin(), events.end(), [](const Event &a, const Event &b) {
        auto [time_a, type_a, idx_a] {a};
        auto [time_b, type_b, idx_b] {b};

        if (time_a == time_b) {
            return type_a > type_b;
        }

        return time_a < time_b;
    });

    int ans {};
    set<int> active_events;

    for (auto [time, type, idx] : events) {
        if (type == START) {
            active_events.insert(idx);

            ans = max(ans, (int) active_events.size());
        } else {
            active_events.erase(idx);
        }
    }

    cout << ans << '\n';

    return 0;
}
