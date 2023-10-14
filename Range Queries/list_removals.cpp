#include <bits/stdc++.h>

using namespace std;

#define PTreapNull -1

typedef int PTreap;

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

template <typename T = int>
struct Treap {
    int priority;
    array<int, 2> children {PTreapNull, PTreapNull};
    int sub_tree_size {1};
    T data {};

    Treap(T data) {
        this->data = data;
        this->priority = rng();
    }
};

vector<Treap<>> treaps;

int size(PTreap t) {
    return t == PTreapNull ? 0 : treaps[t].sub_tree_size;
}

void recalculate(PTreap t) {
    if (t == PTreapNull) {
        return;
    }

    auto &treap {treaps[t]};

    treap.sub_tree_size = 1;

    for (PTreap child : treap.children) {
        if (child == PTreapNull) {
            continue;
        }

        treap.sub_tree_size += treaps[child].sub_tree_size;
    }
}

pair<PTreap, PTreap> split(PTreap t, int left_size) {
    if (t == PTreapNull) {
        return {PTreapNull, PTreapNull};
    }

    auto &treap {treaps[t]};

    if (size(treap.children[0]) >= left_size) {
        auto [left, right] {split(treap.children[0], left_size)};

        treap.children[0] = right;

        recalculate(t);

        return {left, t};
    }

    left_size -= size(treap.children[0]) + 1;

    auto [left, right] {split(treap.children[1], left_size)};

    treap.children[1] = left;
    
    recalculate(t);

    return {t, right};
}

PTreap merge(PTreap l, PTreap r) {
    if (l == PTreapNull || r == PTreapNull) {
        return l == PTreapNull ? r : l;
    }

    auto &lt {treaps[l]}, &rt {treaps[r]};

    PTreap treap {};

    if (lt.priority < rt.priority) {
        lt.children[1] = merge(lt.children[1], r);

        treap = l;
    } else {
        rt.children[0] = merge(l, rt.children[0]);

        treap = r;
    }

    recalculate(treap);

    return treap;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    PTreap treap {PTreapNull};

    for (int i {}; i < n; ++i) {
        int x;

        cin >> x;

        PTreap ot {(int) treaps.size()};

        treaps.emplace_back(x);

        if (treap == PTreapNull) {
            treap = ot;

            continue;
        }

        treap = merge(treap, ot);
    }

    vector<int> ans;

    while (n--) {
        int idx;

        cin >> idx;

        auto [fl, fr] {split(treap, idx - 1)};
        auto [sl, sr] {split(fr, 1)};

        ans.push_back(treaps[sl].data);

        treap = merge(fl, sr);
    }

    for (size_t i {}; int x : ans) {
        cout << x << " \n"[++i == ans.size()];
    }

    return 0;
}
