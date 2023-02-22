#pragma once


void ClassObject::ConstructorWeapon() {

	if (type == ARROW) {
		armor = 40;
		Shift = 900.0f;
		arrowDistance = 250;
		sprite.setTexture(Textures.Arrow);

		WeaponConstructorDirection(2, 15);
		priceWeapon = 10;

		weaponReloading = 0.2;

		
		
	}

	else if (type == ARROW2) {
		armor = 10;
		Shift = 250.0f;
		priceWeapon = 1000;

		sprite.setTexture(Textures.Arrow2);
		WeaponConstructorDirection(4, 30);

		weaponReloading = 10;
	}

	else if (type == ARROW3) {
		armor = 200;
		Shift = 4500.0f;
		priceWeapon = 250;
		arrowDistance = 1500;
		sprite.setTexture(Textures.Arrow);
		WeaponConstructorDirection(2, 75);

		weaponReloading = 4;
	}

	else if (type == SWORD) {
		armor = 200;
		Shift = 0.0f;
		priceWeapon = 0;
		sprite.setTexture(Textures.Sword);
		
		SideSizeX = 6;
		SideSizeY = 26;
		WeaponConstructorDirection(SideSizeX, SideSizeY);
		weaponReloading = 0.5;
		clock.restart().asSeconds();
	}

	
}

void ClassObject::WeaponConstructorDirection(int widht, int hight) {
	typeGroup = WEAPONS;
	direction = ListMain[IdOwner].direction;
;


	if (direction == UP) {
		rect = FloatRectItem(
			rect_centerX(IdOwner) - (float)widht/2,
			rect_top(IdOwner) - (float)hight,
			(float)widht, (float)hight);
		sprite.setTextureRect(IntRect(0, 0, widht, hight));
	}

	else if (direction == RIGHT) {
		rect = FloatRectItem(
			rect_right(IdOwner),
			rect_centerY(IdOwner) - (float)widht / 2 ,
			(float)hight, (float)widht);
		sprite.setTextureRect(IntRect(widht, 0, hight, widht));
	}

	else if (direction == DOWN) {
		rect = FloatRectItem(
			rect_centerX(IdOwner) - (float)widht / 2,
			rect_down(IdOwner),
			(float)widht, (float)hight);
		sprite.setTextureRect(IntRect(0, hight, widht, -hight));
	}

	else if (direction == LEFT) {
		rect = FloatRectItem(
			rect_left(IdOwner)- (float)hight,
			rect_centerY(IdOwner) - (float)widht / 2,
			(float)hight, (float)widht);
		sprite.setTextureRect(IntRect(hight+ widht, 0, -hight, widht));
	}
}


void ClassObject::WeaponCollision(int i) {
	if (type == ARROW3) {
		ListMain[i].armor -= 10000 * deltaShift;
		armor -= 1500 * deltaShift;
		if (Shift > 1000) Shift -= 500;
	}
	else if (armor > ListMain[i].armor) {
		armor -= ListMain[i].armor;
		ListMain[i].armor = -1;
	}
	else {
		ListMain[i].armor -= armor;
		armor = -1;
	}


}

void ClassObject::WeaponUpdate() {


	if (abs(Shift) > 1) {

		if (arrowIsMake) {

			for (MAIN_RANGE) {
				if (IS_COLLISION && CN != IdOwner) WeaponCollision(CN);
			}

			if (direction == UP) {
				rect.top -= DELTA_SHIFT;
			}
			else if (direction == RIGHT) {
				rect.left += DELTA_SHIFT;
			}
			else if (direction == DOWN) {
				rect.top += DELTA_SHIFT;
			}
			else if (direction == LEFT) {
				rect.left -= DELTA_SHIFT;
			}
			arrowDistance -= abs(DELTA_SHIFT);
			if (arrowDistance < 0) armor = -1;
		}
		else {
			arrowIsMake = true;
		}

	}
	else {
		WeaponConstructorDirection(SideSizeX, SideSizeY);

		for (MAIN_RANGE) {
			if (IS_COLLISION && CN != IdOwner) ITEM.armor-=armor*deltaShift;
		}

		if (clock.getElapsedTime().asSeconds() > weaponReloading) {
			armor = -1;
		}
	}
}