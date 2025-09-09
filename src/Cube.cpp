#include "Cube.h"

Cube::Cube()
	: Model(
		&getCubeData(),
		getTextureData(Constants::TEX_EARTH_1),
		&getDefaultProgram()
	){}

