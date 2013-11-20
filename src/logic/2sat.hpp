#pragma once
#include "boilerplate.hpp"

typedef pair<int, bool> PIB;

/// Solve 2SAT-problem, i.e. find assignments of x_0...x_(n-1) to true or false
/// such that all clauses in 'clauses' hold. The clauses are given as
/// ((i1, v1), (i2, v2)), and a clause holds if x_i1 == v1 or x_i2 == v2.
/// The function returns true if there is such an assignment and replaces the
/// content of 'solution' to one solution, otherwise returns false.
bool solve2SAT(int n, const vector<pair<PIB, PIB>>& clauses, vector<char>& solution) {
	vector<vector<PIB>> imp[2];
	imp[0].resize(n);
	imp[1].resize(n);
	
	for(pair<PIB, PIB> clause : clauses) {
		PIB a = clause.first;
		PIB b = clause.second;
		imp[!a.second][a.first].push_back(b);
		imp[!b.second][b.first].push_back(a);
	}
	
	vector<char> isset[2];
	vector<char> val[2];
	vector<int> log[2];
	vector<int> stack[2];
	vector<int> pos[2];
	
	for(int b = 0; b < 2; ++b) {
		isset[b].resize(n, false);
		val[b].resize(n);
		pos[b].resize(n);
	}
	
	int win = 0;
	for(int i = 0; i < n; ++i) {
		if(isset[0][i]) continue;
		
		bool failed[2] = {false, false};
		
		for(int b = 0; b < 2; ++b) {
			isset[b][i] = true;
			val[b][i] = b;
			pos[b][i] = 0;
			
			log[b].clear();
			stack[b].clear();
			
			log[b].push_back(i);
			stack[b].push_back(i);
		}
		
		win = -1;
		while(win == -1 && !(failed[0] && failed[1])) {
			for(int b = 0; b < 2; ++b) {
				if(failed[b]) continue;
				if(stack[b].empty()) {
					win = b;
					break;
				}
				
				int x = stack[b].back();
				bool v = val[b][x];
				
				if(pos[b][x] == imp[v][x].size()) {
					stack[b].pop_back();
				} else {
					PIB p = imp[v][x][pos[b][x]++];
					
					int y = p.first;
					if(isset[b][y]) {
						if(val[b][y] != p.second) {
							failed[b] = true;
							continue;
						}
					} else {
						isset[b][y] = true;
						val[b][y] = p.second;
						log[b].push_back(y);
						
						pos[b][y] = 0;
						stack[b].push_back(y);
					}
				}
			}
		}
		if(win == -1) break;
		
		int lose = 1 - win;
		for(int v : log[lose]) {
			isset[lose][v] = false;
		}
		for(int v : log[win]) {
			isset[lose][v] = true;
			val[lose][v] = val[win][v];
		}
	}
	if(win == -1) return false;
	
	solution = move(val[0]);
	return true;
}
