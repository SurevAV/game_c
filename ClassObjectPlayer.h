#pragma once

#define REDUCE_ARMOR if (Shift>240 && ITEM.typeGroup != PLAYERS) ITEM.armor = -100 * deltaShift;

void ClassObject::ConstructorPlayer() {

	if (type == PLAYER1 || type == PLAYER2) {
		rect = FloatRectItem(x, y, 30, 30);
		PlayerMakeSprite(Textures.SilhouetteNpc, Textures.WeaponNpc);
		typeGroup = PLAYERS;
		clock.restart().asSeconds();
		clockChangeWeapon.restart().asSeconds();
		//sprite.setColor(Color(255, 255, 255, 1));
		armor = 2000;
		armorMax = 2000;
		countWeapons = 2000;
		countWeaponsMax = 2000;
		SideSizeX = 30;
		Shift = 60.0f;
		WaitWeapon = 0.5f;
		//activeArmor = true;
		sizeDetonation = 100.0f;
		isMoving = true;

		listTargetTypes[0] = NPC;
		listTargetTypes[1] = NPC3;
		sizeListTargetTypes = 2;
		viewSize = 200.0;
		unionPlayer = false;
		targetId = 0;

		distanceUseWeapon = 10.0f;
	}

	
}
void ClassObject::PlayerUpdate() {
	Shift = 60.0f;

	if (armor < armorMax && countWeapons > 100) {
		armor += 10 * deltaShift;
		countWeapons -= 5 * deltaShift;
	}

	if (type == PLAYER1){
		PlayerKey(
			KEYS(Keyboard::S),
			KEYS(Keyboard::A),
			KEYS(Keyboard::W),
			KEYS(Keyboard::D),
			KEYS(Keyboard::E),
			KEYS(Keyboard::Q),
			KEYS(Keyboard::R),
			KEYS(Keyboard::Z));
	}
	else {
		PlayerKey(
			KEYS(Keyboard::K),
			KEYS(Keyboard::J),
			KEYS(Keyboard::I),
			KEYS(Keyboard::L),
			KEYS(Keyboard::O),
			KEYS(Keyboard::U),
			KEYS(Keyboard::P),
			KEYS(Keyboard::M));
	}

}

void ClassObject::PlayerMakeSprite(Texture& caterpillar, Texture& platform) {
	spriteSilhouetteNpc.setTexture(caterpillar);
	spriteWeaponNpc.setTexture(platform);
	spriteSilhouetteNpc.setTextureRect(IntRect(0, 0, 30, 30));
	spriteWeaponNpc.setTextureRect(IntRect(0, 0, 30, 30));

}


void ClassObject:: PlayerColor(Color color) {
	spriteSilhouetteNpc.setColor(color);
	spriteWeaponNpc.setColor(color);

}



void ClassObject::PlayerKey(
	bool down, 
	bool left, 
	bool up, 
	bool right,
	bool weapon, 
	bool changeWeapon,
	bool kick,
	bool script) {


	if (colorChange) {
		PlayerColor(Color(255, 255, 255));
		colorChange = false;
	};

	if (script && countWeapons > 0) {
		Shift = 250;
		NpcUpdate();
		countWeapons -= 250 * deltaShift;
		PlayerColor(Color(10, 10, 10, 125));
		colorChange = true;
	};
	
	

	if (down || left || right || up) { 
		shiftCurrentFrame(3.0f, 2.0f);
		isMoved = true;
	}
	

	if (kick && countWeapons > 0) {
		Shift = 120;
		countWeapons -= 100 * deltaShift;
	}
	
	if (down) {
		DOWN_ANIMATION
		rect.top += DELTA_SHIFT;
		for (MAIN_RANGE) {
			if (IS_COLLISION) {
				ITEM.WallCollision(down, false, false, false, id);
				rect.top = rect_top(CN) - rect.height;
				REDUCE_ARMOR
			}
		}
	}
	if (left) {
		LEFT_ANIMATION
		rect.left -= DELTA_SHIFT;
		for (MAIN_RANGE) {
			if (IS_COLLISION) {
				ITEM.WallCollision(false, left, false, false, id);
				rect.left = rect_right(CN);
				REDUCE_ARMOR
			}
		}
	}
	if (up) {
		UP_ANIMATION
		rect.top -= DELTA_SHIFT;
		for (MAIN_RANGE) {
			if (IS_COLLISION) {
				ITEM.WallCollision(false, false, up, false, id);
				rect.top = rect_down(CN);
				REDUCE_ARMOR
			}
		}
	}
	if (right) {
		RIGHT_ANIMATION
		rect.left += DELTA_SHIFT;
		for (MAIN_RANGE) {
			if (IS_COLLISION) {
				ITEM.WallCollision(false, false, false, right, id);
				rect.left = rect_left(CN) - rect.width;
				REDUCE_ARMOR
			}
		}
	}

	if (weapon) {
		if (clock.getElapsedTime().asSeconds() > WaitWeapon && countWeapons > 0) {
			//for (int i = i_OBJECTS; i < COUNT_LIST; ++i) {
			for (int i = COUNT_LIST-1 ; i > i_OBJECTS; --i) {
				if (!ListMain[i].isWork) {
					
					ListMain[i] = ClassObject(rect.left, rect.top, typeWeapon, i, direction, ListMain, id);

					countWeapons -= ListMain[i].priceWeapon;
					if (countWeapons < 0) countWeapons = 0;

					WaitWeapon = ListMain[i].weaponReloading;
					clock.restart().asSeconds();
					break;
				}
			}
		};
	}





	if (changeWeapon) {

		if (clockChangeWeapon.getElapsedTime().asSeconds() > 0.15) {
			typeWeapon += 1;
			clockChangeWeapon.restart().asSeconds();
			if (typeWeapon > SWORD) typeWeapon = ARROW;
		}

	}
}