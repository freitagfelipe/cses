#include <bits/stdc++.h>

using namespace std;

#define MAXN int(2e5 + 10)

vector<int> g[MAXN], p, depth, heavy, head, pos, sz;
int curr_pos;

#define L(x) (x << 1)
#define R(x) (L(x) | 1)

template <typename T, typename U>
class SegmentTree {
public:
    SegmentTree(int n) {
        this->n = n;

        this->tree.resize(this->n * 4);
    }

    void update(int target_node, U v) {
        this->update(1, 1, this->n, target_node, v);
    }

    T query(int l, int r) {
        return this->query(1, 1, this->n, l, r).maxv;
    }

private:
    struct Node {
        T maxv {};

		Node() = default;

        Node operator+(const Node &o) const {
            Node node;

            node.maxv = max(this->maxv, o.maxv);

            return node;
        }
    };

    int n;
    vector<Node> tree;

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

int dfs(int u) {
    sz[u] = 1;
    int max_to_size {};

    for (int to : g[u]) {
        if (to != p[u]) {
            p[to] = u;
            depth[to] = depth[u] + 1;
            
            int to_size {dfs(to)};

            sz[u] += to_size;

            if (to_size > max_to_size) {
                max_to_size = to_size;
                heavy[u] = to;
            }
        }
    }

    return sz[u];
}

void decompose(int u, int h) {
    head[u] = h;
    pos[u] = ++curr_pos;

    if (heavy[u] != -1) {
        decompose(heavy[u], h);
    }

    for (int to : g[u]) {
        if (to != p[u] && to != heavy[u]) {
            decompose(to, to);
        }
    }
}

void build(int root, int n) {
    p.assign(n, -1);
    depth.assign(n, 0);
    heavy.assign(n, -1);
    head.assign(n, 0);
    pos.assign(n, 0);
    sz.assign(n, 0);

    curr_pos = 0;

    dfs(root);
    decompose(root, root);
}

int query_path(int u, int v, SegmentTree<int, int> &st) {
    if (pos[u] < pos[v]) {
        swap(u, v);
    }

    if (head[u] == head[v]) {
        return st.query(pos[v], pos[u]);
    }

    return max(st.query(pos[head[u]], pos[u]), query_path(p[head[u]], v, st));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    
    cin >> n >> q;

    vector<int> v(n);

    for (int &x : v) {
        cin >> x;
    }

    for (int i {}; i < n - 1; ++i) {
        int u, v;

        cin >> u >> v;

        --u;
        --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    build(0, n);

    SegmentTree<int, int> st(n);

    for (int i {}; i < n; ++i) {
        st.update(pos[i], v[i]);
    }

    vector<int> ans;

    while (q--) {
        int op;
        
        cin >> op;

        if (op == 1) {
            int u, x;

            cin >> u >> x;

            st.update(pos[u - 1], x);
        } else {
            int u, v;

            cin >> u >> v;

            ans.push_back(query_path(u - 1, v - 1, st));
        }
    }

    for (size_t i {}; int x : ans) {
        cout << x << " \n"[++i == ans.size()];
    }

    return 0;
}
