#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Program.h"
#include "Constants.h"
#include "Camera.h"
#include <vector>
#include <unordered_map>

Camera& getCamera();

Mesh& getCubeData();

Mesh* getSphereData(float radius);

Texture* getTextureData(const char* tex);

Program& getDefaultProgram();

Program* getProgram(const char* frag);