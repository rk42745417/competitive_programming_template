namespace counting {
    ll mpow(ll a, ull b) {
        ll res = 1;
        for (a = (a % MOD + MOD) % MOD; b; b >>= 1, a = a * a % MOD)
            if (b & 1)
                res = res * a % MOD;
        return res;
    }
    struct combinatoric {
        vector<ll> fac, inv_fac;
        explicit combinatoric(int n) : fac(max(n, 1), 1), inv_fac(fac.size()) {
            for (size_t i = 2; i < fac.size(); i++)
                fac[i] = fac[i - 1] * ll(i) % MOD;
            inv_fac.back() = mpow(fac.back(), MOD - 2);
            for (size_t i = fac.size() - 1; i; i--)
                inv_fac[i - 1] = inv_fac[i] * ll(i) % MOD;
        }
        ll p(int n, int m) const {
            if (m < 0 || n < m)
                return 0;
            return fac[n] * inv_fac[n - m] % MOD;
        }
        ll c(int n, int m) const {
            if (m < 0 || n < m)
                return 0;
            return fac[n] * inv_fac[m] % MOD * inv_fac[n - m] % MOD;
        }
        ll h(int n, int m) const { return c(n + m - 1, m); }
    };
} using namespace counting;
/****************** Counting (mod MOD) ******************/
