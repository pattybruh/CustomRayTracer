//
// Created by Patrick Li on 12/27/24.
//

#include "Sphere.h"

Sphere::Sphere(const point3& center, double radius, std::shared_ptr<Material> mat) : m_center(center),
m_radius(fmax(0,radius)), m_material(mat)
{}

bool Sphere::hit(const Ray& r, Interval rayIntv, hit_record& hr) const {
	vec3 oc = m_center - r.origin();
	double a = r.direction().length_squared();
	double b = dot(oc, r.direction());
	double c = oc.length_squared() - m_radius * m_radius;
	double discriminant = b*b - a*c;
	if(discriminant < 0) {
		return false;
	}
	double sqrtd = sqrt(discriminant);//-sqrt(discriminant) to get closest value
	double root = (b - sqrtd) / a;
	if(!rayIntv.surrounds(root)) {
		root = (b + sqrtd) / a;
		if(!rayIntv.surrounds(root)) {
			return false;
		}
	}
	hr.t = root;
	hr.p = r.at(root);
	vec3 outward_normal = (hr.p - m_center) / m_radius;
	hr.set_face_normal(r, outward_normal);
	hr.mat = m_material;

	return true;
}