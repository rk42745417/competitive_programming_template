struct bipartite_matching {
    int n = 0, m = 0;
    vector<vector<int>> edge;
    vector<int> dist, it, matl, matr;
    bipartite_matching() {}
    bipartite_matching(int _n, int _m) : n(_n), m(_m), edge(_n), dist(_n), it(_n), matl(_n, -1), matr(_m, -1) {}
    bool bfs() {
        queue<int> q;
        for (int i = 0; i < n; i++) {
            dist[i] = matl[i] == -1 ? 0 : -1;
            if (!dist[i])
                q.push(i);
        }
        bool found = false;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : edge[u]) {
                int w = matr[v];
                if (w == -1)
                    found = true;
                else if (dist[w] == -1)
                    dist[w] = dist[u] + 1, q.push(w);
            }
        }
        return found;
    }
    bool dfs(int u) {
        for (int &i = it[u]; i < (int)edge[u].size(); i++) {
            int v = edge[u][i], w = matr[v];
            if (w == -1 || (dist[w] == dist[u] + 1 && dfs(w))) {
                matr[v] = u;
                matl[u] = v;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }
    void add_edge(int u, int v) { edge[u].push_back(v); }
    int other(int x) const { return matl[x]; }
    // Hopcroft-Karp, O(E sqrt(V))
    int match() {
        while (bfs()) {
            fill(it.begin(), it.end(), 0);
            for (int i = 0; i < n; i++)
                if (matl[i] == -1)
                    dfs(i);
        }
        return n - (int)count(matl.begin(), matl.end(), -1);
    }
};
/*
 * bipartite_matching(int n, int m): left size n, right size m
 * match(): return max matching
 * add_edge(int u, int v): add edge from left[u] to right[v]
 * other(int u): return the matched right index of left[u], -1 if not matched
 */
/********* Bipartite Matching ********************/
