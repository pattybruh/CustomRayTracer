//
// Created by Patrick Li on 1/22/25.
//

#include "Quad.h"

Quad::Quad(const point3& q, const vec3& u, const vec3& v, const std::shared_ptr<Material>& mat)
	: m_q(q), m_u(u), m_v(v), m_mat(mat) {
	const vec3 norm = cross(m_u, m_v);
	m_normal = unit_vector(norm);
	m_d = dot(m_normal, m_q);
	m_w = norm / dot(norm,norm);
	setBb();
}

void Quad::setBb() {
	Bbox diag1 = Bbox(m_q, m_q+m_u+m_v);
	Bbox diag2 = Bbox(m_q+m_u, m_q+m_v);
	m_bb = Bbox(diag1, diag2);
}

Bbox Quad::boundingBox() const {
	return m_bb;
}

bool Quad::hit(const Ray& r, Interval rayIntv, hit_record& hr) const {
	double denom = dot(m_normal, r.direction());
	if(std::fabs(denom) < 1e-8) return false;//parallel

	double t = (m_d - dot(m_normal, r.direction())) / denom;
	if(!rayIntv.contains(t)) return false;//t outisde of ray interval

	point3 intersect = r.at(t);
	vec3 planeHit = intersect - m_q;
	double alpha = dot(m_w, cross(planeHit, m_v));
	double beta = dot(m_w, cross(m_u, planeHit));

	Interval unit = Interval(0,1);
	if(!unit.contains(alpha) || !unit.contains(beta)) return false;

	hr.t = t;
	hr.p = r.at(t);
	hr.mat = m_mat;
	hr.set_face_normal(r,m_normal);
	return true;
}

bool Quad::isOn(double a, double b, hit_record& rec) const {
	Interval unit = Interval(0,1);
	return (unit.contains(a) && unit.contains(b));
}

