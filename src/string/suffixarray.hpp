#pragma once
#include "boilerplate.hpp"

namespace suffixarray_ {
struct Elem {
	int start;
	int parts[2];
};
}

/// Return the start indices of the suffices of string S sorted in
/// lexicographical order. Characters past the end come before other characters
/// in the order. The empty suffix is included.
vector<int> constructSuffixArray(const vector<int>& S) {
	using suffixarray_::Elem;
	
	int n = S.size();
	vector<pair<int, int> > C(n + 1);
	vector<int> tmp(n + 1);
	vector<Elem> T(n + 1);
	vector<Elem> T2(n + 1);
	
	for(int i = 0; i <= n; ++i) {
		C[i].first = (i == n) ? INT_MIN : S[i];
		C[i].second = -i;
	}
	sort(C.begin(), C.end());
	
	for(int i = 0; i <= n; ++i) {
		int start = -C[i].second;
		T[i].start = start;
		if(start == n) {
			T[i].parts[0] = 0;
		} else {
			T[i].parts[0] = 1;
			T[i].parts[1] = S[start];
		}
	}
	
	int t = 1;
	while(t <= n) {
		for(int i = 0; i <= n; ++i) {
			if(i != 0 &&
				T[i].parts[0] == T[i - 1].parts[0] &&
				T[i].parts[1] == T[i - 1].parts[1]
			) {
				tmp[T[i].start] = tmp[T[i - 1].start];
			} else {
				tmp[T[i].start] = i;
			}
		}
		
		for(int i = 0; i <= n; ++i) {
			T[i].start = i;
			T[i].parts[0] = (i + t > n) ? 0 : tmp[i + t];
			T[i].parts[1] = tmp[i];
		}
		
		for(int s = 0; s < 2; ++s) {
			fill(tmp.begin(), tmp.end(), 0);
			for(int i = 0; i <= n; ++i) {
				++tmp[T[i].parts[s]];
			}
			
			int x = 0;
			for(int i = 0; i <= n; ++i) {
				int y = tmp[i];
				tmp[i] = x;
				x += y;
			}
			
			for(int i = 0; i <= n; ++i) {
				T2[tmp[T[i].parts[s]]++] = T[i];
			}
			
			swap(T, T2);
		}
		
		t *= 2;
	}
	
	for(int i = 0; i <= n; ++i) {
		tmp[i] = T[i].start;
	}
	
	return tmp;
}
