#include "numtheory/basic.hpp"

bool isPrime(int x) {
	if(x < 2) return false;
	
	for(int i = 2; i < x; ++i) {
		if(x % i == 0) return false;
	}
	
	return true;
}

int main() {
	vector<char> table = genPrimeTable(20000);
	if(table.size() != 20000) fail();
	
	for(int i = 0; i < table.size(); ++i) {
		if((bool)table[i] != isPrime(i)) fail();
	}
	
	return 0;
}
