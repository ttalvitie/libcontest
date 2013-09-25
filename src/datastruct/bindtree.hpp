#pragma once
#include "boilerplate.hpp"

/// Array [0, n[ -> Z with fast query of sums [0, x[.
/// Initially set to zero.
struct BinIndexedTree {
	BinIndexedTree(int n) : n(n), tree(n + 1, 0) { }
	
	/// Add x to i:th value, 0 <= i < n.
	void change(int i, Z x) {
		++i;
		while(i <= n) {
			tree[i] += x;
			i += (i & -i);
		}
	}
	
	/// Get sum of elements [0, i[, 0 <= i <= n.
	Z sum(int i) {
		Z ret = 0;
		while(i != 0) {
			ret += tree[i];
			i -= (i & -i);
		}
		return ret;
	}
	
	
	
	int n;
	vector<Z> tree;
};
