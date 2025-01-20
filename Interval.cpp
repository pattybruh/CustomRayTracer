//
// Created by Patrick Li on 12/30/24.
//
#include "Interval.h"

Interval::Interval() : min(+infinity), max(-infinity){}
Interval::Interval(double pmin, double pmax) : min(pmin), max(pmax){}

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

const Interval Interval::empty = Interval();
const Interval Interval::universe = Interval(-infinity, +infinity);