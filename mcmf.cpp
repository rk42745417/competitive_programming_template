struct cost_flow {
    static constexpr ll COST_INF = LINF;
    struct Edge {
        int v, r;
        ll f, c;
        Edge(int _v, int _r, ll _f, ll _c) : v(_v), r(_r), f(_f), c(_c) {}
    };
    int n, s, t;
    vector<int> prv, prvL;
    vector<ll> dis, h;
    ll fl, cost;
    vector<vector<Edge>> E;
    void init(int _n, int _s, int _t) {
        n = _n; s = _s; t = _t;
        E.assign(n, {});
        prv.resize(n);
        prvL.resize(n);
        dis.resize(n);
        h.resize(n);
        fl = cost = 0;
    }
    void add_edge(int u, int v, ll f, ll c) {
        E[u].emplace_back(v, (int)E[v].size(), f, c);
        E[v].emplace_back(u, (int)E[u].size() - 1, 0, -c);
    }
    // SPFA once for initial potentials, so negative costs are allowed (no negative cycles)
    void init_potential() {
        vector<bool> inq(n);
        fill(h.begin(), h.end(), COST_INF);
        h[s] = 0;
        queue<int> que;
        que.push(s);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            inq[u] = false;
            for (auto &e : E[u]) {
                if (e.f > 0 && h[e.v] > h[u] + e.c) {
                    h[e.v] = h[u] + e.c;
                    if (!inq[e.v]) {
                        inq[e.v] = true;
                        que.push(e.v);
                    }
                }
            }
        }
    }
    // Dijkstra on reduced costs c(u, v) + h[u] - h[v] >= 0
    bool dijkstra() {
        using node = pair<ll, int>;
        fill(dis.begin(), dis.end(), COST_INF);
        dis[s] = 0;
        priority_queue<node, vector<node>, greater<>> pq;
        pq.emplace(0, s);
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d != dis[u])
                continue;
            for (int i = 0; i < (int)E[u].size(); i++) {
                const Edge &e = E[u][i];
                if (e.f <= 0)
                    continue;
                ll nd = d + e.c + h[u] - h[e.v];
                if (dis[e.v] > nd) {
                    dis[e.v] = nd;
                    prv[e.v] = u;
                    prvL[e.v] = i;
                    pq.emplace(nd, e.v);
                }
            }
        }
        if (dis[t] == COST_INF)
            return false;
        for (int i = 0; i < n; i++)
            if (dis[i] != COST_INF)
                h[i] += dis[i];
        return true;
    }
    // O(F (V + E) log V) after one SPFA
    pair<ll, ll> flow() {
        init_potential();
        while (dijkstra()) {
            ll tf = COST_INF;
            for (int v = t; v != s; v = prv[v])
                tf = min(tf, E[prv[v]][prvL[v]].f);
            for (int v = t; v != s; v = prv[v]) {
                Edge &e = E[prv[v]][prvL[v]];
                e.f -= tf;
                E[v][e.r].f += tf;
            }
            cost += tf * (h[t] - h[s]);
            fl += tf;
        }
        return {fl, cost};
    }
} flow;
/*
 * init(int n, int s, int t): n nodes, source s, sink t
 * add_edge(int u, int v, ll cap, ll cost): directed edge, negative cost ok without negative cycles
 * flow(): return {max flow, min cost}
 */
/**************************** Min Cost Max Flow *************************/
