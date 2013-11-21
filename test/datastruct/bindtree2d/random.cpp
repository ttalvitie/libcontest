#include "datastruct/bindtree2d.hpp"
#include "datastruct/querysegtree.hpp"

struct CmpImpl {
	CmpImpl(int w, int h) : tree(w, vector<Z>(h, 0)) { }
	
	void change(int x, int y, Z v) {
		tree[x][y] += v;
	}
	
	Z sum(int x, int y) {
		Z ret = 0;
		for(int i = 0; i < x; ++i) {
			for(int j = 0; j < y; ++j) {
				ret += tree[i][j];
			}
		}
		return ret;
	}
	
	vector<vector<Z>> tree;
};

int main() {
	mt19937 rng;
	
	uniform_int_distribution<int> length_dist(0, 30);
	uniform_int_distribution<Z> val_dist(INT_MIN, INT_MAX);
	
	for(int t = 0; t < 1000; ++t) {
		int w = length_dist(rng);
		int h = length_dist(rng);
		BinIndexedTree2D a(w, h);
		CmpImpl b(w, h);
		
		uniform_int_distribution<int> indx_dist(0, max(w - 1, 0));
		uniform_int_distribution<int> indy_dist(0, max(h - 1, 0));
		uniform_int_distribution<int> endx_dist(0, w);
		uniform_int_distribution<int> endy_dist(0, h);
		for(int t2 = 0; t2 < 1000; ++t2) {
			if(w != 0 && h != 0) {
				for(int t3 = 0; t3 < 15; ++t3) {
					int x = indx_dist(rng);
					int y = indy_dist(rng);
					Z v = val_dist(rng);
					a.change(x, y, v);
					b.change(x, y, v);
				}
			}
			
			int x = endx_dist(rng);
			int y = endy_dist(rng);
			Z A = a.sum(x, y);
			Z B = b.sum(x, y);
			if(A != B) fail();
		}
	}
	
	return 0;
}
