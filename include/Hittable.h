//
// Created by Patrick Li on 12/27/24.
//

#ifndef HITTABLE_H
#define HITTABLE_H

//#include "utility.h"
#include "Ray.h"
#include "Interval.h"
#include "Bbox.h"

class Material;

class hit_record{
public:
	point3 p;
	vec3 normal;
	std::shared_ptr<Material> mat;
	double t;
	bool front_face;

	void set_face_normal(const Ray& r, const vec3& outward_normal) {
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};


class Hittable{
public:
	virtual ~Hittable() = default;
	virtual bool hit(const Ray& r, Interval rayIntv, hit_record& hr) const = 0;
	virtual Bbox boundingBox() const = 0;
};
#endif //HITTABLE_H
