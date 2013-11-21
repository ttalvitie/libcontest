#pragma once
#include "boilerplate.hpp"

/// Compute the sorted vector with value 1 for vertex iff it is a cutvertex.
/// The graph is given as adjacency lists.
///
/// Uses Hopcroft-Tarjan algorithm, runs in O(V + E) time.
vector<char> computeCutvertices(const vector<vector<int>>& G) {
	int n = G.size();
	
	if(n == 0) return vector<char>();
	
	vector<int> pos(n, 0);
	vector<int> parent(n);
	vector<int> depth(n, -1);
	vector<int> lowpoint(n);
	vector<int> prevchild(n, -1);
	vector<char> ret(n, 0);
	stack<int> S;
	
	for(int r = 0; r < n; ++r) {
		if(depth[r] != -1) continue;
		
		depth[r] = 0;
		parent[r] = -1;
		lowpoint[r] = 0;
		int rootchildren = 0;
		S.push(r);
		
		while(!S.empty()) {
			int v = S.top();
			
			if(prevchild[v] != -1) {
				if(v != r && lowpoint[prevchild[v]] >= depth[v]) {
					ret[v] = 1;
				}
				
				lowpoint[v] = min(lowpoint[v], lowpoint[prevchild[v]]);
				
				prevchild[v] = -1;
			}
			
			if(pos[v] == G[v].size()) {
				if(v == r && rootchildren >= 2) ret[r] = 1;
				for(int x : G[v]) {
					if(x == parent[v]) continue;
					lowpoint[v] = min(lowpoint[v], depth[x]);
				}
				
				S.pop();
			} else {
				int x = G[v][pos[v]++];
				
				if(depth[x] == -1) {
					if(v == r) ++rootchildren;
					
					prevchild[v] = x;
					
					depth[x] = depth[v] + 1;
					parent[x] = v;
					lowpoint[x] = depth[x];
					S.push(x);
				}
			}
		}
	}
	
	return ret;
}
