#include "datastruct/treap.hpp"

#include "testutil.hpp"

int main() {
	for(int t = 0; t < 30; ++t) {
		Treap<int>* A = nullptr;
		set<int> B;
		double inc_prob = rand_real(0.0, 1.0);
		int range = rand_bool(0.5) ? rand_int(3, 1000) : rand_int(3, 100000000);
		for(int i = 0; i < 10000; ++i) {
			int x;
			if(rand_bool(inc_prob)) {
				x = i;
			} else {
				x = rand_int(-range, range);
			}
			
			addNode(A, x);
			B.insert(x);
			
			for(int j = 0; j < 10; ++j) {
				int y = rand_int(-range - 5, range + 5);
				Treap<int>* a = lowerBound(A, y);
				set<int>::iterator b = B.lower_bound(y);
				
				if((a == nullptr) != (b == B.end())) fail();
				if(b != B.end() && (a->elem != *b)) fail();
			}
		}
	}
	
	return 0;
}
