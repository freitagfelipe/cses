#include <bits/stdc++.h>
 
using namespace std;
 
typedef pair<int, int> pll;

#define MAXN 2 * int(1e5) + 10

vector<int> g[MAXN];
 
pll dfs(int curr, int d = 0, int p = -1) {
    pll most_distant {curr, d};
 
    for (int neigh : g[curr]) {
        if (neigh != p) {
            pll result {dfs(neigh, d + 1, curr)};
 
            if (result.second > most_distant.second) {
                most_distant = result;
            }
        }
    }
 
    return most_distant;
}
 
int tree_diameter() {
	return dfs(dfs(0).first).second;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    
    cin >> n;
 
    for (int i {}; i < n - 1; ++i) {
        int x, y;
        
        cin >> x >> y;
        
        --x;
        --y;
        
        g[x].push_back(y);
        g[y].push_back(x);
    }
    
    cout << tree_diameter() << '\n';
 
    return 0;
}