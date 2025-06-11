#include "Instances.h"

Instances::Instances(Object& o, Positions& p): obj(o), Pos(p) {};

void Instances::setInstances(std::vector<glm::vec3> pos) {
	Pos = pos;
}

void Instances::drawInstances() {
	for (int i = 0; i < Pos.size(); i++) {
		float time = glfwGetTime() * 50.0f;
		float fixedRotate = i * 20.0f;

		float rotation = i % 3 == 0 ? time : fixedRotate;

		obj
			.setTranslate(Pos[i])
			.setRotate(rotation, glm::vec3(0.0f, 1.0f, 0.0f))
			.draw();
	}
}