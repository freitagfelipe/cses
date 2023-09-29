#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define L(x) (x << 1)
#define R(x) (L(x) | 1)

template <typename T, typename U>
class SegmentTree {
public:
	SegmentTree(int n) {
		this->n = n;
		
		this->tree.resize(this->n * 4);
	}

	SegmentTree(const vector<U> &v) {
		this->n = (int) v.size();

		this->tree.resize(this->n * 4);

		this->build(v, 1, 1, this->n);
	}

	void update(int l, int r) {
		this->update(1, 1, this->n, l, r);
	}

    T query(int l, int r) {
	    return this->query(1, 1, this->n, l, r).sum;
    }

private:
	struct Node {
	    bool lazy_dirt {};
		T lazy_a {};
		T lazy_r {};
		T sum {};

		Node() = default;

		void add_lazy(T a, T r) {
            this->lazy_a += a;
            this->lazy_r += r;
            this->lazy_dirt = true;
		}

		pair<T, T> apply_lazy(int l, int r) {
		    this->sum += (this->lazy_a + this->lazy_a + (r - l) * this->lazy_r) * (r - l + 1) / 2;
		    this->lazy_dirt = false;

		    return {exchange(this->lazy_a, 0), exchange(this->lazy_r, 0)};
		}

		Node operator+(const Node &o) const {
		    Node node;

		    node.sum = this->sum + o.sum;

		    return node;
        }
	};

	int n;
	vector<Node> tree;

	void build(const vector<U> &v, int node, int l, int r) {
        if (l == r) {
            this->tree[node].sum = v[l - 1];

            return;
        }

        int mid {(l + r) / 2};

        this->build(v, L(node), l, mid);
        this->build(v, R(node), mid + 1, r);

        this->tree[node] = this->tree[L(node)] + this->tree[R(node)];
    }

	void lazy_propagation(int node, int l, int r) {
        if (!this->tree[node].lazy_dirt) {
            return;
        }

		auto [a, d] {this->tree[node].apply_lazy(l, r)};

        if (l < r) {
	        this->tree[L(node)].add_lazy(a, d);

            int mid {(l + r) / 2};

	        this->tree[R(node)].add_lazy(a + (mid - l + 1) * d, d);
        }
    }

	void update(int node, int l, int r, int l_target, int r_target) {
        this->lazy_propagation(node, l, r);

        if (r_target < l || r < l_target) {
            return;
        }

        if (l_target <= l && r <= r_target) {
	        this->tree[node].add_lazy(l - l_target + 1, 1);

            this->lazy_propagation(node, l, r);

            return;
        }

        int mid {(l + r) / 2};

        this->update(L(node), l, mid, l_target, r_target);
        this->update(R(node), mid + 1, r, l_target, r_target);

        this->tree[node] = this->tree[L(node)] + this->tree[R(node)];
    }

	Node query(int node, int l, int r, int l_target, int r_target) {
        this->lazy_propagation(node, l, r);

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

    vector<int> v(n);

    for (int &x : v) {
        cin >> x;
    }

    SegmentTree<ll, int> st(v);

    while (q--) {
        int op, l, r;

        cin >> op >> l >> r;

        if (op == 1) {
            st.update(l, r);
        } else {
            cout << st.query(l, r) << '\n';
        }
    }

    return 0;
}
