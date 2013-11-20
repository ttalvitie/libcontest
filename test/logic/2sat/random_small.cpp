#include "logic/2sat.hpp"

#include "testutil.hpp"

bool hasSolution(
	int n,
	const vector<vector<tuple<bool, int, bool>>>& checks,
	vector<int>& choices
) {
	if(choices.size() == n) return true;
	int i = choices.size();
	
	for(int vali = 0; vali < 2; ++vali) {
		bool val = vali;
		choices.push_back(val);
		
		bool ok = true;
		for(const tuple<bool, int, bool>& check : checks[i]) {
			bool mval;
			int oi;
			bool oval;
			tie(mval, oi, oval) = check;
			if(val == mval) continue;
			if(choices[oi] == oval) continue;
			ok = false;
		}
		
		if(ok && hasSolution(n, checks, choices)) return true;
		
		choices.pop_back();
	}
	
	return false;
}

int main() {
	for(int t = 0; t < 100000; ++t) {
		int n = rand_int(0, 20);
		int m = rand_int(0, 120);
		if(n == 0) m = 0;
		
		vector<pair<PIB, PIB>> clauses;
		for(int i = 0; i < m; ++i) {
			int a = rand_int(0, n - 1);
			int b = rand_int(0, n - 1);
			clauses.emplace_back(PIB(a, rand_bool(0.5)), PIB(b, rand_bool(0.5)));
		}
		
		vector<char> solution;
		bool ret = solve2SAT(n, clauses, solution);
		
		// Check by bruteforce whether the clauses have a solution.
		bool ret2;
		{
			vector<vector<tuple<bool, int, bool>>> checks(n);
			for(pair<PIB, PIB> clause : clauses) {
				PIB a = clause.first;
				PIB b = clause.second;
				if(a.first < b.first) {
					checks[b.first].emplace_back(b.second, a.first, a.second);
				} else {
					checks[a.first].emplace_back(a.second, b.first, b.second);
				}
			}
			vector<int> choices;
			ret2 = hasSolution(n, checks, choices);
		}
		
		if(ret != ret2) fail();
		
		if(ret) {
			// In positive case, check that the solution really solves all clauses.
			if(solution.size() != n) fail();
			
			for(pair<PIB, PIB> clause : clauses) {
				PIB a = clause.first;
				PIB b = clause.second;
				
				if(solution[a.first] != a.second && solution[b.first] != b.second) fail();
			}
		}
	}
	
	return 0;
}
