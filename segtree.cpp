struct segtree {
    /* default operations: range addition and range sum query
     * all ranges are half-open [l, r)
     */
    vector<ll> arr, tag;
    int n;
    void init(int _n) {
        n = _n;
        arr.assign(n << 1, 0);
        tag.assign(n, 0);
    }
    void init(const vector<ll> &a) { // build from initial values in O(n)
        init((int)a.size());
        copy(a.begin(), a.end(), arr.begin() + n);
        for (int i = n - 1; i > 0; i--)
            arr[i] = arr[i << 1] + arr[i << 1 | 1];
    }
    void upd(int p, ll val, int h) {
        arr[p] += val << h;
        if (p < n)
            tag[p] += val;
    }
    void push(int p) {
        for (int h = __lg(p); ~h; h--) {
            int i = p >> h;
            if (!tag[i >> 1])
                continue;
            upd(i, tag[i >> 1], h);
            upd(i ^ 1, tag[i >> 1], h);
            tag[i >> 1] = 0;
        }
    }
    void pull(int p) {
        for (int h = 1; p > 1; p >>= 1, h++)
            arr[p >> 1] = arr[p] + arr[p ^ 1] + (tag[p >> 1] << h); // Be careful of the exchange
    }
    void edt(int l, int r, ll val) {
        if (l == r)
            return;
        int tl = l + n, tr = r + n - 1, h = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1, h++) {
            if (l & 1)
                upd(l++, val, h);
            if (r & 1)
                upd(--r, val, h);
        }
        pull(tl);
        pull(tr);
    }
    ll que(int l, int r) {
        if (l == r)
            return 0; // do something!
        ll res = 0;
        push(l + n);
        push(r + n - 1);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                res += arr[l++];
            if (r & 1)
                res += arr[--r];
        }
        return res;
    }
} tree;
/*
 * init(int n) / init(vector<ll> a): zeros / build from a
 * edt(int l, int r, ll v): add v on [l, r)
 * que(int l, int r): sum of [l, r)
 */
/*************************** Segment Tree ************************/
