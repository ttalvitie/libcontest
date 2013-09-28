#pragma once
#include "boilerplate.hpp"

struct DiophantineSolution {
	Z x;
	Z y;
	Z dx;
	Z dy;
};

void assign(Z& a, Z& b, Z aval, Z bval) {
	a = aval;
	b = bval;
}

/// Solve linear diophantine equation ax + by = c. If there is no solution
/// (iff gcd(a, b) does not divide c), fails. Returns structure containing
/// a solution (x, y), all solutions are (x + t * dx, y + t * dy), for all
/// integers t. a and b must be nonzero.
DiophantineSolution solveLinearDiophantine(Z a, Z b, Z c) {
	if(a == 0 || b == 0) fail();
	
	Z A = a;
	Z B = b;
	
	// NOTE: the following chunk only if you need negative a,b,c.
	Z as = 1;
	Z bs = 1;
	if(a < 0) {
		a = -a;
		as = -as;
	}
	if(b < 0) {
		b = -b;
		bs = -bs;
	}
	if(c < 0) {
		c = -c;
		as = -as;
		bs = -bs;
	}
	
	Z x = 0, y = 1, lx = 1, ly = 0;
	while(b != 0) {
		Z q = a / b;
		assign(a, b, b, a % b);
		assign(x, lx, lx - q * x, x);
		assign(y, ly, ly - q * y, y);
	}
	
	if(c % a != 0) fail();
	Z coef = c / a;
	
	DiophantineSolution ret = {as * coef * lx, bs * coef * ly, B / a, -A / a};
	return ret;
}

