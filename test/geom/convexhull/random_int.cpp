#define COORD_TYPE int
#include "geom/convexhull.hpp"

#include "testutil.hpp"

bool isPointOnEdge(V p, V a, V b) {
	if(!collinear(p, a, b)) return false;
	V d1 = p - a;
	V d2 = p - b;
	if(d1 != 0 && d2 != 0) {
		if((d1.real() > 0) != (d2.real() < 0)) return false;
		if((d1.imag() > 0) != (d2.imag() < 0)) return false;
	}
	return true;
}

int main() {
	for(int t = 0; t < 200000; ++t) {
		int n = rand_int(0, rand_bool(0.3) ? 10 : 50);
		int bound = rand_int(0, 100);
		vector<V> points;
		for(int i = 0; i < n; ++i) {
			points.push_back(V(rand_int(-bound, bound), rand_int(-bound, bound)));
		}
		
		vector<V> hull = computeConvexHull(points);
		
		if(hull.size() == 0) {
			if(points.size() != 0) fail();
			continue;
		}
		if(n == 0) fail();
		if(hull.size() == 1) {
			for(V v : points) {
				if(v != hull[0]) fail();
			}
			continue;
		}
		if(hull.size() == 2) {
			if(hull[0] == hull[1]) fail();
			bool found0 = false;
			bool found1 = false;
			for(V v : points) {
				if(v == hull[0]) found0 = true;
				if(v == hull[1]) found1 = true;
				if(!isPointOnEdge(v, hull[0], hull[1])) fail();
			}
			if(!found0) fail();
			if(!found1) fail();
			
			continue;
		}
		
		// Check that the hull is convex.
		{
			V x = hull[hull.size() - 2];
			V y = hull[hull.size() - 1];
			for(V z : hull) {
				if(!ccw(x, y, z)) fail();
				
				x = y;
				y = z;
			}
		}
		
		// Check that the hull doesn't go around multiple times, i.e. has only
		// one local maximum.
		{
			auto vec_less = [](V a, V b) {
				if(a.imag() == b.imag()) {
					return a.real() < b.real();
				} else {
					return a.imag() < b.imag();
				}
			};
			
			V x = hull[hull.size() - 2];
			V y = hull[hull.size() - 1];
			bool max_found = false;
			for(V z : hull) {
				if(vec_less(x, y) && vec_less(z, y)) {
					if(max_found) fail();
					max_found = true;
				}
				
				x = y;
				y = z;
			}
			if(!max_found) fail();
		}
		
		// Check that all hull vertices are in points.
		for(V v : hull) {
			bool found = false;
			for(V v2 : points) {
				if(v == v2) found = true;
			}
			if(!found) fail();
		}
		
		// Check that all points are contained in the hull.
		for(V p : points) {
			bool inside = false;
			V x = hull.back();
			for(V y : hull) {
				if(isPointOnEdge(p, x, y)) {
					inside = true;
					break;
				}
				
				if(x.imag() <= p.imag() && p.imag() < y.imag()) {
					if(ccw(x, y, p)) inside = !inside;
				}
				if(y.imag() <= p.imag() && p.imag() < x.imag()) {
					if(ccw(y, x, p)) inside = !inside;
				}
				
				x = y;
			}
			if(!inside) fail();
		}
	}
	
	return 0;
}
