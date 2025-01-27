//
// Created by Patrick Li on 12/30/24.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "HittableList.h"
#include "color.h"
#include "utility.h"

class Camera {
private:
	point3 m_center, m_origPixel;
	vec3 m_deltaU, m_deltaV;
	int m_imgH;
	//double m_pixel_sample_scale;
	double m_aspectRatio;
	int m_imgW;
	int m_samplesPerPixel;
	vec3 m_u,m_v,m_w;
	vec3 m_dofU, m_dofV;

	void init();
	color ray_color(const Ray& r, const Hittable& obj, int depth) const;
	Ray get_ray(int col, int row) const;
	point3 dof_sample() const;
public:
	int maxBounce = 10;
	double vFOV = 90;
	point3 eye = point3(0,1,0);
	point3 lookAt = point3(0,0,-3);
	vec3 up = vec3(0, 1, 0);
	double focusDist = 10.0;
	double focusAngle = 0;
	color bgColor;


	Camera(int imgW, double aspectRatio, int samplesPerPixel);
	void render(const Hittable& world);
};



#endif //CAMERA_H
