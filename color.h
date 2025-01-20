//
// Created by Patrick Li on 12/26/24.
//

#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
//#include <iostream>

using color = vec3;
inline double lin_to_gamma(double linC) {
	if(linC > 0.0) {
		return std::sqrt(linC);
	}
	return 0;
}
inline void write_color(std::ostream& out, const color& pixel_color) {
	double r = pixel_color.x();
	double g = pixel_color.y();
	double b = pixel_color.z();

	r=lin_to_gamma(r);
	g=lin_to_gamma(g);
	b=lin_to_gamma(b);

	// Translate the [0,1] component values to the byte range [0,255].
	static const Interval intensity(0.00, 0.999);
	int rbyte = int(256 * intensity.clamp(r));
	int gbyte = int(256 * intensity.clamp(g));
	int bbyte = int(256 * intensity.clamp(b));

	// Write out the pixel color components.
	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif //COLOR_H
