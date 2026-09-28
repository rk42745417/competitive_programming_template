namespace number_theory {
    struct prime_sieve {
    private:
        vector<bool> sieve;
        vector<int> prime, lpf;
        int n;
    public:
        // with_lpf: also store the least prime factor (4 bytes per number) for factorize()
        prime_sieve(int _n, bool with_lpf = false) : sieve(_n), n(_n) {
            if (with_lpf)
                lpf.resize(n);
            for (int i = 2; i < n; i++) {
                if (!sieve[i]) {
                    prime.push_back(i);
                    if (with_lpf)
                        lpf[i] = i;
                }
                for (int p : prime) {
                    if (ll(i) * p >= n)
                        break;
                    sieve[i * p] = true;
                    if (with_lpf)
                        lpf[i * p] = p;
                    if (i % p == 0)
                        break;
                }
            }
        }
        size_t prime_cnt() const { return prime.size(); }
        int operator[](int x) const {
            assert(0 <= x && x < (int)prime.size());
            return prime[x];
        }
        bool is_prime(int x) const {
            assert(0 <= x && x < n);
            return x >= 2 && !sieve[x];
        }
        // prime factors of x in non-decreasing order, O(log x)
        vector<int> factorize(int x) const {
            assert(!lpf.empty() && 1 <= x && x < n);
            vector<int> res;
            for (; x > 1; x /= lpf[x])
                res.push_back(lpf[x]);
            return res;
        }
    };
    constexpr ull mul_mod(ull a, ull b, ull m) {
        if ((a | b) >> 32 == 0) // product fits in 64 bits, avoid the slow 128-bit division
            return a * b % m;
        return ull(__uint128_t(a) * b % m);
    }
    constexpr ull pow_mod(ull a, ull b, ull m) {
        ull res = 1 % m;
        for (a %= m; b; b >>= 1, a = mul_mod(a, a, m))
            if (b & 1)
                res = mul_mod(res, a, m);
        return res;
    }
    // deterministic Miller-Rabin for all 64-bit integers
    bool is_prime(ull x) {
        if (x < 2)
            return false;
        for (ull p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
            if (x % p == 0)
                return x == p;
        int s = countr_zero(x - 1);
        ull d = (x - 1) >> s;
        for (ull a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
            ull y = pow_mod(a, d, x);
            if (y == 0 || y == 1 || y == x - 1)
                continue;
            bool composite = true;
            for (int i = 1; i < s && composite; i++) {
                y = mul_mod(y, y, x);
                composite = y != x - 1;
            }
            if (composite)
                return false;
        }
        return true;
    }
    // returns a non-trivial factor of composite x
    ull pollard_rho(ull x) {
        if (x % 2 == 0)
            return 2;
        ull a = 0, b = 0, c = 1, prd = 2, q;
        auto f = [&](ull v) { return mul_mod(v, v, x) + c; };
        for (int k = 1; k % 40 || gcd(prd, x) == 1; k++) {
            if (a == b)
                a = ++c, b = f(a);
            if ((q = mul_mod(prd, max(a, b) - min(a, b), x)))
                prd = q;
            a = f(a), b = f(f(b));
        }
        return gcd(prd, x);
    }
    // prime factors of x in non-decreasing order, ~O(x^(1/4))
    vector<ull> factorize(ull x) {
        if (x <= 1)
            return {};
        if (is_prime(x))
            return {x};
        ull d = pollard_rho(x);
        auto l = factorize(d), r = factorize(x / d);
        vector<ull> res;
        merge(l.begin(), l.end(), r.begin(), r.end(), back_inserter(res));
        return res;
    }
} using namespace number_theory;
/*
 * prime_sieve ps(int n, bool with_lpf = false): primes in [0, n)
 * ps.prime_cnt() / ps[i] / ps.is_prime(x) / ps.factorize(x) (needs with_lpf)
 * is_prime(ull x): deterministic Miller-Rabin
 * factorize(ull x): sorted prime factors by Pollard rho
 */
/****** number theory(divisors primes...) algorithms ***/
