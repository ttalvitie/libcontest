#pragma once
#include "boilerplate.hpp"

#include "geom/basic.hpp"

/// Compute the convex hull of given set of points. The points on the edges
/// of the hull are not listed in the result (if floating point numbers are
/// used, inaccuracy may cause them to be listed).
///
/// Runs in linear time, uses Andrew's monotone chain algorithm.
vector<V> computeConvexHull(vector<V> points) {
	auto cmp = [](V a, V b) {
		if(a.real() == b.real()) {
			return a.imag() < b.imag();
		} else {
			return a.real() < b.real();
		}
	};
	sort(points.begin(), points.end(), cmp);
	points.erase(unique(points.begin(), points.end()), points.end());
	
	int n = points.size();
	if(n <= 2) return points;
	
	vector<V> hull;
	hull.push_back(points[0]);
	for(int dir = 0; dir != 2; ++dir) {
		if(dir) reverse(points.begin(), points.end());
		
		int start = hull.size();
		for(int i = 1; i < n; ++i) {
			while(
				hull.size() > start &&
				!ccw(hull[hull.size() - 2], hull.back(), points[i])
			) {
				hull.pop_back();
			}
			hull.push_back(points[i]);
		}
	}
	hull.pop_back();
	
	return hull;
}
