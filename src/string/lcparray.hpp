#pragma once
#include "boilerplate.hpp"

/// Construct the LCP array for string S when the suffix array is A.
/// LCP-array[i] = LCP(S[i - 1], S[i]), LCP-array[0] = 0.
vector<int> constructLCPArray(const vector<int>& S, const vector<int>& A) {
	int n = S.size();
	
	vector<int> prev(n + 1);
	prev[A[0]] = -1;
	for(int i = 1; i <= n; ++i) {
		prev[A[i]] = A[i - 1];
	}
	
	int p = 0;
	vector<int> lcp(n + 1);
	for(int i = 0; i < n; ++i) {
		if(prev[i] == -1) {
			lcp[i] = 0;
		} else {
			while(i + p < n && prev[i] + p < n && S[i + p] == S[prev[i] + p]) ++p;
			lcp[i] = p;
			if(p != 0) --p;
		}
	}
	
	vector<int> ret(n + 1);
	ret[0] = 0;
	for(int i = 1; i <= n; ++i) {
		ret[i] = lcp[A[i]];
	}
	
	return ret;
}
