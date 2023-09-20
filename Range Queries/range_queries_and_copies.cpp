#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

template <typename T, typename U>
class PersistentSegmentTree {
public:
    PersistentSegmentTree(int n) {
        this->n = n;
    }

    PersistentSegmentTree(const vector<U> &v) {
        this->n = (int) v.size();

        Node *root {this->build(v, 1, this->n)};

        this->states.push_back(root);
    }

    void update(int state, int target_node, U v) {
        if (state < 0 || state >= (int) states.size()) {
            throw runtime_error("Invalid state");
        }

        Node *node {this->update(this->states[state], 1, this->n, target_node, v)};

        this->states[state] = node;
    }

    T query(int state, int l, int r) {
        if (state < 0 || state >= (int) states.size()) {
            throw runtime_error("Invalid state");
        }

        QueryAnswer qa {this->query(this->states[state], 1, this->n, l, r)};

        return qa.sum;
    }

	void create_state(int state) {
		this->states.push_back(this->states[state]);
	}

    size_t states_size() {
        return this->states.size();
    }

private:
    struct Node {
        Node *left {};
        Node *right {};

        T sum {};
        
        Node() = default;

        Node(Node *left, Node *right) {
            this->left = left;
            this->right = right;

            if (left != nullptr) {
                this->sum += left->sum;
            }

            if (right != nullptr) {
                this->sum += right->sum;
            }
        }
    };

    struct QueryAnswer {
        T sum {};
        
        QueryAnswer operator+(const QueryAnswer &o) const {
            QueryAnswer qa;

            qa.sum += this->sum + o.sum;

            return qa;
        }
    };

    int n;
    vector<Node*> states;

    Node *build(const vector<U> &v, int l, int r) {
        if (l == r) {
            Node *node {new Node()};

            node->sum = v[l - 1];

            return node;
        }

        int mid {(l + r) / 2};

        return new Node(this->build(v, l, mid), this->build(v, mid + 1, r));
    }

    Node *update(Node *node, int l, int r, int target, U v) {
        if (l == r) {
            Node *node {new Node()};

            node->sum = v;

            return node;
        }

        int mid {(l + r) / 2};

        if (target <= mid) {
            return new Node(this->update(node->left, l, mid, target, v), node->right);
        }

        return new Node(node->left, this->update(node->right, mid + 1, r, target, v));
    }

    QueryAnswer query(Node *node, int l, int r, int l_target, int r_target) {
        if (l == l_target && r == r_target) {
            QueryAnswer qa;

            qa.sum = node->sum;
            
            return qa;
        }

		int mid {(l + r) / 2};

		if (r_target <= mid) {
		    return this->query(node->left, l, mid, l_target, r_target);
		}

		if (l_target > mid) {
		    return this->query(node->right, mid + 1, r, l_target, r_target);
		}

		return this->query(node->left, l, mid, l_target, mid) + this->query(node->right, mid + 1, r, mid + 1, r_target);
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

    PersistentSegmentTree<ll, int> pst(v);

    while (q--) {
        int op;

        cin >> op;

        if (op == 1) {
            int k, a, x;

            cin >> k >> a >> x;

            pst.update(k - 1, a, x);
        } else if (op == 2) {
            int k, a, b;

            cin >> k >> a >> b;

            cout << pst.query(k - 1, a, b) << '\n';
        } else {
            int k;

            cin >> k;

            pst.create_state(k - 1);
        }
    }

    return 0;
}
