//
// Created by Patrick Li on 12/27/24.
//

#include "Sphere.h"

//still
Sphere::Sphere(const point3& center, double radius, std::shared_ptr<Material> mat) :
m_center(center, vec3(0,0,0)), m_radius(std::fmax(0,radius)), m_material(mat) {
	vec3 v = vec3(radius, radius, radius);
	m_bb = Bbox(center-v, center+v);//bounding box is size of sphere
}

//movmement
Sphere::Sphere(const point3& center1, const point3& center2, double radius, std::shared_ptr<Material> mat) :
m_center(center1, center2-center1), m_radius(std::fmax(0,radius)), m_material(mat) {
	vec3 v = vec3(radius, radius, radius);
	Bbox b1(m_center.at(0)-v, m_center.at(0)+v);
	Bbox b2(m_center.at(1)-v, m_center.at(1)+v);
	m_bb = Bbox(b1, b2);
}

bool Sphere::hit(const Ray& r, Interval rayIntv, hit_record& hr) const {
	point3 currCenter = m_center.at(r.time());
	vec3 oc = currCenter - r.origin();
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
	vec3 outward_normal = (hr.p - currCenter) / m_radius;
	hr.set_face_normal(r, outward_normal);
	hr.mat = m_material;

	return true;
}

Bbox Sphere::boundingBox() const {
	return m_bb;
}