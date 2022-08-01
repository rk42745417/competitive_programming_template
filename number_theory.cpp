namespace number_theory {
	bool is_prime(ull x) {
		for(ull i = 2; i * i <= x; i++)
			if(x % i == 0)
				return false;
		return true;
	}
} using namespace number_theory;
/****** number theory(divisors primes...) algorithms ***/

