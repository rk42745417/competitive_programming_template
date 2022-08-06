namespace number_theory {
    struct prime_sieve {
        private:
            vector<bool> sieve;
            vector<int> prime;
            int n;
        public:
            prime_sieve(int _n): n(_n) {
                sieve.resize(n);
                for(int i = 2; i < n; i++) {
                    if(!sieve[i])
                        prime.push_back(i);
                    for(int p : prime) {
                        if(1LL * i * p >= n)
                            break;
                        sieve[i * p] = true;
                        if(i % p == 0)
                            break;
                    }
                }
            }
            inline size_t prime_cnt() { return prime.size(); }
            inline int operator[](int x) {
                assert(0 <= x && x < prime.size());
                return prime[x];
            }
            inline bool is_prime(int x) {
                assert(0 <= x && x < n);
                return !sieve[x];
            }
    };
    bool is_prime(ull x) {
        for(ull i = 2; i * i <= x; i++)
            if(x % i == 0)
                return false;
        return true;
    }
} using namespace number_theory;
/****** number theory(divisors primes...) algorithms ***/

