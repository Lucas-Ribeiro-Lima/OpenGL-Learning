#include "Cube.h"

Cube::Cube()
	: Object(
		&getCubeGeometry(),
		getTexture(Constants::TEX_EARTH_1),
		&getDefaultProgram()
	){}

