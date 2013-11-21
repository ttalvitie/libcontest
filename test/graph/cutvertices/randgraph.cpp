#define COORD_TYPE int
#include "graph/cutvertices.hpp"

#include "testutil.hpp"

void dfs(int x, const vector<vector<int>>& G, vector<char>& visited) {
	if(visited[x]) return;
	visited[x] = true;
	for(int y : G[x]) {
		dfs(y, G, visited);
	}
}

vector<char> cmpImpl(const vector<vector<int>>& G) {
	int n = G.size();
	if(n == 0) return vector<char>();
	
	int comp2 = 0;
	{
		vector<char> visited(n, 0);
		for(int j = 0; j < n; ++j) {
			if(!visited[j]) {
				dfs(j, G, visited);
				++comp2;
			}
		}
	}
	
	vector<char> ret(n, 0);
	for(int i = 0; i < n; ++i) {
		vector<char> visited(n, 0);
		visited[i] = true;
		int comp = 0;
		for(int j = 0; j < n; ++j) {
			if(!visited[j]) {
				dfs(j, G, visited);
				++comp;
			}
		}
		
		bool only_self = true;
		for(int x : G[i]) {
			if(x != i) only_self = false;
		}
		if(comp != comp2 && !only_self) ret[i] = 1;
	}
	return ret;
}

int main() {
	for(int t = 0; t < 20000; ++t) {
		int V = rand_int(0, 50);
		int E = rand_int(0, rand_bool(0.5) ? 50 : 500);
		
		vector<vector<int>> G(V);
		if(V != 0) {
			for(int i = 0; i < E; ++i) {
				int a = rand_int(0, V - 1);
				int b = rand_int(0, V - 1);
				G[a].push_back(b);
				G[b].push_back(a);
			}
		}
		
		vector<char> res = computeCutvertices(G);
		vector<char> res2 = cmpImpl(G);
		
		if(res.size() != res2.size() || !equal(res.begin(), res.end(), res2.begin())) fail();
	}
	
	return 0;
}
