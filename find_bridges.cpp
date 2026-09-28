struct find_bridges {
    int n = 0, t = 1;
    vector<vector<int>> edge;
    vector<bool> is;
    vector<pair<int, int>> edges;
    vector<int> tim, low;
    find_bridges() {}
    find_bridges(int _n) : n(_n), edge(_n), tim(_n), low(_n) {}
    void add_edge(int u, int v) {
        if (u != v) {
            edge[u].push_back((int)edges.size());
            edge[v].push_back((int)edges.size());
        }
        is.push_back(false);
        edges.emplace_back(u, v);
    }
    void dfs(int u, int p = -1) {
        tim[u] = low[u] = t++;
        for (int i : edge[u]) {
            if (i == p)
                continue;
            int v = edges[i].first ^ edges[i].second ^ u;
            if (tim[v]) {
                low[u] = min(low[u], tim[v]);
            } else {
                dfs(v, i);
                if (low[v] > tim[u])
                    is[i] = true;
                low[u] = min(low[u], low[v]);
            }
        }
    }
    int find() {
        for (int i = 0; i < n; i++)
            if (!tim[i])
                dfs(i);
        return (int)ranges::count(is, true);
    }
    bool is_bridge(int x) const { return is[x]; }
};
/*
 * find_bridges(int n): n nodes
 * add_edge(int u, int v): add undirected edge (u, v)
 * find(): return count of bridges
 * is_bridge(int x): return whether edge x is bridge
 */
/************ Tarjan's algorithm to find bridges ************/
