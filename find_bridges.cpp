struct find_bridges {
	int n, t;
	vector<vector<int>> edge;
	vector<bool> is;
	vector<pair<int, int>> edges;
	vector<int> tim, low;
	find_bridges() { }
	find_bridges(int _n) {
		n = _n;
		t = 1;
		edge.resize(n);
		tim.resize(n);
		low.resize(n);
	}
	void add_edge(int u, int v) {
		if(u != v) {
			edge[u].push_back(edges.size());
			edge[v].push_back(edges.size());
		}
		is.push_back(false);
		edges.push_back({u, v});
	}
	void dfs(int u, int p = -1) {
		tim[u] = low[u] = t++;
		for(int i : edge[u]) {
			if(i == p)
				continue;
			int v = edges[i].first;
			if(v == u)
				v = edges[i].second;
			if(tim[v])
				low[u] = min(low[u], tim[v]);
			else {
				dfs(v, i);
				if(low[v] > tim[u])
					is[i] = true;
				low[u] = min(low[u], low[v]);
			}
		}
	}
	int find() {
		for(int i = 0; i < n; i++)
			if(!tim[i])
				dfs(i);
		int ans = 0;
		for(int i = 0; i < edges.size(); i++)
			ans += is[i];
		return ans;
	}
	inline bool is_edge(int x) { return is[x]; }
};
/*
 * find_bridges(int n): node count
 * add_edge(int u, int v): add undirected edge (u, v)
 * find(): return count of bridges
 * is_edge(int x): return whether edge x is bridge
 */
/************ Tarjan's algorithm to find bridges ************/
