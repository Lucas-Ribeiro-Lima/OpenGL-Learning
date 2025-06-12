#include "Instances.h"

Instances::Instances(Object* o, Positions p): obj(o), Pos(p) {};

void Instances::setInstances(std::vector<glm::vec3> pos) {
	Pos = pos;
}

void Instances::drawInstances() {
	for (int i = 0; i < Pos.size(); i++) {
		(*obj)
			.setTranslate(Pos[i])
			.draw();
	}
}