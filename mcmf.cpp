struct cost_flow {
    static constexpr ll COST_INF = LINF;
    struct Edge {
        int v, r;
        ll f, c;
        Edge(int _v, int _r, ll _f, ll _c) : v(_v), r(_r), f(_f), c(_c) {}
    };
    int n, s, t;
    vector<int> prv, prvL;
    vector<bool> inq;
    vector<ll> dis;
    ll fl, cost;
    vector<vector<Edge>> E;
    void init(int _n, int _s, int _t) {
        n = _n; s = _s; t = _t;
        E.assign(n, {});
        prv.resize(n);
        prvL.resize(n);
        inq.resize(n);
        dis.resize(n);
        fl = cost = 0;
    }
    void add_edge(int u, int v, ll f, ll c) {
        E[u].emplace_back(v, (int)E[v].size(), f, c);
        E[v].emplace_back(u, (int)E[u].size() - 1, 0, -c);
    }
    pair<ll, ll> flow() {
        while (true) {
            fill(dis.begin(), dis.end(), COST_INF);
            fill(inq.begin(), inq.end(), false);
            dis[s] = 0;
            queue<int> que;
            que.push(s);
            while (!que.empty()) {
                int u = que.front();
                que.pop();
                inq[u] = false;
                for (int i = 0; i < (int)E[u].size(); i++) {
                    auto [v, r, f, c] = E[u][i];
                    if (f > 0 && dis[v] > dis[u] + c) {
                        prv[v] = u;
                        prvL[v] = i;
                        dis[v] = dis[u] + c;
                        if (!inq[v]) {
                            inq[v] = true;
                            que.push(v);
                        }
                    }
                }
            }
            if (dis[t] == COST_INF)
                break;
            ll tf = COST_INF;
            for (int v = t; v != s; v = prv[v])
                tf = min(tf, E[prv[v]][prvL[v]].f);
            for (int v = t; v != s; v = prv[v]) {
                Edge &e = E[prv[v]][prvL[v]];
                e.f -= tf;
                E[v][e.r].f += tf;
            }
            cost += tf * dis[t];
            fl += tf;
        }
        return {fl, cost};
    }
} flow;
/**************************** Min Cost Max Flow *************************/
