#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define L(x) (x << 1)
#define R(x) (L(x) | 1)
#define MAXN int(2e5) + 10

int v[MAXN];

template <typename T, typename U>
class SegmentTree {
public:
    void build(int n, U *v) {
        this->n = n;

        this->arr.resize(n + 1);
        this->tree.resize(n * 4);

        this->build(v, 1, 1, n);
    }

    void update(int target_node, U v) {
        this->update(1, 1, this->n, target_node, v);
    }

    T query() {
        T neutral {};

        return max(this->query(1, 1, this->n, 1, this->n).ans, neutral);
    }

private:
    struct Node {
        T sum {};
        T prefix {};
        T suffix {};
        T ans {};

		Node() = default;

        Node operator+(const Node &o) const {
            Node node;

            node.sum = this->sum + o.sum;
            node.prefix = max(this->prefix, this->sum + o.prefix);
            node.suffix = max(o.suffix, this->suffix + o.sum);
            node.ans = max({this->ans, o.ans, this->suffix + o.prefix});

            return node;
        }
    };

    int n;
    vector<U> arr;
    vector<Node> tree;

    void build(U *v, int node, int l, int r) {
        if (l == r) {
            this->tree[node].sum = this->tree[node].prefix = this->tree[node].suffix = this->tree[node].ans = v[l - 1];
            this->arr[l] = v[l - 1];

            return;
        }

        int mid {(l + r) / 2};

        this->build(v, L(node), l, mid);
        this->build(v, R(node), mid + 1, r);

        this->tree[node] = this->tree[L(node)] + this->tree[R(node)];
    }

    void update(int node, int l, int r, int target, U v) {
        if (l == r) {
            this->arr[l] = v;
            this->tree[node].sum = this->tree[node].prefix = this->tree[node].suffix = this->tree[node].ans = v;

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

    Node query(int node, int l, int r, int l_target, int r_target) {
		if (l == l_target && r == r_target) {
			return this->tree[node];
		}

		int mid {(l + r) / 2};

		if (r_target <= mid) {
			return this->query(L(node), l, mid, l_target, r_target);
		}

		if (l_target > mid) {
			return this->query(R(node), mid + 1, r, l_target, r_target);
		}

        return this->query(L(node), l, mid, l_target, mid) + this->query(R(node), mid + 1, r, mid + 1, r_target);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;

    cin >> n >> q;

    for (int i {}; i < n; ++i) {
        cin >> v[i];
    }

    SegmentTree<ll, int> st;

    st.build(n, v);

    while (q--) {
        int k, x;

        cin >> k >> x;

        st.update(k, x);

        cout << st.query() << '\n';
    }

    return 0;
}
