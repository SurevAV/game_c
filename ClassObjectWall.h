#pragma once

#define WALLS_CONSTRUCTOR rect = FloatRectItem(x, y); sprite.setTexture(Textures.WallBrick); 

void ClassObject::ConstructorWall() {


	switch (type) {
	case WALL1:
		WALLS_CONSTRUCTOR
		sprite.setTextureRect(IntRect(0, 0, 32, 32));
		armor = 50;
		isMoving = true;
		break;


	case WALL2:
		WALLS_CONSTRUCTOR
		sprite.setTextureRect(IntRect(32, 0, 32, 32));
		armor = 1000;
		isMoving = true;
		break;

	case WALL3:
		WALLS_CONSTRUCTOR
		sprite.setTextureRect(IntRect(96, 0, 32, 32));
		armor = 10;
		isMoving = true;
		break;

	case WALL4:
		WALLS_CONSTRUCTOR
		sprite.setTextureRect(IntRect(64, 32, 32, 32));
		armor = 1000;
		break;

	case WALLITEM:
		rect = FloatRectItem(x, y, 64, 64); 
		sprite.setTexture(Textures.WallBrick);
		sprite.setTextureRect(IntRect(32, 64, 64, 64));
		armor = 1000;
		break;

	case TNT:
		WALLS_CONSTRUCTOR
		sprite.setTextureRect(IntRect(64, 0, 32, 32));
		armor = 10;
		isMoving = true;
		break;

	case MAP:
		WALLS_CONSTRUCTOR
		sprite.setTextureRect(IntRect(0, 32, 32, 32));
		armor = 100000;
		viewSize = 35;
		break;

	case REMONT:
		WALLS_CONSTRUCTOR
		sprite.setTextureRect(IntRect(32, 32, 32, 32));
		armor = 10;
		viewSize = 35;
		break;

	case WOOD:
		WALLS_CONSTRUCTOR
		sprite.setTextureRect(IntRect(0, 64, 32, 64));
		armor = 10;
		viewSize = 35;
		//shiftSprite = 32.0f;
		break;

	default:
		break;
	}
}



void ClassObject::WallCollision(bool down, bool left, bool up, bool right, int item) {

	if (ListMain[item].typeGroup == PLAYERS) {
		if (type == REMONT) {
			ListMain[item].armor = ListMain[item].armorMax;
			ListMain[item].countWeapons = ListMain[item].countWeaponsMax;
			armor = -1;
		}
		else if (type == MAP) {
			triggerMakeMap = true;
		}
	}




	if (isMoving) {

		isMoved = true;

		if (ListMain[item].direction == DOWN) {
			rect.top = ListMain[item].rect.down();
			for (MAIN_RANGE) {
				if (IS_COLLISION && CN != item) {
					rect.top = rect_top(CN) - rect.height;
				}
			}
		}
		if (ListMain[item].direction == LEFT) {
			rect.left = ListMain[item].rect.left-rect.width;
			for (MAIN_RANGE) {
				if (IS_COLLISION && CN != item) {
					rect.left = rect_right(CN);
				}
			}
		}
		if (ListMain[item].direction == UP) {
			rect.top = ListMain[item].rect.top- rect.height;
			for (MAIN_RANGE) {
				if (IS_COLLISION && CN != item) {
					rect.top = rect_down(CN);
				}
			}
		}
		if (ListMain[item].direction == RIGHT) {
			rect.left = ListMain[item].rect.right();
			for (MAIN_RANGE) {
				if (IS_COLLISION && CN != item) {
					rect.left = rect_left(CN) - rect.width;
				}
			}
		}

	}
}