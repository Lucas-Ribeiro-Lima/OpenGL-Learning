#pragma once
#include "Geometry.h"
#include "Texture.h"
#include "Program.h"
#include "Constants.h"
#include "Camera.h"
#include <vector>
#include <unordered_map>

Camera& getCamera();

Geometry& getCubeGeometry();

Geometry* getSphereGeometry(float radius);

Texture* getTexture(const char* tex);

Program& getDefaultProgram();

Program* getProgram(const char* frag);