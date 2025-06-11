#pragma once
#include "Geometry.h"
#include "Texture.h"
#include "Program.h"
#include "Constants.h"
#include "Camera.h"
#include <vector>

Camera& getCamera();

Geometry& getCubeGeometry();

Geometry& getSphereGeometry(float radius);

Texture& getEarthTexture(const char* tex);

Program& getDefaultProgram();

Program& getProgram(const char* frag);