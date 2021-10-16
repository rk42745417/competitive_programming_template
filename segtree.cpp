struct segtree {
	/* N is required as the length of the array.
	 * default operations: range addtion and rage sum query
	 */
	int64_t arr[N << 1], tag[N];
	int n;
	void init(int _n) {
		n = _n;
	}
	void upd(int p, int64_t val, int h) {
		arr[p] += val << h;
		if(p < n)
			tag[p] += val;
	}
	void push(int p) {
		for(int h = __lg(p); ~h; h--) {
			int i = p >> h;
			if(!tag[i >> 1])
				continue;
			upd(i, tag[i >> 1], h);
			upd(i ^ 1, tag[i >> 1], h);
			tag[i >> 1] = 0;
		}
	}
	void pull(int p) {
		for(int h = 1; p > 1; p >>= 1, h++) {
			arr[p >> 1] = arr[p] + arr[p ^ 1] + (tag[p >> 1] << h); //Be careful of the exchange
		}
	}
	void mod(int l, int r, int val) {
		int tl = l + n, tr = r + n - 1, h = 0;
		for(l += n, r += n; l < r; l >>= 1, r >>= 1, h++) {
			if(l & 1)
				upd(l++, val, h);
			if(r & 1)
				upd(--r, val, h);
		}
		pull(tl); pull(tr);
	}
	ll que(int l, int r) {
		int64_t res = 0;
		push(l + n); push(r + n - 1);
		for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if(l & 1)
				res += arr[l++];
			if(r & 1)
				res += arr[--r];
		}
		return res;
	}
} tree;
/*************************** Segment Tree ************************/
