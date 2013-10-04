#include "string/suffixarray.hpp"

#include <boost/random.hpp>

using namespace boost::random;

vector<int> constructSuffixArrayCmpImpl(const vector<Z>& S) {
	int n = S.size();
	string Ss;
	for(int i = 0; i < n; ++i) Ss.push_back(S[i]);
	vector<string> suf;
	for(int i = 0; i <= n; ++i) {
		suf.push_back(Ss.substr(i));
	}
	sort(suf.begin(), suf.end());
	
	vector<int> ret;
	for(int i = 0; i <= n; ++i) {
		ret.push_back(n - suf[i].size());
	}
	
	return ret;
}

int main() {
	mt19937 rng;
	
	uniform_int_distribution<int> length_dist(0, 50);
	uniform_int_distribution<int> alph_dist(1, 6);
	uniform_int_distribution<int> bool_dist(0, 1);
	
	for(int t = 0; t < 100000; ++t) {
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
		
		vector<int> a = constructSuffixArray(S);
		vector<int> b = constructSuffixArrayCmpImpl(S);

		if(a.size() != b.size()) fail();
		if(!equal(a.begin(), a.end(), b.begin())) fail();
	}
	
	return 0;
}
