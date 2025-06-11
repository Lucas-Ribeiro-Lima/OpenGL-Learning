#include "Cube.h"

Cube::Cube()
	: Object(
		&getCubeGeometry(),
		&getEarthTexture(Constants::TEX_EARTH_1),
		&getDefaultProgram()
	){}

