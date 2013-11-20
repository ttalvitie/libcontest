#define COORD_TYPE int

#include "geom/basic.hpp"

int main() {
	mt19937 rng;
	
	uniform_int_distribution<int> posdist(-10000, 10000);
	uniform_int_distribution<int> vecdist(-1000, 1000);
	uniform_int_distribution<int> coefdist(-10, 10);
	
	// Check positive results.
	for(int i = 0; i < 10000; ++i) {
		V a(posdist(rng), posdist(rng));
		V v(vecdist(rng), vecdist(rng));
		int c1 = 0;
		if(i > 1000) c1 = coefdist(rng);
		int c2 = coefdist(rng);
		V b = a + c1 * v;
		V c = a + c2 * v;
		if(!collinear(a, b, c)) fail();
	}
	
	uniform_int_distribution<int> smallposdist(500, 515);
	
	// Check consistency with ccw.
	for(int i = 0; i < 10000; ++i) {
		V a(smallposdist(rng), smallposdist(rng));
		V b(smallposdist(rng), smallposdist(rng));
		V c(smallposdist(rng), smallposdist(rng));
		
		if(ccw(a, b, c) || ccw(a, c, b)) {
			if(collinear(a, b, c)) fail();
		} else {
			if(!collinear(a, b, c)) fail();
		}
	}
	
	return 0;
}
