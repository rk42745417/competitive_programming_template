int dep[N], pa[N], hea[N], hev[N], pos[N], t;
vector<int> edge[N];
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
void hld(int u, int h) {
	hea[u] = h;
	pos[u] = t++;
	if(~hev[u])
		hld(hev[u], h);
	for(int v : edge[u])
		if(v != pa[u] && v != hev[u])
			hld(v, v);
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