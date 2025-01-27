//
// Created by Patrick Li on 1/26/25.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include <color.h>
#include <vec3.h>

class Texture{
public:
	virtual ~Texture() = default;
	virtual color value(double u, double v, const point3& p) const = 0;
};

class SolidColorTexture : public Texture{
private:
	color m_color;
	public:
	SolidColorTexture(const color& c);
	SolidColorTexture(double r, double g, double b);
	color value(double u, double v, const point3& p) const override;
};

class CheckerTexture : public Texture{
	private:
	double m_scale;
	std::shared_ptr<Texture> m_even;
	std::shared_ptr<Texture> m_odd;
public:
	CheckerTexture(double scale, std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd);
	CheckerTexture(double scale, const color& c1, const color& c2);
	color value(double u, double v, const point3& p) const override;
};

#endif //TEXTURE_H
