#include "graph/maxflow.hpp"

int main() {
	mt19937 rng;
	uniform_int_distribution<int> sizedist(2, 40);
	uniform_int_distribution<int> edgecountdist(0, 200);
	uniform_int_distribution<int> capacitydist(0, 1000);
	
	for(int i = 0; i < 10000; ++i) {
		int size = sizedist(rng);
		
		uniform_int_distribution<int> vertdist(0, size - 1);
		
		int s = vertdist(rng);
		int t = vertdist(rng);
		while(t == s) t = vertdist(rng);
		
		EdmondsKarp ek(size);
		
		int edgecount = edgecountdist(rng);
		for(int j = 0; j < edgecount; ++j) {
			int a = vertdist(rng);
			int b = vertdist(rng);
			int cap = capacitydist(rng);
			ek.addEdge(a, b, cap);
		}
		
		int flow1 = ek.maxFlow(s, t);
		
		// Test balance.
		vector<int> L(size, 0);
		for(int i = 0; i < size; ++i) {
			for(int j = 0; j < ek.G[i].size(); ++j) {
				if(ek.G[i][j].flow > 0) {
					L[i] -= ek.G[i][j].flow;
					L[ek.G[i][j].dest] += ek.G[i][j].flow;
				}
			}
		}
		for(int i = 0; i < size; ++i) {
			if(i == s) {
				if(L[i] != -flow1) fail();
			} else if(i == t) {
				if(L[i] != flow1) fail();
			} else {
				if(L[i] != 0) fail();
			}
		}
		
		// Test that there are no augmenting paths.
		std::vector<char> found(size, false);
		queue<int> Q;
		Q.push(s);
		found[s] = true;
		while(!Q.empty()) {
			int v = Q.front();
			Q.pop();
			if(v == t) fail();
			for(int j = 0; j < ek.G[v].size(); ++j) {
				if(ek.G[v][j].flow == ek.G[v][j].cap) continue;
				int x = ek.G[v][j].dest;
				if(found[x]) continue;
				Q.push(x);
				found[x] = true;
			}
		}
	}
	
	return 0;
}
