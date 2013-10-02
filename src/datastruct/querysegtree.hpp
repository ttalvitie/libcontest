#pragma once
#include "boilerplate.hpp"

/// Array [0, n[ -> Z with fast queries of A[i] (x) A[i + 1] (x) ... (x) A[j - 1]
/// for given i, j where (x) is the associative operation given by oper.
struct QuerySegmentTree {
	QuerySegmentTree(vector<int> src) {
		N = 1;
		while(N < src.size()) N *= 2;
		tree.resize(2 * N);
		copy(src.begin(), src.end(), tree.begin() + N);
		for(int x = N - 1; x != 0; --x) {
			tree[x] = oper(tree[2 * x], tree[2 * x + 1]);
		}
	}
	
	/// Query A[x] (x) A[x + 1] (x) ... (x) A[y - 1].
	Z query(int x, int y) {
		x += N;
		y += N;
		
		if(x == y) fail();
		if(x + 1 == y) return tree[x];
		
		Z a = tree[x];
		Z b = tree[--y];
		while(x / 2 != y / 2) {
			if(x % 2 == 0) a = oper(a, tree[x + 1]);
			if(y % 2 == 1) b = oper(tree[y - 1], b);
			
			x /= 2;
			y /= 2;
		}
		return oper(a, b);
	}
	
	/// Set A[x] to val.
	void set(int x, Z val) {
		x += N;
		tree[x] = val;
		x /= 2;
		while(x != 0) {
			tree[x] = oper(tree[2 * x], tree[2 * x + 1]);
			x /= 2;
		}
	}
	
	Z oper(Z a, Z b) {
#ifdef QUERYSEGMENTTREE_OPER
		return QUERYSEGMENTTREE_OPER(a, b);
#else
		return max(a, b);
#endif
	}
	
	int N;
	vector<Z> tree;
};