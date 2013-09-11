#include "numtheory/basic.hpp"

map<int, int> factor(int x) {
	map<int, int> ret;
	
	for(int i = 2; i * i <= x; ++i) {
		while(x % i == 0) {
			++ret[i];
			x /= i;
		}
	}
	if(x > 1) ++ret[x];
	
	return ret;
}

int main() {
	vector<map<int, int> > f;
	f.push_back(map<int, int>());
	for(int i = 1; i < 100; ++i) {
		f.push_back(factor(i));
	}
	
	for(int a = -99; a < 100; ++a) {
		for(int b = -99; b < 100; ++b) {
			map<int, int> gf;
			typedef map<int, int>::iterator I;
			for(I i = f[abs(a)].begin(); i != f[abs(a)].end(); ++i) {
				gf[i->first] = min(i->second, f[abs(b)][i->first]);
			}
			for(I i = f[abs(b)].begin(); i != f[abs(b)].end(); ++i) {
				gf[i->first] = min(i->second, f[abs(a)][i->first]);
			}
			
			int g = 1;
			for(I i = gf.begin(); i != gf.end(); ++i) {
				for(int j = 0; j < i->second; ++j) {
					g *= i->first;
				}
			}
			
			if(a == 0 && b == 0) {
				if(gcd(a, b) != 0) fail();
			} else if(a == 0) {
				if(gcd(a, b) != abs(b)) fail();
			} else if(b == 0) {
				if(gcd(a, b) != abs(a)) fail();
			} else {
				if(gcd(a, b) != g) fail();
			}
		}
	}
	
	return 0;
}
