#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
#include "Program.h"
#include <memory>

Camera &getCamera();

Mesh &getCubeData();

std::shared_ptr<Mesh> getSphereData(float radius);

std::shared_ptr<Texture> getTextureData(const char *tex);

std::shared_ptr<Program> getProgram(const char* vertex, const char *frag);
