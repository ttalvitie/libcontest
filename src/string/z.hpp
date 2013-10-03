#pragma once
#include "boilerplate.hpp"

/// Return vector containing for each position i the length of the longest
/// substring that is also a prefix of the string.
vector<int> zAlgorithm(const string& S) {
	int n = S.size();
	if(n == 0) fail();
	vector<int> ret(n);
	ret[0] = n;
	
	int L = 0;
	int R = 0;
	for(int i = 1; i < n; ++i) {
		if(i > R) {
			L = i;
			R = i;
			while(R < n && S[R - L] == S[R]) ++R;
			ret[i] = R - L;
			--R;
		} else if(ret[i - L] < R - i + 1) {
			ret[i] = ret[i - L];
		} else {
			L = i;
			while(R < n && S[R - L] == S[R]) ++R;
			ret[i] = R - L;
			--R;
		}
	}
	
	return ret;
}
