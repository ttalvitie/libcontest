#pragma once
#include "boilerplate.hpp"

/// Array [0, w[ x [0, h[ -> Z with fast query of sums [0, x[ x [0, y[.
/// Initially set to zero.
struct BinIndexedTree2D {
	BinIndexedTree2D(int w, int h) : w(w), h(h) {
		tree.resize(w + 1);
		for(vector<Z>& v : tree) v.resize(h + 1, 0);
	}
	
	/// Add v to i:th value, 0 <= x < w, 0 <= y < h.
	void change(int x, int y, Z v) {
		++x;
		++y;
		while(x <= w) {
			int t = y;
			while(t <= h) {
				tree[x][t] += v;
				t += (t & -t);
			}
			x += (x & -x);
		}
	}
	
	/// Get sum of elements [0, x[ x [0, y[, 0 <= x, y <= n.
	Z sum(int x, int y) {
		Z ret = 0;
		while(x != 0) {
			int t = y;
			while(t != 0) {
				ret += tree[x][t];
				t -= (t & -t);
			}
			x -= (x & -x);
		}
		return ret;
	}
	
	int w;
	int h;
	vector<vector<Z>> tree;
};
