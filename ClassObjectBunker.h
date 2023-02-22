#pragma once



void ClassObject::ConstructorBunker() {

	if (type == BUNKER2) {
		rect = FloatRectItem(x, y);
		sprite.setTexture(Textures.Bunker2);
		sprite.setTextureRect(IntRect(0, 0, 32, 32));
		clock.restart().asSeconds();
		armor = 500;
		WaitWeapon = 5.0f;
		typeGroup = BUNKERS;
		type = BUNKER2;
		typeWeapon = ARROW;
		isMoving = true;
	
	}
}


void ClassObject::BunkerUpdate() {
	if (clock.getElapsedTime().asSeconds() > WaitWeapon) {
		int directionChange = 0;

		for (int i = COUNT_LIST - 1; i > i_OBJECTS; --i) {
			if (!ListMain[i].isWork) {
				if (directionChange == 0) {

					direction = UP;
					ListMain[i] = ClassObject(rect.left, rect.top, typeWeapon, i, direction, ListMain, id);
					
				}
				else if (directionChange == 1) {
			
					direction = LEFT;
					ListMain[i] = ClassObject(rect.left, rect.top, typeWeapon, i, direction, ListMain, id);
				}
				else if (directionChange == 2) {
			
					direction = DOWN;
					ListMain[i] = ClassObject(rect.left, rect.top, typeWeapon, i, direction, ListMain, id);
				}
				else if (directionChange == 3) {
			
					direction = RIGHT;
					ListMain[i] = ClassObject(rect.left, rect.top, typeWeapon, i, direction, ListMain, id);
					break;
				}
				directionChange+=1;
	
			}

		}

		clock.restart().asSeconds();
	};
}