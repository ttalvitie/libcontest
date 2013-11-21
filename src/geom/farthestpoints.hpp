#pragma once
#include "boilerplate.hpp"

#include "geom/convexhull.hpp"

/// Find the distance between farthest points in 'points'.
/// NOTE: may not work for collinear cases with floating point coordinates.
VC computeFarthestPoints(const vector<V>& points) {
	vector<V> hull = computeConvexHull(points);
	int n = hull.size();
	
	if(n < 2) fail();
	if(n == 2) return abs(hull[0] - hull[1]);
	
	auto prev = [n](int i) {
		if(i == 0) return n - 1;
		return i - 1;
	};
	auto next = [n](int i) {
		if(i == n - 1) return 0;
		return i + 1;
	};
	
	int f = 0;
	double d = 0;
	
	int a = 0;
	int b = 1;
	for(int i = 0; i <= n; ++i) {
		d = max(d, abs(hull[a] - hull[f]));
		
		auto dist = [&](int x) {
			return pointLineDistance(hull[x], hull[a], hull[b]);
		};
		while(dist(next(f)) > dist(f)) {
			f = next(f);
			d = max(d, abs(hull[a] - hull[f]));
		}
		while(dist(prev(f)) > dist(f)) {
			f = prev(f);
			d = max(d, abs(hull[a] - hull[f]));
		}
		
		a = next(a);
		b = next(b);
	}
	
	return d;
}
