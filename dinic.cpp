struct dinic {
    struct FlowEdge {
        int v, u;
        ll cap, flow = 0;
        FlowEdge(int _v, int _u, ll _cap) : v(_v), u(_u), cap(_cap) {}
    };
    static constexpr ll flow_inf = LINF;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;
    dinic(int _n, int _s, int _t) : adj(_n), n(_n), s(_s), t(_t), level(_n), ptr(_n) {}
    void add_edge(int v, int u, ll cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }
    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }
    // pushes as much as possible from v in one call (multi-augment)
    ll dfs(int v, ll pushed) {
        if (v == t || pushed == 0)
            return pushed;
        ll res = 0;
        for (int &cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            ll tr = dfs(u, min(pushed - res, edges[id].cap - edges[id].flow));
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            res += tr;
            if (res == pushed)
                return res;
        }
        return res;
    }
    ll flow() {
        ll f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (ll pushed = dfs(s, flow_inf))
                f += pushed;
        }
        return f;
    }
    // call after flow(): cut[v] is true iff v is on the source side of a min cut
    vector<bool> min_cut() const {
        vector<bool> cut(n);
        for (int i = 0; i < n; i++)
            cut[i] = level[i] != -1;
        return cut;
    }
};
/*********************** Dinic's Max Flow ***********************/
