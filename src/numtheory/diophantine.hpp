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
	if(a < 0 || b < 0 || c < 0) {
		DiophantineSolution ret = solveLinearDiophantine(abs(a), abs(b), abs(c));
		
		if((a < 0) != (c < 0)) {
			ret.x *= -1;
			ret.dx *= -1;
		}
		if((b < 0) != (c < 0)) {
			ret.y *= -1;
			ret.dy *= -1;
		}
		
		return ret;
	}
	
	Z d = a;
	Z e = b;
	
	Z x = 0, y = 1, lx = 1, ly = 0;
	while(e != 0) {
		Z q = d / e;
		assign(d, e, e, d % e);
		assign(x, lx, lx - q * x, x);
		assign(y, ly, ly - q * y, y);
	}
	
	if(c % d != 0) fail();
	Z coef = c / d;
	
	DiophantineSolution ret = {coef * lx, coef * ly, b / d, -a / d};
	return ret;
}

