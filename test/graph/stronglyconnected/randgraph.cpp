#define COORD_TYPE int
#include "graph/stronglyconnected.hpp"

#include "testutil.hpp"

vector<vector<int>> cmpImpl(const vector<vector<int>>& G) {
	int n = G.size();
	vector<vector<char>> M(n, vector<char>(n, 0));
	
	for(int x = 0; x < n; ++x) {
		M[x][x] = 1;
		for(int y : G[x]) {
			M[x][y] = 1;
		}
	}
	
	while(true) {
		bool change = false;
		for(int x = 0; x < n; ++x) {
			for(int y = 0; y < n; ++y) {
				if(!M[x][y]) continue;
				for(int z = 0; z < n; ++z) {
					if(!M[y][z]) continue;
					if(!M[x][z]) change = true;
					M[x][z] = 1;
				}
			}
		}
		if(!change) break;
	}
	
	vector<vector<int>> ret;
	vector<char> seen(n, 0);
	for(int x = 0; x < n; ++x) {
		if(seen[x]) continue;
		vector<int> comp;
		for(int y = 0; y < n; ++y) {
			if(!M[x][y] || !M[y][x]) continue;
			if(seen[y]) fail();
			seen[y] = true;
			comp.push_back(y);
		}
		ret.push_back(move(comp));
	}
	
	return ret;
}

int main() {
	for(int t = 0; t < 20000; ++t) {
		int V = rand_int(0, 50);
		int E = rand_int(0, rand_bool(0.5) ? 100 : 1000);
		
		vector<vector<int>> G(V);
		if(V != 0) {
			for(int i = 0; i < E; ++i) {
				int a = rand_int(0, V - 1);
				int b = rand_int(0, V - 1);
				G[a].push_back(b);
			}
		}
		vector<vector<int>> res = computeStronglyConnectedComponents(G);
		for(vector<int>& v : res) sort(v.begin(), v.end());
		sort(
			res.begin(), res.end(),
			[](const vector<int>& a, const vector<int>& b) { return a.front() < b.front(); }
		);
		
		vector<vector<int>> cmp = cmpImpl(G);
		
		if(res.size() != cmp.size()) fail();
		for(int i = 0; i < res.size(); ++i) {
			if(res[i].size() != cmp[i].size()) fail();
			if(!equal(res[i].begin(), res[i].end(), cmp[i].begin())) fail();
		}
	}
	
	return 0;
}
