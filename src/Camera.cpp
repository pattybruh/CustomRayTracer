//
// Created by Patrick Li on 12/30/24.
//

#include "Camera.h"

#include "Material.h"

void Camera::init() {
	m_center = eye;
	m_imgH = (int)(m_imgW/m_aspectRatio);
	//m_pixel_sample_scale = 1.0/samplesPerPixel;

	//double focalLength = (m_center - lookAt).length();
	double theta = degrees_to_radians(vFOV);
	double viewport_height = 2.0 * std::tan(theta/2.0)*focusDist;
	double viewport_width = viewport_height * ((double)m_imgW/(double)m_imgH);

	m_w = unit_vector(m_center-lookAt);
	m_u = unit_vector(cross(up, m_w));
	m_v = unit_vector(cross(m_w, m_u));

	vec3 viewportU = viewport_width * m_u;
	vec3 viewportV = viewport_height * -m_v;
	m_deltaU = viewportU/m_imgW;
	m_deltaV = viewportV/m_imgH;

	point3 viewportOrigin = m_center - (focusDist*m_w) - viewportU/2 - viewportV/2;
	m_origPixel = viewportOrigin + 0.5*(m_deltaU+m_deltaV);

	double focusRadius = focusDist*std::tan(degrees_to_radians(focusAngle/2.0));
	m_dofU = m_u*focusRadius;
	m_dofV = m_v*focusRadius;
}

color Camera::ray_color(const Ray& r, const Hittable& obj, int bounce) const {
	if(bounce <= 0) {
		return color(0.0, 0.0, 0.0);
	}
	hit_record rec;

	if(!obj.hit(r, Interval(0.001, infinity), rec)) {//0.001 fix shadow acne by ignoring close hits
		//return 0.5 * (rec.normal+color(1,1,1));
		return bgColor;
	}
	Ray scatter;
	color atten;
	color emitColor = rec.mat->emit(rec.u, rec.v, rec.p);
	if(!rec.mat->scatter(r, rec, atten, scatter)) {
		return emitColor;
	}
	return emitColor + (atten*ray_color(scatter, obj, bounce-1));
	return color(0.0, 0.0, 0.0);
	//bg color
	vec3 unitDir = unit_vector(r.direction());
	double a = 0.5 * (unitDir.y()+1.0);
	return (1.0-a) * color(1.0,1.0,1.0) + a*color(0.4,0.46,1.0);
}

Camera::Camera(int imgW, double aspectRatio, int samplesPerPixel) : m_imgW(imgW), m_aspectRatio(aspectRatio),
m_samplesPerPixel(samplesPerPixel) {}

void Camera::render(const Hittable& world) {
	init();
	std::cout << "P3\n" << m_imgW << " " << m_imgH << "\n255\n";
	for(int row=0; row<m_imgH; row++) {
		std::clog << "\rLines remaining: " << m_imgH-row << ' ' << std::flush;
		for(int col=0; col<m_imgW; col++) {
			/*
			point3 pixelCenter = m_origPixel + col*m_deltaU + row*m_deltaV;
			vec3 rayDir = pixelCenter - m_center;
			Ray r(m_center, rayDir);
			color pixelColor = ray_color(r, world);
			write_color(std::cout, pixelColor);
			*/
			color pixelColor(0, 0, 0);
			for(int sample=0; sample<m_samplesPerPixel; sample++) {
				Ray r = get_ray(col, row);
				pixelColor += ray_color(r, world, maxBounce);
			}
			write_color(std::cout, pixelColor/m_samplesPerPixel);
		}
	}
	std::clog << "Done!\n";
}

Ray Camera::get_ray(int col, int row) const {
	vec3 offset(random_double()-0.5, random_double()-0.5, 0);
	point3 pixelSampleCenter = m_origPixel + (col+offset.x())*m_deltaU + (row+offset.y())*m_deltaV;

	point3 rayOrigin = (focusAngle<=0) ? m_center : dof_sample();
	return Ray(rayOrigin, pixelSampleCenter-rayOrigin, random_double());
}

point3 Camera::dof_sample() const {
	vec3 r = random_in_unit_disk();
	return m_center + (r[0]*m_dofU) + (r[1]*m_dofV);
}