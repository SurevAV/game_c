#pragma once

void ClassObject::update() {

	

	switch (typeGroup) {

		case DETONATIONS:
			DetonationUpdate();
			break;

		case PLAYERS:
			PlayerUpdate();
			break;

		case WEAPONS:
			WeaponUpdate();
			break;

		case BUNKERS:
			BunkerUpdate();
			break;

		case NPCS:
			NpcUpdate();
			break;

		default:
			break;
	}


}

void ClassObject::deleteObject() {
	if (type == TNT) {
		ListMain[id] = ClassObject(rect.centerX(), rect.centerY(), DETONATION, id, RIGHT, ListMain, id);
	}
	else if (type == ARROW2) {
		ListMain[id] = ClassObject(rect.centerX(), rect.centerY(), DETONATION, id, RIGHT, ListMain, id, 50);
	}
	else {
		ListMain[id] = ClassObject();
	}
}