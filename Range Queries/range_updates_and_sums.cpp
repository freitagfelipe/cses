#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
#define L(x) (x << 1)
#define R(x) (L(x) | 1)
#define MAXN int(2e5) + 10
 
int v[MAXN];

enum Type { SET, INCREASE };
 
template <typename T, typename U>
class SegmentTree {
public:
	void build(int n, U *v) {
		this->n = n;
 
		this->arr.resize(n + 1);
		this->tree.resize(n * 4);
 
		this->build(v, 1, 1, n);
	}
 
	void update(int l, int r, U v, Type type) {
		this->update(1, 1, this->n, l, r, v, type);
	}
 
    T query(int l, int r) {
        return this->query(1, 1, this->n, l, r).sum;
    }
 
private:
	struct Node {
		T sum_lazy {};
		T set_lazy {};
		bool dirty_set {};
		bool dirty_sum {};
        T sum;
 
        Node() = default;
 
		void add_lazy(T v, Type type) {
		    if (type == INCREASE) {
		        this->sum_lazy += v;
		        this->dirty_sum = true;
		    } else {
		        this->set_lazy = v;
		        this->dirty_set = true;

		        this->sum_lazy = 0;
		        this->dirty_sum = false;
		    }
		}
 
		tuple<T, bool, T, bool> apply_lazy(int interval_size) {
		    if (this->dirty_set) {
                this->sum = this->set_lazy * interval_size;
		    }

		    if (this->dirty_sum) {
                this->sum += this->sum_lazy * interval_size;
		    }
 
            return {exchange(this->sum_lazy, 0), exchange(this->dirty_sum, false), exchange(this->set_lazy, 0), exchange(this->dirty_set, false)};
		}
 
		Node operator+(const Node &o) const {
            Node node;
 
            node.sum = this->sum + o.sum;
 
            return node;
        }
	};
 
	int n;
	vector<U> arr;
	vector<Node> tree;
 
	void build(int *v, int node, int l, int r) {
        if (l == r) {
            this->arr[l] = v[l - 1];
            this->tree[node].sum = v[l - 1];
 
            return;
        }
 
        int mid {(l + r) / 2};
 
        this->build(v, L(node), l, mid);
        this->build(v, R(node), mid + 1, r);
 
        this->tree[node] = this->tree[L(node)] + this->tree[R(node)];
    }
 
	void lazy_propagation(int node, int l, int r) {
        if (!this->tree[node].dirty_sum && !this->tree[node].dirty_set) {
            return;
        }
 
		auto [sum_lazy, dirty_sum, set_lazy, dirty_set] {this->tree[node].apply_lazy(r - l + 1)};
 
        if (l < r) {
            if (dirty_set) {
	            this->tree[L(node)].add_lazy(set_lazy, SET);
	            this->tree[R(node)].add_lazy(set_lazy, SET);
            }

            if (dirty_sum) {
	            this->tree[L(node)].add_lazy(sum_lazy, INCREASE);
	            this->tree[R(node)].add_lazy(sum_lazy, INCREASE);
            }
        }
    }
 
	void update(int node, int l, int r, int l_target, int r_target, T v, Type type) {
        this->lazy_propagation(node, l, r);
 
        if (r_target < l || r < l_target) {
            return;
        }
 
        if (l_target <= l && r <= r_target) {
	        this->tree[node].add_lazy(v, type);
 
            this->lazy_propagation(node, l, r);
 
            return;
        }
 
        int mid {(l + r) / 2};
 
        this->update(L(node), l, mid, l_target, r_target, v, type);
        this->update(R(node), mid + 1, r, l_target, r_target, v, type);
 
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
    
    for (int i {}; i < n; ++i) {
        cin >> v[i];
    }
 
    SegmentTree<ll, int> st;
 
    st.build(n, v);
 
    while (q--) {
        int op;
 
        cin >> op;
 
        if (op == 1) {
            int l, r, x;
 
            cin >> l >> r >> x;
 
            st.update(l, r, x, INCREASE);
        } else if (op == 2) {
            int l, r, x;
 
            cin >> l >> r >> x;
 
            st.update(l, r, x, SET);
        } else {
            int l, r;
 
            cin >> l >> r;
 
            cout << st.query(l, r) << '\n';
        }
    }
 
    return 0;
}
