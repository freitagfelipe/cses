#include <bits/stdc++.h>

using namespace std;

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

    vector<pair<int, int>> get_min_cut() {
        vector<bool> visited(this->n);

        visited[this->s] = true;

        queue<int> q;

        q.push(this->s);

        while (!q.empty()) {
            int u {q.front()};

            q.pop();

            for (int edge_id : g[u]) {
                auto [from, to, capacity, flow] {this->edges[edge_id]};

                if (capacity == flow) {
                    continue;
                }

                if (!visited[to]) {
                    q.push(to);

                    visited[to] = true;
                }
            }
        }

        vector<pair<int, int>> min_cut;

        for (auto [from, to, capacity, flow] : this->edges) {
            if (capacity > 0 && capacity == flow && visited[from] != visited[to]) {
                min_cut.emplace_back(from, to);
            }
        }
        
        return min_cut;
    }

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;

    cin >> n >> m;

    Dinic<int> d(n, 0, n - 1);

    for (int i {}; i < m; ++i) {
        int u, v;

        cin >> u >> v;

        --u;
        --v;

        d.add_edge(u, v, 1);
        d.add_edge(v, u, 1);
    }

    d.get_max_flow();

    auto ans {d.get_min_cut()};

    cout << ans.size() << '\n';

    for (auto [u, v] : ans) {
        cout << u + 1 << " " << v + 1 << '\n';
    }

    return 0;
}
