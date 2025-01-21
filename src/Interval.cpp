//
// Created by Patrick Li on 12/30/24.
//
#include "Interval.h"

Interval::Interval() : min(+infinity), max(-infinity){}
Interval::Interval(double pmin, double pmax) : min(pmin), max(pmax){}
Interval::Interval(const Interval&a, const Interval& b) {
	min = std::min(a.min, b.min);
	max = std::max(a.max, b.max);
}

double Interval::size() const {
	return max - min;
}

bool Interval::contains(double x) const {
	return min <= x && x <= max;
}

bool Interval::surrounds(double x) const {
	return min < x && x < max;
}

double Interval::clamp(double x) const {
	if(x<min) return min;
	if(x > max) return max;
	return x;
}

Interval Interval::expand(double x) const {
	double padding = x/2.0;
	return Interval(min-padding, max+padding);
}

const Interval Interval::Intv_Empty = Interval();
const Interval Interval::Intv_Universe = Interval(-infinity, +infinity);