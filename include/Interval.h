//
// Created by Patrick Li on 12/30/24.
//

#ifndef INTERVAL_H
#define INTERVAL_H
#include "utility.h"

class Interval{
	public:
	double min, max;
	static const Interval Intv_Empty, Intv_Universe;
	Interval();
	Interval(double pmin, double pmax);
	Interval(const Interval&a, const Interval& b);

	double size() const;

	bool contains(double x) const;

	bool surrounds(double x) const;

	double clamp(double x) const;

	Interval expand(double x) const;
};

const extern Interval Intv_Empty;
const extern Interval Intv_Universe;
#endif //INTERVAL_H
