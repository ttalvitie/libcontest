#pragma once
#include "boilerplate.hpp"

/// Array [0, w[ x [0, h[ -> Z with fast queries of given rectangles.
struct QuerySegmentTree2D {
	/// The associative and commutative operator to use. To be implemented by
	/// the user. Should output (0, 0) -> 0.
	static Z oper(Z a, Z b); // { return <result>; }
	
	// Initially set to 0.
	QuerySegmentTree2D(int w, int h) {
		++w;
		++h;
		W = 1;
		while(W < w) W *= 2;
		H = 1;
		while(H < h) H *= 2;
		tree.resize(2 * W);
		for(int i = 1; i < 2 * W; ++i) {
			tree[i].resize(2 * H, 0);
		}
	}
	
	/// Query from rectangle [x1, x2[ x [y1, y2[. Returns 0 if the set is empty.
	Z query(int x1, int y1, int x2, int y2) {
		if(x1 >= x2 || y1 >= y2) return 0;
		
		x1 += W;
		x2 += W + 1;
		y1 += H;
		y2 += H + 1;
		
		bool first = true;
		Z ret = 0;
		
		auto addCol = [&](int x) {
			auto add = [&](int y) {
				int u1 = x;
				int u2 = x;
				int v1 = y;
				int v2 = y;
				while(u1 < W) u1 *= 2;
				while(u2 < W) u2 = 2 * u2 + 1;
				while(v1 < H) v1 *= 2;
				while(v2 < H) v2 = 2 * v2 + 1;
				
				if(first) {
					ret = tree[x][y];
					first = false;
				} else {
					ret = oper(ret, tree[x][y]);
				}
			};
			
			int t1 = y1;
			int t2 = y2;
			while(t1 / 2 != t2 / 2) {
				if(t1 % 2 == 0) add(t1 + 1);
				if(t2 % 2 == 1) add(t2 - 1);
				
				t1 /= 2;
				t2 /= 2;
			}
		};
		
		while(x1 / 2 != x2 / 2) {
			if(x1 % 2 == 0) addCol(x1 + 1);
			if(x2 % 2 == 1) addCol(x2 - 1);
			
			x1 /= 2;
			x2 /= 2;
		}
		
		return ret;
	}
	
	/// Set A[x][y] to val.
	void set(int x, int y, Z val) {
		x += W + 1;
		y += H + 1;
		
		tree[x][y] = val;
		
		while(x != 0) {
			if(x < W) tree[x][y] = oper(tree[2 * x][y], tree[2 * x + 1][y]);
			
			int t = y;
			t /= 2;
			while(t != 0) {
				tree[x][t] = oper(tree[x][2 * t], tree[x][2 * t + 1]);
				
				t /= 2;
			}
			x /= 2;
		}
	}
	
	int W;
	int H;
	vector<vector<Z>> tree;
};