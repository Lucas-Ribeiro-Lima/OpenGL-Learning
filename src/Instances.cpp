#include "Instances.h"

Instances::Instances(Model* o, Positions p): obj(o), Pos(p) {};

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