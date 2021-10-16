struct heavy_light_decomposition {
	/* Requirements:
	 * N := the count of nodes
	 * edge[N] := the edges of the graph
	 * Can be modified:
	 * tree := Segment Tree or other data structure
	 */
	int dep[N], pa[N], hea[N], hev[N], pos[N], t;
	int dfs(int u) {
		int mx = 0, sz = 1;
		hev[u] = -1;
		for(int v : edge[u]) {
			if(v == pa[u])
				continue;
			pa[v] = u;
			dep[v] = dep[u] + 1;
			int c = dfs(v);
			if(c > mx)
				mx = c, hev[u] = v;
			sz += c;
		}
		return sz;
	}
	void find_head(int u, int h) {
		hea[u] = h;
		pos[u] = t++; // 0-indexed !!!
		if(~hev[u])
			find_head(hev[u], h);
		for(int v : edge[u])
			if(v != pa[u] && v != hev[u])
				find_head(v, v);
	}
	void init(int rt) {
		dfs(rt, rt);
		find_head(rt, rt);
	}
	/* It is necessary to edit below for every use */
	void edt(int a, int b, int v) {

	}
	int query(int a, int b) { // query path sum
		int res = 0;
		for(; hea[a] != hea[b]; a = pa[hea[a]]) {
			if(dep[hea[a]] < dep[hea[b]])
				swap(a, b);
			res += tree.que(pos[hea[a]], pos[a] + 1);
		}
		if(dep[a] > dep[b])
			swap(a, b);
		return res + tree.que(pos[a], pos[b] + 1);
	}
} hld;
/****************** Heavy Light Decomposition ***************/
