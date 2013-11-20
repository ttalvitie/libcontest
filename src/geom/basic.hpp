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

/// Check whether segments [a, b] and [c, d] intersect.
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

/// Compute the distance of point v from line a..b.
/// NOTE: Only for non-integers!
VC pointLineDistance(V p, V a, V b) {
	return abs(((p - a) / (b - a)).imag()) * abs(b - a);
}

/// Compute the distance of point v from segment a..b.
/// NOTE: Only for non-integers!
VC pointSegmentDistance(V p, V a, V b) {
	V z = (p - a) / (b - a);
	if(z.real() < 0) return abs(p - a);
	if(z.real() > 1) return abs(p - b);
	return abs(z.imag()) * abs(b - a);
}

/// Return interpolation parameter between a and b of the point that is also
/// on line c..d.
/// NOTE: Only for non-integers!
VC intersectionParam(V a, V b, V c, V d) {
	V u = (c - a) / (b - a);
	V v = (d - a) / (b - a);
	return (u.real() * v.imag() - u.imag() * v.real()) / (v.imag() - u.imag());
}
