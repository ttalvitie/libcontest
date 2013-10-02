#include "datastruct/querysegtree.hpp"

#include <boost/random.hpp>

using namespace boost::random;

Z QuerySegmentTree::oper(Z a, Z b) {
	return a ^ b;
}

struct CmpImpl {
	CmpImpl(int n) : tree(n, 0) { }
	
	void set(int i, Z x) {
		tree[i] = x;
	}
	
	Z query(int i, int j) {
		Z ret = 0;
		for(int x = i; x < j; ++x) {
			ret = QuerySegmentTree::oper(ret, tree[x]);
		}
		return ret;
	}
	
	vector<Z> tree;
};

int main() {
	mt19937 rng;
	
	uniform_int_distribution<int> length_dist(1, 30);
	uniform_int_distribution<Z> val_dist(INT_MIN, INT_MAX);
	
	for(int t = 0; t < 1000; ++t) {
		int n = length_dist(rng);
		CmpImpl a(n);
		QuerySegmentTree b(std::vector<Z>(n, 0));
		
		uniform_int_distribution<int> ind_dist(0, max(n - 1, 0));
		for(int t2 = 0; t2 < 1000; ++t2) {
			for(int t3 = 0; t3 < 15; ++t3) {
				int i = ind_dist(rng);
				Z x = val_dist(rng);
				a.set(i, x);
				b.set(i, x);
			}
			
			int i = uniform_int_distribution<int>(0, n - 1)(rng);
			int j = uniform_int_distribution<int>(i + 1, n)(rng);
			Z A = a.query(i, j);
			Z B = b.query(i, j);
			if(A != B) fail();
		}
	}
	
	return 0;
}
