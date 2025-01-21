//
// Created by Patrick Li on 12/26/24.
//
#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray{
public:
	Ray(){}
	Ray(const vec3& origin, const vec3& direction, double time) : m_origin(origin), m_direction(direction), m_time(time){}
	Ray(const vec3& origin, const vec3& direction) : Ray(origin, direction, 0){}
	const point3& origin() const { return m_origin; }
	const vec3& direction() const { return m_direction; }

	point3 at(double t) const {
		return m_origin + t * m_direction;
	}

	double time() const {
		return m_time;
	}

private:
	point3 m_origin;
	vec3 m_direction;
	double m_time;
};


#endif //RAY_H
