//
// Created by Patrick Li on 1/21/25.
//

#ifndef BBOX_H
#define BBOX_H
#include "vec3.h"
#include "Ray.h"
#include "Interval.h"


class Bbox {
public:
	Interval x,y,z;
	static const Bbox Bbox_Empty, Bbox_Universe;

	Bbox();
	Bbox(const Interval& x, const Interval& y, const Interval& z);
	Bbox(const point3& a, const point3& b);
	Bbox(const Bbox&a, const Bbox&b);

	const Interval& axisInterval(int n) const;
	bool hit(const Ray& r, Interval ray_t) const;
	int longestAxis() const;
};

const extern Bbox Bbox_Empty;
const extern Bbox Bbox_Universe;


#endif //BBOX_H
