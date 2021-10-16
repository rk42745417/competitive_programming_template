struct cost_flow {
    static const int MXN = 1005;
    static const int64_t INF = 102938475610293847LL;
    struct Edge {
        int v, r;
        int64_t f, c;
        Edge(int a,int b,int _c,int d):v(a),r(b),f(_c),c(d){
		}
    };
    int n, s, t, prv[MXN], prvL[MXN], inq[MXN];
    int64_t dis[MXN], fl, cost;
    vector<Edge> E[MXN];
    void init(int _n, int _s, int _t) {
        n = _n; s = _s; t = _t;
        for (int i=0; i<n; i++) E[i].clear();
        fl = cost = 0;
    }
    void add_edge(int u, int v, int64_t f, int64_t c)
    {
        E[u].push_back(Edge(v, E[v].size() , f, c));
        E[v].push_back(Edge(u, E[u].size()-1, 0, -c));
    }
    pair<int64_t, int64_t> flow() {
        while (true) {
            for (int i=0; i<n; i++) {
                dis[i] = INF;
                inq[i] = 0;
            }
            dis[s] = 0;
            queue<int> que;
            que.push(s);
            while (!que.empty()) {
                int u = que.front(); que.pop();
                inq[u] = 0;
                for (int i=0; i<E[u].size(); i++) {
                    int v = E[u][i].v;
                    int64_t w = E[u][i].c;
                    if (E[u][i].f > 0 && dis[v] > dis[u] + w) {
                        prv[v] = u; prvL[v] = i;
                        dis[v] = dis[u] + w;
                        if (!inq[v]) {
                            inq[v] = 1;
                            que.push(v);
                        }
                    }
                }
            }
            if (dis[t] == INF) break;
            int64_t tf = INF;
            for (int v=t, u, l; v!=s; v=u) {
                u=prv[v]; l=prvL[v];
                tf = min(tf, E[u][l].f);
            }
            for (int v=t, u, l; v!=s; v=u) {
                u=prv[v]; l=prvL[v];
                E[u][l].f -= tf;
                E[v][E[u][l].r].f += tf;
            }
            cost += tf * dis[t];
            fl += tf;
        }
        return {fl, cost};
    }
} flow;
/**************************** Min Cost Max Flow *************************/
