#include "geom/basic.hpp"

int main() {
	mt19937 rng;
	
	uniform_real_distribution<double> posdist(-1e4, 1e4);
	uniform_real_distribution<double> distdist(1, 1e4);
	uniform_real_distribution<double> angledist(-PI, PI);
	uniform_real_distribution<double> angle2dist(0.1, 3.1);
	
	for(int i = 0; i < 10000; ++i) {
		V a(posdist(rng), posdist(rng));
		double a1 = angledist(rng);
		double a2 = a1 + angle2dist(rng);
		V b = a + distdist(rng) * exp(V(0, a1));
		V c = a + distdist(rng) * exp(V(0, a2));
		if(!ccw(a, b, c)) fail();
		if(ccw(a, c, b)) fail();
	}
	
	return 0;
}
