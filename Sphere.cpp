#include "Sphere.h"

Sphere::Sphere(float radius)
	: Object(
		&getSphereGeometry(radius),
		&getEarthTexture(Constants::TEX_PLANET_1),
		&getProgram(Constants::FRAG_1)
	) {}

Sphere::Sphere(float radius, bool w)
	: Object(
		&getSphereGeometry(radius),
		&getProgram(Constants::FRAG_2)
	) {
	wireframe = w;
}