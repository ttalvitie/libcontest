#pragma once
#include "boilerplate.hpp"

/// In the Nim game, there are heaps of coins with h[i] coins in i:th heap.
/// The players remove any positive number of coins from one heap in turns.
/// The player who removes the last coin wins. The function returns a pair
/// consisting of the index of the heap and the number of coins to remove
/// to win, or pair (-1, -1) if there is no winning strategy.
pair<int, Z> solveNim(const vector<Z>& h) {
	Z nim = 0;
	for(int i = 0; i < h.size(); ++i) {
		nim ^= h[i];
	}
	
	if(nim == 0) return pair<int, Z>(-1, -1);
	
	for(int i = 0; i < h.size(); ++i) {
		if((nim ^ h[i]) < h[i]) return pair<int, Z>(i, h[i] - (nim ^ h[i]));
	}
	
	fail();
	return pair<int, Z>(-2, -2);
}
