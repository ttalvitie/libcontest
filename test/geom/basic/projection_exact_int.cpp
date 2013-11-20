#define COORD_TYPE int

#include "geom/basic.hpp"

int main() {
	mt19937 rng;
	
	uniform_int_distribution<int> posdist(-10000, 10000);
	uniform_int_distribution<int> vecdist(-100, 100);
	uniform_int_distribution<int> coefdist(-100, 100);
	
	for(int i = 0; i < 10000; ++i) {
		V s(posdist(rng), posdist(rng));
		V v(vecdist(rng), vecdist(rng));
		int a = coefdist(rng);
		int b = coefdist(rng);
		if(projectionParam(s + a * v + b * V(0, 1) * v, s, s + v) != a) fail();
	}
	
	return 0;
}
