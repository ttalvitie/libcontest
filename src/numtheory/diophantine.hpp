#pragma once
#include "boilerplate.hpp"

struct DiophantineSolution {
	int64_t x;
	int64_t y;
	int64_t dx;
	int64_t dy;
};

void assign(int64_t& a, int64_t& b, int64_t aval, int64_t bval) {
	a = aval;
	b = bval;
}

/// Solve linear diophantine equation ax + by = c. If there is no solution
/// (iff gcd(a, b) does not divide c), fails. Returns structure containing
/// a solution (x, y), all solutions are (x + t * dx, y + t * dy), for all
/// integers t. a and b must be nonzero. |a|, |b| and |c| should have couple
/// of high bits zero so that computations do not overflow.
DiophantineSolution solveLinearDiophantine(int64_t a, int64_t b, int64_t c) {
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
	
	int64_t d = a;
	int64_t e = b;
	
	int64_t x = 0, y = 1, lx = 1, ly = 0;
	while(e != 0) {
		int64_t q = d / e;
		assign(d, e, e, d % e);
		assign(x, lx, lx - q * x, x);
		assign(y, ly, ly - q * y, y);
	}
	
	if(c % d != 0) fail();
	int64_t coef = c / d;
	
	DiophantineSolution ret;
	ret.x = 0;
	ret.y = 0;
	ret.dx = b / d;
	ret.dy = -a / d;
	
	int64_t B = int64_t(1) << 62;
	for(int i = 0; i <= 62; ++i) {
		ret.x <<= 1;
		ret.y <<= 1;
		
		if(coef & B) {
			ret.x += lx;
			ret.y += ly;
		}
		
		int64_t t = (ret.y - ret.x) / (ret.dx - ret.dy);
		ret.x += t * ret.dx;
		ret.y += t * ret.dy;
		
		B >>= 1;
	}
	
	return ret;
}

