//
// Created by Patrick Li on 12/26/24.
//

#ifndef VEC3_H
#define VEC3_H

#include <iostream>

#include "utility.h"

class vec3{
public:
	double e[3];

	vec3() : e{0, 0, 0} {
	}

	vec3(double e0, double e1, double e2) : e{e0, e1, e2} {
	}

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator[](int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; }

	vec3& operator+=(const vec3& v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	vec3& operator*=(double t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	vec3& operator/=(double t) {
		return *this *= 1 / t;
	}

	double length() const {
		return std::sqrt(length_squared());
	}

	double length_squared() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	bool nearly_zero() const {
		auto s = 1e-8;
		return (std::fabs(e[0]) < s) &&(std::fabs(e[1]) < s) &&(std::fabs(e[2]) < s);
	}

	static vec3 random() {
		return vec3(random_double(), random_double(), random_double());
	}
	static vec3 random(double min, double max) {
		return vec3(random_double(min, max),random_double(min, max),random_double(min, max));
	}

};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;

// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
	return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
	return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
	            u.e[2] * v.e[0] - u.e[0] * v.e[2],
	            u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3& v) {
	return v / v.length();
}

inline void unit_vector(vec3& v) {
	v *= (1.0/v.length());
}
inline vec3 random_unit_vector() {
	while(1) {
		vec3 test = vec3::random(-1.0, 1.0);
		double l = test.length_squared();
		if(1e-160 < l && l <= 1) {
			unit_vector(test);
			return test;
		}
	}
}
inline vec3 random_on_hemi(vec3& norm) {
	vec3 test = random_unit_vector();
	if(dot(test, norm) > 0.0) {
		return test;
	}
	return -test;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2 * dot(v, n) * n;
}

inline vec3 refract(const vec3& v, const vec3& n, double etas) {
	double cosT = std::fmin(dot(-v, n), 1.0);
	vec3 outPerp = etas*(v+cosT*n);
	vec3 outParallel = -std::sqrt(std::fabs(1.0-outPerp.length_squared()))*n;
	return outPerp + outParallel;
}

inline vec3 random_in_unit_disk() {
	while(1) {
		vec3 test(random_double(-1,1), random_double(-1,1), 0.0);
		if(test.length_squared() < 1) {
			return test;
		}
	}
}

#endif //VEC3_H
