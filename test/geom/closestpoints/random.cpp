#include "geom/closestpoints.hpp"

#include "testutil.hpp"

int main() {
	for(int t = 0; t < 100000; ++t) {
		int n = rand_int(2, 40);
		vector<V> points;
		for(int i = 0; i < n; ++i) {
			points.push_back(V(rand_real(-1.0, 1.0), rand_real(-1.0, 1.0)));
		}
		
		double d = computeClosestPoints(points);
		double cmpd = 100;
		for(int i = 0; i < n; ++i) {
			for(int j = i + 1; j < n; ++j) {
				cmpd = min(cmpd, abs(points[i] - points[j]));
			}
		}
		
		if(d != cmpd) fail();
	}
	
	return 0;
}
