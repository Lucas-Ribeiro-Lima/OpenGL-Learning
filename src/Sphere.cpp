#include "Sphere.h"

Sphere::Sphere(float radius)
	: Model(
		getSphereData(radius),
		getTextureData(Constants::TEX_PLANET_1),
		getProgram(Constants::FRAG_1)
	) {}

Sphere::Sphere(float radius, const char* tex)
	: Model(
		getSphereData(radius),
		getTextureData(tex),
		getProgram(Constants::FRAG_1)
	) {}

Sphere::Sphere(float radius, bool w)
	: Model(
		getSphereData(radius),
		getProgram(Constants::FRAG_LIGHT)
	) {
	wireframe = w;
}
