#include "datastruct/bindtree.hpp"
#include "datastruct/querysegtree.hpp"

#include <boost/random.hpp>

using namespace boost::random;

Z QuerySegmentTree::oper(Z a, Z b) {
	return a + b;
}

struct CmpImpl {
	CmpImpl(int n) : tree(n, 0) { }
	
	/// Add x to i:th value, 0 <= i < n.
	void change(int i, Z x) {
		tree[i] += x;
	}
	
	/// Get sum of elements [0, i[, 0 <= i <= n.
	Z sum(int i) {
		Z ret = 0;
		for(int j = 0; j < i; ++j) {
			ret += tree[j];
		}
		return ret;
	}
	
	vector<Z> tree;
};

int main() {
	mt19937 rng;
	
	uniform_int_distribution<int> length_dist(0, 50);
	uniform_int_distribution<Z> val_dist(INT_MIN, INT_MAX);
	
	for(int t = 0; t < 1000; ++t) {
		int n = length_dist(rng);
		BinIndexedTree a(n);
		CmpImpl b(n);
		QuerySegmentTree c(std::vector<Z>(n, 0));
		
		uniform_int_distribution<int> ind_dist(0, max(n - 1, 0));
		uniform_int_distribution<int> end_dist(0, n);
		for(int t2 = 0; t2 < 1000; ++t2) {
			if(n != 0) {
				for(int t3 = 0; t3 < 15; ++t3) {
					int i = ind_dist(rng);
					Z x = val_dist(rng);
					a.change(i, x);
					b.change(i, x);
					c.set(i, c.query(i, i + 1) + x);
				}
			}
			
			int i = end_dist(rng);
			Z A = a.sum(i);
			Z B = b.sum(i);
			Z C = 0;
			if(i != 0) C = c.query(0, i);
			if(A != B || B != C) fail();
		}
	}
	
	return 0;
}
