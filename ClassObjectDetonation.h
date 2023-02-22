#pragma once


void ClassObject::ConstructorDetonation() {
	if (type == DETONATION) {
		armor = 100000;
		rect = FloatRectItem(x - sizeDetonation, y - sizeDetonation, sizeDetonation * 2, sizeDetonation * 2);
		typeGroup = DETONATIONS;

		for (MAIN_RANGE) {
			if (IS_COLLISION && ITEM.typeGroup != DETONATIONS) {
				ITEM.armor -= 1000;
			}
		}
		clock.restart().asSeconds();
	}
}

void ClassObject::DetonationUpdate() {
	if (clock.getElapsedTime().asSeconds() > 0.1) {
		armor = -1;
	}
}


