#include <bits/stdc++.h>

using namespace std;

#define L(x) (x << 1)
#define R(x) (L(x) | 1)

template <typename T, typename U>
class SegmentTree {
public:
	SegmentTree(const vector<U> &v) {
        this->n = (int) v.size();

        this->tree.resize(this->n * 4);

        this->build(v, 1, 1, this->n);
	}

    void update(int target_node, U v) {
        this->update(1, 1, this->n, target_node, v);
    }

    pair<T, int> query(int v) {
        if (this->tree[1].maxv < v) {
            return {0, -1};
        }

        return this->query(1, v);
    }

private:
    struct Node {
        T maxv {};
        int idx {};

		Node() = default;

        Node operator+(const Node &o) const {
            Node node;

            node.maxv = max(this->maxv, o.maxv);

            return node;
        }
    };

    int n;
    vector<Node> tree;

    void build(const vector<U> &v, int node, int l, int r) {
        if (l == r) {
            this->tree[node].maxv = v[l - 1];
            this->tree[node].idx = l;

            return;
        }

        int mid {(l + r) / 2};

        this->build(v, L(node), l, mid);
        this->build(v, R(node), mid + 1, r);

        this->tree[node] = this->tree[L(node)] + this->tree[R(node)];
    }

    void update(int node, int l, int r, int target, U v) {
        if (l == r) {
            this->tree[node].maxv = v;

            return;
        }

        int mid {(l + r) / 2};

        if (target <= mid) {
            this->update(L(node), l, mid, target, v);
        } else {
            this->update(R(node), mid + 1, r, target, v);
        }

        this->tree[node] = this->tree[L(node)] + this->tree[R(node)];
    }

    pair<T, int> query(int node, U v) {
        if (this->tree[node].idx != 0) {
            return {this->tree[node].maxv, this->tree[node].idx};
        }

        if (this->tree[L(node)].maxv >= v) {
            return this->query(L(node), v);
        }

        return this->query(R(node), v);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;

    cin >> n >> m;

    vector<int> v(n);

    for (int &x : v) {
        cin >> x;
    }

    SegmentTree<int, int> st(v);

    while (m--) {
        int x;

        cin >> x;

        auto [v, idx] {st.query(x)};

        if (idx == -1) {
            cout << 0 << " \n"[m == 0];
        } else {
            st.update(idx, v - x);

            cout << idx << " \n"[m == 0];
        }
    }

    return 0;
}
