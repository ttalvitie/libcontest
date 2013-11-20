#include "geom/basic.hpp"

#include "testutil.hpp"

int main() {
	for(int t = 0; t < 2000000; ++t) {
		V c(rand_real(-1.0, 1.0), rand_real(-1.0, 1.0));
		V dir1(rand_real(-1.0, 1.0), rand_real(-1.0, 1.0));
		V dir2(rand_real(-1.0, 1.0), rand_real(-1.0, 1.0));
		dir1 /= abs(dir1);
		dir2 /= abs(dir2);
		
		if(abs(dir1 - dir2) < 0.1) continue;
		if(abs(dir1 + dir2) < 0.1) continue;
		
		double s1 = rand_real(-1.0, 1.0);
		double t1 = rand_real(-1.0, 1.0);
		double s2 = rand_real(-1.0, 1.0);
		double t2 = rand_real(-1.0, 1.0);
		
		if(abs(s1 - t1) < 0.1) continue;
		if(abs(s2 - t2) < 0.1) continue;
		
		V A = c + s1 * dir1;
		V B = c + t1 * dir1;
		V C = c + s2 * dir2;
		V D = c + t2 * dir2;
		
		A += V(rand_real(-1e-8, 1e-8));
		B += V(rand_real(-1e-8, 1e-8));
		C += V(rand_real(-1e-8, 1e-8));
		D += V(rand_real(-1e-8, 1e-8));
		
		double param = intersectionParam(A, B, C, D);
		V c2 = interpolate(param, A, B);
		
		if(abs(c - c2) > 1e-4) fail();
	}
	
	return 0;
}
