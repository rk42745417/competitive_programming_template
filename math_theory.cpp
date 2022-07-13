namespace math_theory {
	bool is_prime(ll x) {
		for(ll i = 2; i * i <= x; i++)
			if(x % i == 0)
				return false;
		return true;
	}
} using namespace math_theory;
/****** math theory(divisors primes...) algorithms ***/

