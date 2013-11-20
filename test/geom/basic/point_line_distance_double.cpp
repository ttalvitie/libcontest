#include "geom/basic.hpp"

#include "testutil.hpp"

int main() {
	double pi = 4 * atan(1);
	for(int t = 0; t < 2000000; ++t) {
		V a(rand_real(-1.0, 1.0), rand_real(-1.0, 1.0));
		V b(rand_real(-1.0, 1.0), rand_real(-1.0, 1.0));
		V dir = b - a;
		dir /= abs(dir);
		
		if(rand_bool(0.5)) {
			double t = rand_real(0.0, 1.0);
			double dist = rand_real(-1.0, 1.0);
			V x = interpolate(t, a, b) + dist * dir * V(0, 1);
			dist = abs(dist);
			if(abs(dist - pointSegmentDistance(x, a, b)) > 1e-5) fail();
			if(abs(dist - pointLineDistance(x, a, b)) > 1e-5) fail();
		} else {
			V c = exp(V(0, rand_real(-0.5 * pi, 0.5 * pi)));
			double dist = rand_real(0.0, 1.0);
			V x;
			if(rand_bool(0.5)) {
				x = b + dir * c * dist;
			} else {
				x = a - dir * c * dist;
			}
			if(abs(dist - pointSegmentDistance(x, a, b)) > 1e-5) fail();
			if(abs(abs(c.imag()) * dist - pointLineDistance(x, a, b)) > 1e-5) fail();
		}
	}
	
	return 0;
}
