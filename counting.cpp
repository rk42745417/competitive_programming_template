namespace counting {
    ll mpow(ll a, ull b) {
        ll res = 1;
        for(a %= MOD; b; b >>= 1, a = a * a % MOD)
            if(b & 1)
                res = res * a % MOD;
        return res;
    }
    struct combinatoric {
        vector<ll> fac, inv_fac;
        combinatoric(int n) {
            fac.resize(n, 1);
            inv_fac.resize(n);
            for(int i = 2; i < n; i++)
                fac[i] = fac[i - 1] * i % MOD;
            inv_fac[n - 1] = mpow(fac[n - 1], MOD - 2);
            for(int i = n - 1; i; i--)
                inv_fac[i - 1] = inv_fac[i] * i % MOD;
        }
        inline ll p(int n, int m) {
            if(n < m)
                return 0;
            return fac[n] * mpow(fac[n - m], MOD - 2) % MOD;
        }
        inline ll c(int n, int m) {
            if(n < m)
                return 0;
            return fac[n] * mpow(fac[m], MOD - 2) % MOD * mpow(fac[n - m], MOD - 2) % MOD;
        }
        inline ll h(int n, int m) { return c(n + m - 1, m); }
    };
} using namespace counting;
