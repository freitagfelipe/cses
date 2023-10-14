#include <bits/stdc++.h>

using namespace std;

#define PTreapNull -1

typedef long long ll;
typedef int PTreap;
typedef ll Ttype;

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

template <typename T>
struct Treap {
    int priority;
    array<int, 2> children {PTreapNull, PTreapNull};
    int sub_tree_size {1};
    T data {};
    T lazy {};
    T sum {};

    Treap(T data) {
        this->data = data;
        this->sum = data;
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
    treap.sum = treap.data;

    for (PTreap child : treap.children) {
        if (child == PTreapNull) {
            continue;
        }

        treap.sub_tree_size += treaps[child].sub_tree_size;
        treap.sum += treaps[child].sum;
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;

    cin >> n >> q;

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

    while (q--) {
        int op, l, r;

        cin >> op >> l >> r;

        auto [fl, fr] {split_by_size(treap, l - 1)};
        auto [sl, sr] {split_by_size(fr, r - l + 1)};

        if (op == 1) {
            treaps[sl].lazy ^= 1;
        } else {
            cout << treaps[sl].sum << '\n';
        }

        treap = merge(fl, merge(sl, sr));
    }

    return 0;
}
