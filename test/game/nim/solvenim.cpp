#define INT_TYPE long long int
#include "game/nim.hpp"

#include <boost/random.hpp>

using namespace boost::random;

int main() {
	mt19937 rng;
	
	for(int n = 0; n < 10; ++n) {
		// Random check that winning strategies work.
		uniform_int_distribution<Z> heapsize_dist(0, 1000000000000000L);
		vector<Z> h(n);
		for(int t = 0; t < 10000; ++t) {
			for(int i = 0; i < n; ++i) {
				h[i] = heapsize_dist(rng);
			}
			int odote = 0;
			while(true) {
				bool nol = true;
				for(int i = 0; i < n; ++i) {
					if(h[i] != 0) nol = false;
				}
				if(nol) {
					if(solveNim(h) != pair<int, Z>(-1, -1)) fail();
					break;
				}
				
				pair<int, Z> p = solveNim(h);
				if(odote != 0) {
					if(odote == 1) {
						if(p.first == -1) fail();
					} else {
						if(p.first != -1) fail();
					}
				}
				if(p.first == -1) {
					bool loyty = false;
					for(int i = 0; i < n; ++i) {
						if(h[i] != 0) {
							loyty = true;
							h[i] -= uniform_int_distribution<Z>(1, h[i])(rng);
							break;
						}
					}
					if(!loyty) fail();
					odote = 1;
				} else {
					if(p.second > h[p.first]) fail();
					h[p.first] -= p.second;
					odote = -1;
				}
			}
		}
	}
	
	return 0;
}
