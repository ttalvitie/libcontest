#include "numtheory/diophantine.hpp"
#include "numtheory/basic.hpp"

DiophantineSolution bruteSolve(Z a, Z b, Z c) {
	Z x = 0;
	Z x1 = -1;
	Z y1 = -1;
	Z x2 = -1;
	Z y2 = -1;
	while(true) {
		if((c - a * x) % b == 0) {
			if(x1 == -1) {
				x1 = x;
				y1 = (c - a * x) / b;
				++x;
				continue;
			} else {
				x2 = x;
				y2 = (c - a * x) / b;
				break;
			}
		}
		++x;
	}
	
	DiophantineSolution ret = {x1, y1, x2 - x1, y2 - y1};
	return ret;
}

void cmpSol(DiophantineSolution s1, DiophantineSolution s2) {
	if(!((s1.dx == s2.dx && s1.dy == s2.dy) || (s1.dx == -s2.dx && s1.dy == -s2.dy))) fail();
	int m = (s2.x - s1.x) / s1.dx;
	if(s2.x != s1.x + m * s1.dx || s2.y != s1.y + m * s1.dy) fail();
}

int main() {
	// Non-zero cases.
	for(int a = -100; a < 100; ++a) {
		if(a == 0) continue;
		for(int b = -100; b < 100; ++b) {
			if(b == 0) continue;
			int g = gcd(a, b);
			for(int c = -20 * g; c < 20 * g; c += g) {
				DiophantineSolution s1 = bruteSolve(a, b, c);
				DiophantineSolution s2 = solveLinearDiophantine(a, b, c);
				cmpSol(s1, s2);
			}
		}
	}
	
	return 0;
}
