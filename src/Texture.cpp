//
// Created by Patrick Li on 1/26/25.
//

#include "Texture.h"

SolidColorTexture::SolidColorTexture(const color& c) : m_color(c) {
}
SolidColorTexture::SolidColorTexture(double r, double g, double b) : SolidColorTexture(color(r,g,b)) {
}
color SolidColorTexture::value(double u, double v, const point3& p) const {
	return m_color;
}


CheckerTexture::CheckerTexture(double scale, std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd) :
m_scale(1.0/scale), m_even(even), m_odd(odd) {
}
CheckerTexture::CheckerTexture(double scale, const color& c1, const color& c2) :
CheckerTexture(scale, std::make_shared<SolidColorTexture>(c1), std::make_shared<SolidColorTexture>(c2)){
}
color CheckerTexture::value(double u, double v, const point3& p) const {
	int xInt = static_cast<int>(std::floor(m_scale*p.x()));
	int yInt = static_cast<int>(std::floor(m_scale*p.y()));
	int zInt = static_cast<int>(std::floor(m_scale*p.z()));
	if((xInt+yInt+zInt)%2 == 0) {
		return m_even->value(u,v,p);
	}
	else {
		return m_odd->value(u,v,p);
	}
}
