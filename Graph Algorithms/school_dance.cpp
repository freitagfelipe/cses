#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

template <typename T>
class Dinic {
public:
    Dinic(int n, int s, int t): g(n), level(n), ptr(n) {
        this->n = n;
        this->s = s;
        this->t = t;
    }

    void add_edge(int from, int to, T capacity) {
        this->edges.emplace_back(from, to, capacity);
        this->edges.emplace_back(to, from, 0);

        this->g[from].push_back(this->m++);
        this->g[to].push_back(this->m++);
    }

    T get_max_flow() {
        T flow {};

        while (true) {
            fill(this->level.begin(), this->level.end(), -1);
            
            if (!bfs()) {
                break;
            }

            fill(this->ptr.begin(), this->ptr.end(), 0);

            while (T new_flow = dfs(s, Dinic::FLOW_INF)) {
                flow += new_flow;
            }
        }

        return flow;
    }

    template <typename U>
    friend vector<pii> get_match(const Dinic<U> &d, int k);

private:
    struct Edge {
        int from;
        int to;
        T capacity;
        T flow {};

        Edge(int from, int to, int capacity) {
            this->from = from;
            this->to = to;
            this->capacity = capacity;
        }
    };

    const static T FLOW_INF {numeric_limits<T>::max()};

    vector<vector<int>> g; 
    vector<Edge> edges;
    vector<int> level, ptr;
    int n, m {};
    int s, t;

    bool bfs() {
        this->level[this->s] = 0;

        queue<int> q;

        q.push(this->s);

        while (!q.empty()) {
            int u {q.front()};

            q.pop();

            for (int edge_id : this->g[u]) {
                auto [from, to, capacity, flow] {this->edges[edge_id]};

                if (capacity - flow < 1 || this->level[to] != -1) {
                    continue;
                }

                this->level[to] = this->level[u] + 1;

                q.push(to);
            }
        }

        return this->level[this->t] != -1;
    }

    T dfs(int u, T bottleneck) {
        if (bottleneck == 0 || u == this->t) {
            return bottleneck;
        }

        for (int &i {this->ptr[u]}; i < (int) g[u].size(); ++i) {
            int edge_id {this->g[u][i]};
            auto [from, to, capacity, flow] {this->edges[edge_id]};

            if (this->level[u] + 1 != this->level[to] || capacity - flow < 1) {
                continue;
            }
            
            T new_flow {dfs(to, min(bottleneck, capacity - flow))};

            if (new_flow == 0) {
                continue;
            }

            this->edges[edge_id].flow += new_flow;
            this->edges[edge_id ^ 1].flow -= new_flow;

            return new_flow;
        }

        return 0;
    }
};

template <typename U>
vector<pii> get_match(const Dinic<U> &d, int k) {
    vector<pii> match;

    for (int u {1}; u <= k; ++u) {
        for (int edge_id : d.g[u]) {
            auto [from, to, capacity, flow] {d.edges[edge_id]};

            if (capacity > 0 && capacity == flow) {
                match.emplace_back(from, to);
            }
        }
    }

    return match;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;

    cin >> n >> m >> k;

    Dinic<long long> d(n + m + 2, 0, n + m + 1);

    for (int i {1}; i <= n; ++i) {
        d.add_edge(0, i, 1);
    }

    for (int i {}; i < k; ++i) {
        int u, v;

        cin >> u >> v;

        d.add_edge(u, v + n, 1);
    }

    for (int i {}; i < m; ++i) {
        d.add_edge(i + n + 1, n + m + 1, 1);
    }

    cout << d.get_max_flow() << '\n';

    auto matching {get_match(d, n)};

    for (auto [f, s] : matching) {
        cout << f << " " << s - n << '\n';
    }

    return 0;
}
