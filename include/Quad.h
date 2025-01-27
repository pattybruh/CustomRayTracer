//
// Created by Patrick Li on 1/22/25.
//

#ifndef QUAD_H
#define QUAD_H
#include "Hittable.h"

class Quad : public Hittable{
	point3 m_q;
	vec3 m_u, m_v, m_normal, m_w;
	std::shared_ptr<Material> m_mat;
	Bbox m_bb;
	double m_d;
public:
	Quad(const point3& q, const vec3& u, const vec3& v, const std::shared_ptr<Material>& mat);
	virtual void setBb();
	virtual bool isOn(double a, double b, hit_record& rec) const;
	Bbox boundingBox() const override;
	bool hit(const Ray& r, Interval rayIntv, hit_record& hr) const override;
};
#endif //QUAD_H
