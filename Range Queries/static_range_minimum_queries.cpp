#include <iostream>
#include <functional>
#include <vector>
 
using namespace std;
 
#define MAXN int(1e6 + 10)
 
int v[MAXN];
 
class SparseTable {
public:
    SparseTable(function<int(int, int)> fn) {
        this->fn = fn;
    }
 
    void build(int n, int *v) {
        this->logs.resize(n + 1);
 
        this->logs[1] = 0;
 
        for (int i {2}; i <= n; ++i) {
            this->logs[i] = this->logs[i / 2] + 1;
        }
 
        this->sparse_table.resize(n, vector<int>(this->logs[n] + 1));
 
        for (int i {}; i < n; ++i) {
            this->sparse_table[i][0] = v[i];
        }
 
        for (int k {1}; (1 << k) <= n; ++k) {
            for (int i {}; i + (1 << k) - 1 < n; ++i) {
                this->sparse_table[i][k] = this->fn(this->sparse_table[i][k - 1], this->sparse_table[i + (1 << (k - 1))][k - 1]);
            }
        }
    }
 
    int query(int l, int r) {
        int size {r - l + 1};
        int k {this->logs[size]};
 
        return this->fn(this->sparse_table[l][k], this->sparse_table[r - (1 << k) + 1][k]);
    }
    
private:
    vector<int> logs;
    vector<vector<int>> sparse_table;
    function<int(int, int)> fn;
};
 
int main() {
    int n, q;
 
    cin >> n >> q;
 
    for (int i {}; i < n; ++i) {
        cin >> v[i];
    }
    
    std::function<int(int, int)> fn {[](int a, int b) {
        return min(a, b);
    }};
 
    SparseTable st(fn);
 
    st.build(n, v);
 
    for (int i {}; i < q; ++i) {
        int l, r;
 
        cin >> l >> r;
 
        cout << st.query(l - 1, r - 1) << '\n';
    }
 
    return 0;
}