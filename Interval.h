//
// Created by Patrick Li on 12/30/24.
//

#ifndef INTERVAL_H
#define INTERVAL_H
#include "utility.h"

class Interval{
	public:
	double min, max;
	static const Interval empty, universe;
	Interval();
	Interval(double pmin, double pmax);

	double size() const;

	bool contains(double x) const;

	bool surrounds(double x) const;

	double clamp(double x) const;
};

const extern Interval empty;
const extern Interval universe;
#endif //INTERVAL_H
