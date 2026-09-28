namespace number_theory {
    struct prime_sieve {
    private:
        vector<bool> sieve;
        vector<int> prime;
        int n;
    public:
        prime_sieve(int _n) : sieve(_n), n(_n) {
            for (int i = 2; i < n; i++) {
                if (!sieve[i])
                    prime.push_back(i);
                for (int p : prime) {
                    if (ll(i) * p >= n)
                        break;
                    sieve[i * p] = true;
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
    };
    bool is_prime(ull x) {
        if (x < 2)
            return false;
        for (ull i = 2; i <= x / i; i++)
            if (x % i == 0)
                return false;
        return true;
    }
} using namespace number_theory;
/****** number theory(divisors primes...) algorithms ***/
