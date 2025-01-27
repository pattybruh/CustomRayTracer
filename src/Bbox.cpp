//
// Created by Patrick Li on 1/21/25.
//

#include "Bbox.h"

Bbox::Bbox(){}
Bbox::Bbox(const Interval& x, const Interval& y, const Interval& z) : x(x), y(y), z(z) {
	minPadding();
}
Bbox::Bbox(const point3& a, const point3& b) {
	x = (a[0]<b[0]) ? Interval(a[0], b[0]) : Interval(b[0], a[0]);
	y = (a[1]<b[1]) ? Interval(a[1], b[1]) : Interval(b[1], a[1]);
	z = (a[2]<b[2]) ? Interval(a[2], b[2]) : Interval(b[2], a[2]);

	minPadding();
}
Bbox::Bbox(const Bbox&a, const Bbox&b) {
	x = Interval(a.x, b.x);
	y = Interval(a.y, b.y);
	z = Interval(a.z, b.z);
}

void Bbox::minPadding() {
	if(x.size() < 0.0001) x=x.expand(0.0001);
	if(y.size() < 0.0001) y=y.expand(0.0001);
	if(z.size() < 0.0001) z=z.expand(0.0001);
}


const Interval& Bbox::axisInterval(int n) const {
	if(n==1) return y;
	if(n==2) return z;
	return x;
}
bool Bbox::hit(const Ray& r, Interval res) const {
	const point3& rayOrig = r.origin();
	const vec3& rayDir = r.direction();
	for(int i=0; i<3; i++) {
		const Interval& axis = axisInterval(i);
		const double invD = 1.0/rayDir[i];
		double t0 = (axis.min-rayOrig[i])*invD;
		double t1 = (axis.max-rayOrig[i])*invD;
		if(t0 < t1) {
			res.min = std::max(t0, res.min);
			res.max = std::min(t1, res.max);
		}
		else {
			res.min = std::max(t1, res.min);
			res.max = std::min(t0, res.max);
		}
		if(res.max <= res.min) return false;
	}
	return true;
}

int Bbox::longestAxis() const {
	if(x.size() > y.size()) {
		return x.size() > z.size() ? 0 : 2;
	}
	return y.size() > z.size() ? 1 : 2;
}


const Bbox Bbox::Bbox_Empty = Bbox(Interval::Intv_Empty, Interval::Intv_Empty, Interval::Intv_Empty);
const Bbox Bbox::Bbox_Universe = Bbox(Interval::Intv_Universe, Interval::Intv_Universe, Interval::Intv_Universe);