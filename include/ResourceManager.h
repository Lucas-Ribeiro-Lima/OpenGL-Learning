#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
#include "Program.h"

Camera *getCamera();

Mesh *getCubeData();

Mesh *getSphereData(float radius);

Texture *getTextureData(const char *tex);

Program *getDefaultProgram();

Program *getProgram(const char *frag);
