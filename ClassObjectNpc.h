#pragma once

#define NPCS_CONSTRUCTOR typeGroup = NPCS; rect = FloatRectItem(x, y, 30, 30); clock.restart().asSeconds(); targetId = 0; WaitWeapon = 2;  countWeapons = 100000; isMoving = true;

void ClassObject::ConstructorNpc() {

	if (type == NPC) {
		NPCS_CONSTRUCTOR
		PlayerMakeSprite(Textures.SilhouetteNpc, Textures.WeaponNpc);
		
		armor = 100;
		armorMax = 100;
		SideSizeX = 30;
		Shift = 45.0f;

		listTargetTypes[2] = NPC2;
		listTargetTypes[0] = PLAYER1;
		listTargetTypes[1] = PLAYER2;
		sizeListTargetTypes = 3;

		viewSize = 300.0;
		typeWeapon = ARROW;

		unionPlayer = false;
		
	}


	else if (type == NPC2) {
		NPCS_CONSTRUCTOR
		PlayerMakeSprite(Textures.SilhouetteNpc, Textures.WeaponNpc);
		armor = 100;
		armorMax = 100;
		SideSizeX = 30;
		Shift = 45.0f;


		listTargetTypes[0] = PLAYER1;
		listTargetTypes[1] = PLAYER2;
		listTargetTypes[2] = NPC;
		listTargetTypes[3] = NPC3;
		sizeListTargetTypes = 4;

		viewSize = 300.0;

		typeWeapon = ARROW;
		//activeArmor = true;

		unionPlayer = true;
	}


	else if (type == NPC3) {
		NPCS_CONSTRUCTOR
		PlayerMakeSprite(Textures.SilhouetteNpc, Textures.WeaponNpc);
		armor = 100;
		armorMax = 100;
		SideSizeX = 30;
		Shift = 90.0f;

		listTargetTypes[0] = NPC2;
		listTargetTypes[1] = PLAYER1;
		listTargetTypes[2] = PLAYER2;
		listTargetTypes[3] = REMONT;
		sizeListTargetTypes = 4;

		viewSize = 300.0;

		typeWeapon = ARROW;

		unionPlayer = false;
	
	}
}

bool ClassObject::NpcCheckUnion(int i) {
	return ((ListMain[i].typeGroup == PLAYERS && unionPlayer) || typeGroup == PLAYERS) ? false : true;

}

void ClassObject::NpcUpdate() {
	//if (clockView.getElapsedTime().asSeconds() > 1 || typeGroup == PLAYERS) {
	//	targetId = 0;
	//	
	//	float distanceXmain = viewSize;
	//	float distanceYmain = viewSize;

	//	float distanceX = 0;
	//	float distanceY = 0;

	//	for (MAIN_RANGE) {
	//		distanceX = abs(rect_left(CN) - rect.left);//DISTANCE_X
	//		distanceY = abs(rect_top(CN) - rect.top);//DISTANCE_Y

	//		if (distanceX <= distanceXmain && distanceY <= distanceYmain)
	//		{
	//			for (int item = 0; item < sizeListTargetTypes; ++item) {

	//				if (ITEM.type == listTargetTypes[item]) {
	//					targetId = CN;

	//					if (unionPlayer) {
	//						if (ITEM.typeGroup != PLAYERS) {
	//							distanceXmain = distanceX;
	//							distanceYmain = distanceY;
	//						}
	//					}
	//					else {
	//						distanceXmain = distanceX;
	//						distanceYmain = distanceY;
	//					}
	//				}
	//			}
	//		}
	//	}
	//	clockView.restart().asSeconds();
	//}

	if (clockView.getElapsedTime().asSeconds() > 1 || typeGroup == PLAYERS) {
		targetId = 0;

		float distanceXmain = viewSize;
		float distanceYmain = viewSize;

		float distanceX = 0;
		float distanceY = 0;

		for (MAIN_RANGE) {

			float xItem = rect_centerX(CN) - rect.centerX();
			float yItem = rect_centerY(CN) - rect.centerY();
			bool skip = false;

			if (direction == LEFT && xItem >= 0) {
				skip = true;
			}
			else if (direction == RIGHT && xItem < 0) {
				skip = true;
			}
			else if (direction == UP && yItem >= 0) {
				skip = true;
			}
			else if (direction == DOWN && yItem < 0) {
				skip = true;
			}


			if (!skip || typeGroup == PLAYERS)
			{
				distanceX = abs(xItem);//DISTANCE_X
				distanceY = abs(yItem);//DISTANCE_Y

				if (distanceX <= distanceXmain && distanceY <= distanceYmain)
				{
					for (int item = 0; item < sizeListTargetTypes; ++item) {

						if (ITEM.type == listTargetTypes[item]) {
							targetId = CN;

							if (unionPlayer) {
								if (ITEM.typeGroup != PLAYERS) {
									distanceXmain = distanceX;
									distanceYmain = distanceY;
								}
							}
							else {
								distanceXmain = distanceX;
								distanceYmain = distanceY;
							}
						}
					}
				}
			}

		}
		clockView.restart().asSeconds();
	}


	if (targetId != 0) {

		
		float shiftX = rect.left - rect_left(targetId);
		float shiftY = rect.top - rect_top(targetId);

		if (abs(shiftX) <= abs(shiftY)) {
			if (shiftX < -2) {
				PlayerKey(false, false, false, true, false, false, false, false);
			}
			else if (shiftX > 2) {
				PlayerKey(false, true, false, false, false, false, false, false);
			}
			else {
				if (shiftY <= 0) {

					if (shiftY < -distanceUseWeapon) {
						PlayerKey(true, false, false, false, NpcCheckUnion(targetId), false, false, false);
					}
					else {
						DOWN_ANIMATION
						PlayerKey(false, false, false, false, NpcCheckUnion(targetId), false, false, false);
					}
				}
				else {
					if (shiftY > distanceUseWeapon) {
						PlayerKey(false, false, true, false, NpcCheckUnion(targetId), false, false, false);
					}
					else {
						UP_ANIMATION
						PlayerKey(false, false, false, false, NpcCheckUnion(targetId), false, false, false);
					}
				}
			}
		}
		else
		{
			if (shiftY < -2) {
				PlayerKey(true, false, false, false, false, false, false, false);
			}
			else if (shiftY > 2) {
				PlayerKey(false, false, true, false, false, false, false, false);
			}
			else {

				if (shiftX <= 0) {

					if (shiftX < -distanceUseWeapon) {
						PlayerKey(false, false, false, true, NpcCheckUnion(targetId), false, false, false);
					}
					else {
						RIGHT_ANIMATION
						PlayerKey(false, false, false, false, NpcCheckUnion(targetId), false, false, false);
					}
				}
				else {

					if (shiftX > distanceUseWeapon) {
						PlayerKey(false, true, false, false, NpcCheckUnion(targetId), false, false, false);
					}
					else {
						LEFT_ANIMATION
						PlayerKey(false, false, false, false, NpcCheckUnion(targetId), false, false, false);
					}

				}
			}
		}
	}
}