template<typename T>
struct shortest_path {
    static constexpr T T_INF = numeric_limits<T>::max();
    int n;
    vector<vector<pair<int, T>>> adj;
    vector<T> dis;
    vector<int> prv;
    shortest_path(int _n) : n(_n), adj(_n) {}
    void add_edge(int u, int v, T w) { adj[u].emplace_back(v, w); }
    // O((V + E) log V), weights must be non-negative
    const vector<T>& run(int s) {
        using node = pair<T, int>;
        dis.assign(n, T_INF);
        prv.assign(n, -1);
        priority_queue<node, vector<node>, greater<>> pq;
        dis[s] = 0;
        pq.emplace(0, s);
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d != dis[u])
                continue;
            for (auto [v, w] : adj[u]) {
                if (d + w < dis[v]) {
                    dis[v] = d + w;
                    prv[v] = u;
                    pq.emplace(dis[v], v);
                }
            }
        }
        return dis;
    }
    vector<int> path(int t) const {
        if (dis[t] == T_INF)
            return {};
        vector<int> res;
        for (int v = t; v != -1; v = prv[v])
            res.push_back(v);
        reverse(res.begin(), res.end());
        return res;
    }
};
/*
 * shortest_path<T> sp(int n): n nodes, weights must be non-negative
 * add_edge(int u, int v, T w): directed edge u -> v
 * run(int s): return distances from s, T_INF if unreachable
 * path(int t): nodes on a shortest path s -> t, empty if unreachable
 */
/****************** Dijkstra's algorithm *****************/
