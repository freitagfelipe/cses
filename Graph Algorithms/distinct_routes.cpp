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

    vector<vector<int>> get_distinct_routes() {
        vector<vector<int>> routes;

        while (true) {
            fill(this->level.begin(), this->level.end(), -1);
            
            if (!bfs()) {
                break;
            }

            fill(this->ptr.begin(), this->ptr.end(), 0);

            while (dfs(s, Dinic::FLOW_INF));
        }

        vector<int> route;

        this->ptr.assign(this->n, 0);

        while (this->mount_path(this->s, routes, route)) {
            route = {};
        }

        return routes;
    }

private:
    struct Edge {
        int from;
        int to;
        T capacity;
        T flow {};
        bool used {};

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
                auto [from, to, capacity, flow, used] {this->edges[edge_id]};

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
            auto [from, to, capacity, flow, used] {this->edges[edge_id]};

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

    bool mount_path(int u, vector<vector<int>> &routes, vector<int> &route) {
        if (u == this->t) {
            route.push_back(this->t);

            routes.push_back(route);

            route.pop_back();

            return true;
        }
        
        route.push_back(u);

        for (int &i {this->ptr[u]}; i < (int) g[u].size(); ++i) {
            int edge_id {this->g[u][i]};
            auto &[from, to, capacity, flow, used] {this->edges[edge_id]};

            if (capacity != 0 && capacity == flow && !used) {
                used = true;

                if (this->mount_path(to, routes, route)) {
                    ++i;

                    return true;
                }
            }
        }

        route.pop_back();

        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;

    cin >> n >> m;

    Dinic<long long> d(n, 0, n - 1);

    for (int i {}; i < m; ++i) {
        int u, v;

        cin >> u >> v;

        d.add_edge(u - 1, v - 1, 1);
    }

    auto routes {d.get_distinct_routes()};

    cout << routes.size() << '\n';

    for (const vector<int> &route : routes) {
        cout << route.size() << '\n';

        int c {};

        for (int u : route) {
            cout << u + 1 << " \n"[++c == (int) route.size()];
        }
    }

    return 0;
}
