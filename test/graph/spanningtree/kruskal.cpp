#include "graph/spanningtree.hpp"

void findComponent(const vector<vector<int> >& G, int v, set<int>& c) {
	c.insert(v);
	for(int i = 0; i < G[v].size(); ++i) {
		int x = G[v][i];
		if(c.count(x)) continue;
		findComponent(G, x, c);
	}
}

bool sameComponents(const vector<vector<int> >& A, const vector<vector<int> >& B) {
	if(A.size() != B.size()) return false;
	int n = A.size();
	set<int> found;
	for(int v = 0; v < n; ++v) {
		if(found.count(v)) continue;
		set<int> cA, cB;
		findComponent(A, v, cA);
		findComponent(B, v, cB);
		if(cA.size() != cB.size()) return false;
		if(!std::equal(cA.begin(), cA.end(), cB.begin())) return false;
		
		for(set<int>::iterator i = cA.begin(); i != cA.end(); ++i) {
			found.insert(*i);
		}
	}
	
	return true;
}

void failIfNotTreeComponent(const vector<vector<int> >& G, int v, int from = -1, int level = 0) {
	if(level == G.size()) fail();
	for(int i = 0; i < G[v].size(); ++i) {
		int x = G[v][i];
		if(x == from) continue;
		failIfNotTreeComponent(G, x, v, 1);
	}
}

int main() {
	mt19937 rng;
	uniform_int_distribution<int> size_dist(0, 40);
	
	for(int t = 0; t < 10000; ++t) {
		int n = size_dist(rng);
		
		uniform_int_distribution<int> edgecount_dist(0, 5 * n);
		int edgecount = edgecount_dist(rng);
		if(n < 2) edgecount = 0;
		uniform_int_distribution<int> weight_dist(0, 12);
		
		vector<pair<double, pair<int, int> > > edges;
		for(int i = 0; i < edgecount; ++i) {
			uniform_int_distribution<int> vertex_dist(0, n - 1);
			int v1 = vertex_dist(rng);
			int v2 = v1;
			while(v1 == v2) v2 = vertex_dist(rng);
			
			edges.push_back(pair<double, pair<int, int> >(
				weight_dist(rng),
				pair<int, int>(v1, v2)
			));
		}
		
		vector<vector<int> > graph(n);
		for(int i = 0; i < edgecount; ++i) {
			int v1 = edges[i].second.first;
			int v2 = edges[i].second.second;
			graph[v1].push_back(v2);
			graph[v2].push_back(v1);
		}
		
		pair<vector<vector<int> >, double> p = kruskal(n, edges);
		
		if(!sameComponents(graph, p.first)) fail();
		
		for(int v = 0; v < n; ++v) {
			failIfNotTreeComponent(p.first, v);
		}
		
		double weight = 0.0;
		for(int x = 0; x < n; ++x) {
			for(int i = 0; i < p.first[x].size(); ++i) {
				int y = p.first[x][i];
				
				double best = 1.0 / 0.0;
				for(int ei = 0; ei < edges.size(); ++ei) {
					if(
						(edges[ei].second.first == x && edges[ei].second.second == y) ||
						(edges[ei].second.first == y && edges[ei].second.second == x)
					) {
						best = min(best, edges[ei].first);
					}
				}
				weight += best;
			}
		}
		
		if(weight != 2.0 * p.second) fail();
	}
	
	return 0;
}
