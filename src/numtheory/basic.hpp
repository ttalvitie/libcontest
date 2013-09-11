#pragma once
#include "boilerplate.hpp"

Z gcd_(Z a, Z b) {
	if(a == 0) return b;
	return gcd_(b % a, a);
}

/// Return the greatest common divisor of two integers. Returns 0 if a and b
/// are zero, otherwise result is always positive.
Z gcd(Z a, Z b) {
	return gcd_(abs(a), abs(b));
}

/// Return lookup table of primes in [0, n[. (1 for prime, 0 for non-prime).
vector<char> genPrimeTable(int n) {
	vector<char> ret(n, 1);
	if(n > 0) ret[0] = 0;
	if(n > 1) ret[1] = 0;
	for(int i = 2; i * i <= n; ++i) {
		int x = i * i;
		while(x < n) {
			ret[x] = 0;
			x += i;
		}
	}
	return ret;
}
