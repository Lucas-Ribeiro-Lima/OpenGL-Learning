#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Utils.h"

enum Directions {
	front = 1,
	right = 1,
	left = -1,
	back = -1,
	
};

class Camera
{
private:
	glm::vec3 pos{ 0.0f, 0.0f, 30.0f };
	glm::vec3 front{ 0.0f, 0.0f, -1.0f };
	glm::vec3 up{ 0.0f, 1.0f, 0.0f };

	glm::mat4 view = glm::lookAt(pos, pos + front, up);
	glm::mat4 perspective = glm::perspective(45.0f, 1280.0f / 920.0f, 0.1f, 1000.f);

	float cameraSpeed = 50.0f;

	float fov = 45.0f;
	float yaw = -90.0f;
	float pitch = 0.0f;

public:
	Camera();
	glm::mat4 getView();
	glm::mat4 getPerspective();
	void updateView();
	void updatePerspective();
	void update(float yaw, float pitch, float fov);
	void setFrontBack(float value, Directions dir);
	void setLeftRight(float value, Directions dir);
};

