#include "Camera.h"

Camera::Camera() {};

void Camera::setFrontBack(float value, Directions dir) {
	if (dir == 1) {
		pos += front * value;
	}
	else {
		pos -= front * value;
	}
	updateView();
}

void Camera::setLeftRight(float value, Directions dir) {
	if (dir == 1) {
		pos += glm::normalize(glm::cross(front, up)) * value;
;	}
	else {
		pos -= glm::normalize(glm::cross(front, up)) * value;
	}
	updateView();
}

glm::mat4 Camera::getView() {
	return view;
}

glm::mat4 Camera::getPerspective() {
	return perspective;
}

void Camera::updateView() {
	view = glm::lookAt(pos, pos + front, up);
}

void Camera::updatePerspective() {
	perspective = glm::perspective(fov, 1280.0f / 960.0f, 0.1f, 100.0f);
}

void Camera::update(float y, float p, float f) {
	if (fov != f) {
		fov = f;
		updatePerspective();
	}
	if (yaw != y || pitch != p) {
		glm::vec3 direction;
		direction.x = cos(glm::radians(y)) * cos(glm::radians(p));
		direction.y = sin(glm::radians(p));
		direction.z = sin(glm::radians(y)) * cos(glm::radians(p));
		front = glm::normalize(direction);
		updateView();
	}
}