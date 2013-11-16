#pragma once

#include "boilerplate.hpp"
#include <boost/random.hpp>

namespace testutil {
	mt19937 rng;
}

template <typename T>
T rand_int(T a, T b) {
	if(a > b) swap(a, b);
	uniform_int_distribution<T> dist(a, b);
	return dist(testutil::rng);
}

float rand_real(float a, float b) {
	if(a > b) swap(a, b);
	uniform_real_distribution<float> dist(a, b);
	return dist(testutil::rng);
}
double rand_real(double a, double b) {
	if(a > b) swap(a, b);
	uniform_real_distribution<double> dist(a, b);
	return dist(testutil::rng);
}

bool rand_bool(double true_prob) {
	return rand_real(0.0, 1.0) < true_prob;
}
