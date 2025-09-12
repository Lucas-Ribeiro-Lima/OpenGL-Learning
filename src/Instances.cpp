#include "Instances.h"

Instances::Instances(std::unique_ptr<Model> obj, glm::vec3 pos): obj(std::move(obj)) {
	Pos.push_back(pos);
};

void Instances::setInstances(Positions pos) {
	Pos = pos;
}

void Instances::drawInstances() {
	for (int i = 0; i < Pos.size(); i++) {
		(*obj)
			.setTranslate(Pos[i])
			.draw();
	}
}