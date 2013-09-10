#pragma once

#include "boilerplate.hpp"

// WARNING: be careful with overflows and accuracy. Check what the code does.

/// Return true iff points a, b, c are CCW oriented.
bool ccw(V a, V b, V c) {
	return ((c - a) * conj(b - a)).imag() > 0;
}

/// Return true iff points a, b, c are collinear.
/// NOTE: doesn't make much sense with non-integer COORD_TYPE.
bool collinear(V a, V b, V c) {
	return ((c - a) * conj(b - a)).imag() == 0;
}

/// Check whethersegments [a, b] and [c, d] intersect.
/// The segments must not be collinear. Doesn't handle edge cases (endpoint of
/// a segment on the other segment) consistently.
bool intersects(V a, V b, V c, V d) {
	return ccw(a, d, b) != ccw(a, c, b) && ccw(c, a, d) != ccw(c, b, d);
}

/// Interpolate between points a and b with parameter t.
V interpolate(VC t, V a, V b) {
	return a + t * (b - a);
}

/// Return interpolation parameter between a and b of projection of v to the
/// line defined by a and b.
/// NOTE: no rounding behavior specified for integers.
VC projectionParam(V v, V a, V b) {
	return ((v - a) / (b - a)).real();
}
