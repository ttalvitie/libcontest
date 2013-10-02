#pragma once

// Boilerplate required by other modules.

using namespace std;

#include <algorithm> // abs, binary_search, copy, equal_range, lower_bound, max,
                     // merge, min, upper_bound, sort, swap, ...
#include <bitset>    // bitset
#include <complex>   // complex
#include <climits>   // INT_MAX, INT_MIN, ...
#include <cstdlib>   // exit
#include <deque>     // deque
#include <iostream>  // cin, cout, cerr
#include <list>      // list
#include <map>       // map
#include <queue>     // queue, priority_queue
#include <set>       // set
#include <stack>     // stack
#include <string>    // string
#include <sstream>   // stringstream
#include <vector>    // vector

// Complex number/vector type for geometry.
#ifdef COORD_TYPE
	typedef COORD_TYPE VC;
#else
	typedef double VC;
#endif
typedef complex<VC> V;

// Integer type used for integers apart from indices.
#ifdef INT_TYPE
	typedef INT_TYPE Z;
#else
	typedef int Z;
#endif

const double PI = 4 * atan(1);

void fail(string msg) {
	cerr << "FAIL: " << msg << "\n";
	abort();
}
void fail() {
	cerr << "FAIL\n";
	abort();
}
