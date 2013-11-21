#pragma once
#include "boilerplate.hpp"

/// Compute the strongly connected components of a directed graph given as adjacency
/// lists. The result is a vector of the strongly connected components, each
/// given as a vector of vertex indices.
///
/// Uses Tarjan's algorithm, runs in O(V + E) time.
vector<vector<int>> computeStronglyConnectedComponents(const vector<vector<int>>& G) {
	int n = G.size();
	
	vector<int> ind(n, -1);
	vector<int> low(n);
	vector<int> parent(n, -1);
	vector<int> pos(n, 0);
	vector<char> in_tarj(n, 0);
	
	stack<int> dfs, tarj;
	
	int cur_ind = 0;
	
	vector<vector<int>> ret;
	for(int s = 0; s < n; ++s) {
		if(ind[s] != -1) continue;
		
		dfs.push(s);
		while(!dfs.empty()) {
			int v = dfs.top();
			dfs.pop();
			
			if(pos[v] == 0) {
				if(ind[v] != -1) fail();
				ind[v] = cur_ind;
				low[v] = cur_ind;
				++cur_ind;
				tarj.push(v);
				in_tarj[v] = 1;
			}
			
			if(pos[v] == G[v].size()) {
				if(parent[v] != -1) {
					low[parent[v]] = min(low[parent[v]], low[v]);
				}
				if(low[v] == ind[v]) {
					vector<int> comp;
					int r;
					do {
						r = tarj.top();
						tarj.pop();
						in_tarj[r] = 0;
						comp.push_back(r);
					} while(r != v);
					ret.push_back(move(comp));
				}
			} else {
				dfs.push(v);
				
				int x = G[v][pos[v]];
				if(ind[x] == -1) {
					parent[x] = v;
					dfs.push(x);
				} else if(in_tarj[x]) {
					low[v] = min(low[v], ind[x]);
				}
				
				++pos[v];
			}
		}
	}
	
	return ret;
}
