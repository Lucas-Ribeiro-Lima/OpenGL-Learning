#include "Camera.h"

Camera::Camera() {};

void Camera::setFrontBack(float value, Directions dir) {
	if (dir == 1) {
		pos += front * value;
	}
	else {
		pos -= front * value;
	}
	update();
}

void Camera::setLeftRight(float value, Directions dir) {
	if (dir == 1) {
		pos += glm::normalize(glm::cross(front, up)) * value;
;	}
	else {
		pos -= glm::normalize(glm::cross(front, up)) * value;
	}
	update();
}

glm::mat4 Camera::getView() {
	return view;
}

void Camera::update() {
	view = glm::lookAt(pos, pos + front, up);
}

void Camera::updateFront(float y, float p) {
	if (yaw == y && pitch == p) return;
	glm::vec3 direction;
	direction.x = cos(glm::radians(y)) * cos(glm::radians(p));
	direction.y = sin(glm::radians(p));
	direction.z = sin(glm::radians(y)) * cos(glm::radians(p));
	front = glm::normalize(direction);
}