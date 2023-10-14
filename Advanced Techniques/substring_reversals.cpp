#include <bits/stdc++.h>

using namespace std;

#define PTreapNull -1

typedef int PTreap;
typedef char Ttype;

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

template <typename T>
struct Treap {
    int priority;
    array<int, 2> children {PTreapNull, PTreapNull};
    int sub_tree_size {1};
    T data {};
    T lazy {};

    Treap(T data) {
        this->data = data;
        this->priority = rng();
    }
};

vector<Treap<Ttype>> treaps;

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

void apply_lazy(PTreap t) {
    if (t == PTreapNull || treaps[t].lazy == 0) {
        return;
    }

    auto &treap {treaps[t]};

    for (PTreap child : treap.children) {
        if (child == PTreapNull) {
            continue;
        }

        treaps[child].lazy ^= 1;
    }

    swap(treap.children[0], treap.children[1]);

    treap.lazy = 0;

    recalculate(t);
}

pair<PTreap, PTreap> split_by_size(PTreap t, int left_size) {
    if (t == PTreapNull) {
        return {PTreapNull, PTreapNull};
    }

    apply_lazy(t);

    auto &treap {treaps[t]};

    if (size(treap.children[0]) >= left_size) {
        auto [left, right] {split_by_size(treap.children[0], left_size)};

        treap.children[0] = right;

        recalculate(t);

        return {left, t};
    }

    left_size -= size(treap.children[0]) + 1;

    auto [left, right] {split_by_size(treap.children[1], left_size)};

    treap.children[1] = left;
    
    recalculate(t);

    return {t, right};
}

PTreap merge(PTreap l, PTreap r) {
    if (l == PTreapNull || r == PTreapNull) {
        return l == PTreapNull ? r : l;
    }

    apply_lazy(l);
    apply_lazy(r);

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

void solver(PTreap t) {
    if (t == PTreapNull) {
        return;
    }

    apply_lazy(t);

    auto &treap {treaps[t]};

    solver(treap.children[0]);

    cout << treap.data;

    solver(treap.children[1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    string s;

    cin >> n >> q >> s;

    PTreap treap {PTreapNull};

    for (char ch : s) {
        PTreap ot {(int) treaps.size()};

        treaps.emplace_back(ch);

        if (treap == PTreapNull) {
            treap = ot;

            continue;
        }

        treap = merge(treap, ot);
    }

    while (q--) {
        int l, r;

        cin >> l >> r;

        auto [fl, fr] {split_by_size(treap, l - 1)};
        auto [sl, sr] {split_by_size(fr, r - l + 1)};

        treaps[sl].lazy ^= 1;

        treap = merge(fl, merge(sl, sr));
    }

    solver(treap);

    cout << '\n';

    return 0;
}
