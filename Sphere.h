//
// Created by Patrick Li on 12/27/24.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "vec3.h"

class Sphere : public Hittable {
private:
	point3 m_center;
	double m_radius;
	std::shared_ptr<Material> m_material;
public:
	Sphere(const point3& center, double radius, std::shared_ptr<Material> mat);
	bool hit(const Ray& r, Interval rayIntv, hit_record& rec) const override;
};



#endif //SPHERE_H
