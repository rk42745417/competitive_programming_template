struct bipartite_matching {
	int n, m;
	vector<vector<int>> edge;
	vector<bool> vis;
	vector<int> matl, matr;
	bipartite_matching() { }
	bipartite_matching(int _n, int _m) {
		n = _n;
		m = _m;
		edge.resize(n);
		vis.resize(m);
		matl.resize(n, -1);
		matr.resize(m, -1);
	}
	bool dfs(int u) {
		for(int v : edge[u]) {
			if(vis[v])
				continue;
			vis[v] = true;
			if(matr[v] == -1 || dfs(matr[v])) {
				matr[v] = u;
				matl[u] = v;
				return true;
			}
		}
		return false;
	}
	inline void add_edge(int u, int v) { edge[u].push_back(v); }
	inline int other(int x) { return matl[x]; }
	// O(n^3)
	int match() {
		int ans = 0;
		for(int i = 0; i < n; i++) {
			fill(vis.begin(), vis.end(), false);
			ans += dfs(i);
		}
		return ans;
	}
};
/*
 * bipartite(int n, int m): left size n, right size m
 * match(): return max matching
 * add_edge(int u, int v): add edge from left[u] to right[v]
 * other(int u): return the matched right index of left[u], -1 if not matched
 */
/********* Bipartite Matching ********************/
