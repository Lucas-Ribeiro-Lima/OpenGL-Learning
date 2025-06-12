#include "Sphere.h"

Sphere::Sphere(float radius)
	: Object(
		getSphereGeometry(radius),
		getTexture(Constants::TEX_PLANET_1),
		getProgram(Constants::FRAG_1)
	) {}

Sphere::Sphere(float radius, const char* tex)
	: Object(
		getSphereGeometry(radius),
		getTexture(tex),
		getProgram(Constants::FRAG_1)
	) {}

Sphere::Sphere(float radius, bool w)
	: Object(
		getSphereGeometry(radius),
		getProgram(Constants::FRAG_2)
	) {
	wireframe = w;
}
