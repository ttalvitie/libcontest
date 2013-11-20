#include "string/z.hpp"

vector<int> zAlgorithmCmpImpl(const string& S) {
	int n = S.size();
	vector<int> ret(n);
	
	for(int i = 0; i < n; ++i) {
		int x = 0;
		while(i + x < n && S[x] == S[i + x]) ++x;
		ret[i] = x;
	}
	
	return ret;
}

int main() {
	mt19937 rng;
	
	uniform_int_distribution<int> length_dist(0, 100);
	uniform_int_distribution<int> alph_dist(1, 6);
	
	for(int t = 0; t < 400000; ++t) {
		int n = length_dist(rng);
		int k = alph_dist(rng);
		uniform_int_distribution<int> char_dist('A', 'A' + k - 1);
		
		vector<int> S;
		for(int i = 0; i < n; ++i) {
			S.push_back(char_dist(rng));
		}
		
		vector<int> a = zAlgorithm(S);
		vector<int> b = zAlgorithm(S);
		
		if(a.size() != b.size() || !equal(a.begin(), a.end(), b.begin())) fail();
	}
	
	return 0;
}
