#include "Instances.h"

Instances::Instances(Object& obj, Positions& pos): Obj(obj), Pos(pos) {};

void Instances::setInstances(std::vector<glm::vec3> pos) {
	Pos = pos;
}

void Instances::drawInstances() {
	for (int i = 0; i < Pos.size(); i++) {
		float time = glfwGetTime() * 50.0f;
		float fixedRotate = i * 20.0f;

		float rotation = i % 3 == 0 ? time : fixedRotate;

		Obj
			.setTranslate(Pos[i])
			.setRotate(rotation, glm::vec3(1.0f))
			.draw();
	}
}