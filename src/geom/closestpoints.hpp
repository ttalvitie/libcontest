#pragma once
#include "boilerplate.hpp"

/// Find the distance between closest points in 'points'.
VC computeClosestPoints(vector<V> points) {
	int n = points.size();
	
	if(n < 2) fail();
	
	auto cmpx = [](V a, V b) { return a.real() < b.real(); };
	auto cmpy = [](V a, V b) { return a.imag() < b.imag(); };
	
	sort(points.begin(), points.end(), cmpx);
	
	vector<V> sorty = points;
	vector<V> sorty2(n);
	vector<V> tmp;
	
	VC d = abs(points[1] - points[0]);
	
	int x = 1;
	while(x < n) {
		for(int a = 0; a < n; a += 2 * x) {
			auto u = sorty.begin() + a;
			auto v = sorty.begin() + min(a + x, (int)sorty.size());
			auto w = sorty.begin() + min(a + 2 * x, (int)sorty.size());
			
			tmp.clear();
			for(auto i = v; i != w; ++i) {
				if(i->real() <= points[a + x - 1].real() + d) tmp.push_back(*i);
			}
			
			for(auto i = u; i != v; ++i) {
				auto f = lower_bound(tmp.begin(), tmp.end(), V(0, i->imag() - d), cmpy);
				while(f != tmp.end() && f->imag() <= i->imag() + d) {
					d = min(d, abs(*f - *i));
					++f;
				}
			}
			
			merge(u, v, v, w, sorty2.begin() + a, cmpy);
		}
		
		swap(sorty, sorty2);
		
		x <<= 1;
	}
	
	return d;
}
