#include "string/suffixarray.hpp"
#include "string/lcparray.hpp"

int main() {
	mt19937 rng;
	
	uniform_int_distribution<int> length_dist(0, 50);
	uniform_int_distribution<int> alph_dist(1, 6);
	uniform_int_distribution<int> bool_dist(0, 1);
	
	for(int t = 0; t < 200000; ++t) {
		int n = length_dist(rng);
		int k = alph_dist(rng);
		uniform_int_distribution<int> char_dist('A', 'A' + k - 1);
		if(bool_dist(rng)) {
			char_dist = uniform_int_distribution<int>(INT_MIN, INT_MIN + k - 1);
		}
		
		vector<int> S;
		for(int i = 0; i < n; ++i) {
			S.push_back(char_dist(rng));
		}
		
		vector<int> A = constructSuffixArray(S);
		vector<int> LCP = constructLCPArray(S, A);
		
		if(LCP.size() != n + 1) fail();
		if(LCP[0] != 0) fail();
		for(int i = 1; i <= n; ++i) {
			int cmp = 0;
			while(A[i] + cmp < n && A[i - 1] + cmp < n && S[A[i] + cmp] == S[A[i - 1] + cmp]) ++cmp;
			if(LCP[i] != cmp) fail();
		}
	}
	
	return 0;
}
