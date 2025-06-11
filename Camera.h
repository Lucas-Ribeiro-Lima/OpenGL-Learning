#pragma once
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

enum Directions {
	front = 1,
	right = 1,
	left = -1,
	back = -1,
	
};

class Camera
{
private:
	glm::vec3 pos{ 0.0f, 0.0f, 3.0f };
	glm::vec3 front{ 0.0f, 0.0f, -1.0f };
	glm::vec3 up{ 0.0f, 1.0f, 0.0f };

	glm::mat4 view = glm::lookAt(pos, pos + front, up);

	float yaw = -90.0f;
	float pitch = 0.0f;

public:
	Camera();
	glm::mat4 getView();
	void update();
	void updateFront(float yaw, float pitch);
	void setFrontBack(float value, Directions dir);
	void setLeftRight(float value, Directions dir);
};

