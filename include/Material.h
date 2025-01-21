//
// Created by Patrick Li on 1/14/25.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "Hittable.h"

class Material{
public:
	virtual ~Material() = default;
	virtual bool scatter(const Ray& r, const hit_record& rec, color& atten, Ray& scatter) const {
		return false;
	}
};

class Lambertian : public Material{
private:
	color m_reflectCoeff;
public:
	Lambertian(const color& c) : m_reflectCoeff(c) {}
	bool scatter(const Ray& r, const hit_record& rec, color& atten, Ray& scatter) const override{
		vec3 scatterDir = rec.normal + random_unit_vector();
		if(scatterDir.nearly_zero()) scatterDir = rec.normal;
		scatter = Ray(rec.p, scatterDir, r.time());
		atten = m_reflectCoeff;
		return true;
	}
};

class Metal : public Material{
private:
	color m_reflectCoeff;
	double m_fuzzCoeff;
public:
	Metal(const color& c, const double fuzz) : m_reflectCoeff(c), m_fuzzCoeff(fuzz < 1 ? fuzz : 1) {}
	bool scatter(const Ray& r, const hit_record& rec, color& atten, Ray& scatter) const override{
		vec3 reflectDir = unit_vector(reflect(r.direction(), rec.normal)) + (m_fuzzCoeff * random_unit_vector());
		scatter = Ray(rec.p, reflectDir, r.time());
		atten = m_reflectCoeff;
		return dot(scatter.direction(), rec.normal) > 0;
	}
};

class Dielectric : public Material{
private:
	double m_refractionCoeff;

	static double reflectance(double cosine, double ridx) {
		double r = (1-ridx) / (1+ridx);
		r =r*r;
		return r + (1-r)*pow((1-cosine),5);
	}
public:
	Dielectric(double refractionIndex) : m_refractionCoeff(refractionIndex) {}
	bool scatter(const Ray& r, const hit_record& rec, color& atten, Ray& scatter) const override {
		atten = color(1.0, 1.0, 1.0);
		double ridx = rec.front_face ? (1.0/m_refractionCoeff) : m_refractionCoeff;
		vec3 unitDir = unit_vector(r.direction());

		double cosT = std::fmin(dot(-unitDir, rec.normal), 1.0);
		double sinT = std::sqrt(1.0-cosT*cosT);

		if(ridx * sinT > 1.0 || reflectance(cosT, ridx) > random_double()) {
			scatter = Ray(rec.p, reflect(unitDir, rec.normal), r.time());
		}
		else {
			scatter = Ray(rec.p, refract(unitDir, rec.normal, ridx), r.time());
		}
		return true;
	}
};

#endif //MATERIAL_H
