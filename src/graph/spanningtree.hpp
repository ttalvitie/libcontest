#pragma once
#include "boilerplate.hpp"

#include "datastruct/unionfind.hpp"

/// Find the minimum spanning tree of a graph with vertices 0,...,n-1 and
/// edges given by (weight, (vertex1, vertex2)) using Kruskal algorithm.
/// If the input graph is not connected, the result consists of spanning trees
/// for each component. The return value is a pair of the resulting forest and
/// its total weight.
/// Weight type may be replaced with any number type.
pair<vector<vector<int> >, double> kruskal(
	int n,
	vector<pair<double, pair<int, int> > > edges
) {
	sort(edges.begin(), edges.end());
	
	vector<vector<int> > span(n);
	double weight = 0.0;
	UnionFind c(n);
	for(int i = 0; i < edges.size(); ++i) {
		int v1 = edges[i].second.first;
		int v2 = edges[i].second.second;
		if(c.find(v1) != c.find(v2)) {
			c.merge(v1, v2);
			span[v1].push_back(v2);
			span[v2].push_back(v1);
			weight += edges[i].first;
		}
	}
	
	return pair<vector<vector<int> >, double>(span, weight);
}
