#pragma once

class ClassBack {
public:
	IntRect spriteRect;
	FloatRectItem rect;
	ClassBack(float x, float y, int type)
	{
		rect = FloatRectItem(x, y);
		if (type == BACKGROUND) {
			spriteRect = IntRect(0, 0, 32, 32);
		}
		else if (type == BACKGROUND2) {
			spriteRect = IntRect(32, 0, 32, 32);
		}
		else if (type == BACKGROUND3) {
			spriteRect = IntRect(64, 0, 32, 32);
		}
		else if (type == BACKGROUND4) {
			spriteRect = IntRect(96, 0, 32, 32);
		}
	};

	ClassBack() {};
};

class ClassMapItems {
public:
	Clock clock;
	float x;
	float y;

	float remake;
	int type = 0;
	bool isItem = false;

	ClassMapItems(float _x, float _y, int _type, float _remake) {
		x = _x;
		y = _y;
		type = _type;
		isItem = true;
		remake = _remake;

	}
	ClassMapItems() {
		isItem = false;
	}

	void deleteItem(int item) {
		if (item == type) clock.restart().asSeconds();
	}

	bool isRemake() {
		return isItem && clock.getElapsedTime().asSeconds() > remake;
	}
};