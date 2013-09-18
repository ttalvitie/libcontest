#pragma once
#include "boilerplate.hpp"

/// Data structure containing a subdivision of set 0,...,n-1. Each set has a
/// representative element of the set, and two sets can be merged fast.
/// Initially each element is in its own set.
struct UnionFind {
	UnionFind(int n) : parent(n) {
		for(int i = 0; i < n; ++i) {
			parent[i] = i;
		}
	}
	
	/// Find the representative element for set containing x.
	int find(int x) {
		if(parent[x] != x) {
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}
	
	/// Merge sets containing x and y.
	void merge(int x, int y) {
		x = find(x);
		y = find(y);
		parent[x] = y;
	}
	
	vector<int> parent;
};
