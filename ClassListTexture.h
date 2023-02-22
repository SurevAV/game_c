#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ClassObject.h"


#define CN numbersCollisionItems[i]
#define ITEM ListMain[CN]

#define MAIN_RANGE int i = 0; i < countCollisionItems; ++i
#define IS_COLLISION  rect.intersects(ITEM.rect) && CN != id && ITEM.typeGroup != WEAPONS && ITEM.typeGroup != DETONATIONS

#define MAIN_RANGE_BACK int i = 0; i < countCollisionBack; ++i
#define CN_BACK numbersCollisionBack[i]
#define DELTA_SHIFT Shift * deltaShift

#define RECT_IN_SPRITE IntRect((int)currentFrame * SideSizeX, SideSizeX*direction, SideSizeX, SideSizeX)
#define ANIMATION spriteSilhouetteNpc.setTextureRect(RECT_IN_SPRITE); spriteWeaponNpc.setTextureRect(RECT_IN_SPRITE);

#define LEFT_ANIMATION direction = LEFT; ANIMATION;
#define DOWN_ANIMATION direction = DOWN; ANIMATION;
#define RIGHT_ANIMATION direction = RIGHT; ANIMATION;
#define UP_ANIMATION direction = UP; ANIMATION;


#define i_PLAYER1 1 //can not use zero because zero is target npc deafult
#define i_PLAYER2 2
#define i_OBJECTS 4
#define COUNT_LIST 54000

#define WIDHT_LEVEL 500
#define HEIGHT_LEVEL 500




#define KEYS Keyboard::isKeyPressed


#define PLAYER1 1
#define PLAYER2 2

#define ARROW 100
#define ARROW2 101
#define ARROW3 102
#define SWORD 103

#define NPC 201
#define NPC2 202
#define NPC3 203




#define TNT 301
#define BUNKER2 302
#define WALL1 303
#define WALL2 304
#define MAP 305
#define WALL3 306
#define REMONT 307
#define WALL4 308
#define WOOD 309
#define WALLITEM 310

#define BACKGROUND 401
#define BACKGROUND2 402
#define BACKGROUND3 403
#define BACKGROUND4 404


#define DETONATION 4

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3



#define WEAPONS 1
#define DETONATIONS 2
#define BUNKERS 3
#define PLAYERS 4
#define NPCS 5



#define rect_left(item) ListMain[item].rect.left
#define rect_top(item) ListMain[item].rect.top
#define rect_down(item) ListMain[item].rect.down()
#define rect_right(item) ListMain[item].rect.right()
#define rect_centerX(item) ListMain[item].rect.centerX()
#define rect_centerY(item) ListMain[item].rect.centerY()

using namespace sf;
using namespace std;



class ClassListTexture {
public:

	Texture WallBrick;
	Texture Background;
	Texture Arrow;
	Texture Arrow2;
	Texture Bunker2;
	Texture Sword;




	Texture SilhouetteNpc;
	Texture WeaponNpc;



	CircleShape circle;

	//------------------
	Texture Armor;
	Texture countWeapons;
	Texture typeWeapon;

	Sprite spriteArmor;
	Sprite spriteCountWeapons;
	Sprite spriteTypeWeapon;
	//------------------

	//------------------
	Sprite spriteBackground;
	//------------------


	//map---------------

	Texture mapWall;
	Sprite spriteMapWall;


	Texture mapPlayer;

	Sprite spriteMapPlayer;
	//map---------------

	

	


	ClassListTexture() {

		Background.loadFromImage(openFile("images/background/background5.png"));

		WallBrick.loadFromImage(openFile("images/walls/brick/brick.png"));
		Arrow.loadFromImage(openFile("images/arrow/arrow.png"));
		Arrow2.loadFromImage(openFile("images/arrow/arrow2.png"));
		Sword.loadFromImage(openFile("images/arrow/sword.png"));

		Bunker2.loadFromImage(openFile("images/bunker/bunker2.png"));
		Armor.loadFromImage(openFile("images/interface/armor.png"));
		countWeapons.loadFromImage(openFile("images/interface/countArrows.png"));
		typeWeapon.loadFromImage(openFile("images/interface/arrows_type.png"));
	

		SilhouetteNpc.loadFromImage(openFile("images/npc/silhouette.png"));
		WeaponNpc.loadFromImage(openFile("images/npc/weapon.png"));

		mapWall.loadFromImage(openFile("images/walls/brick/WallMap.png"));
		mapPlayer.loadFromImage(openFile("images/walls/brick/PlayerMap.png"));

		circle.setRadius(50);
		circle.setFillColor(Color(255, 201, 14));
		circle.setOutlineThickness(50 * 0.1f);
		circle.setOutlineColor(sf::Color(255, 220, 25));



		spriteArmor.setTexture(Armor);
		spriteCountWeapons.setTexture(countWeapons);
		spriteTypeWeapon.setTexture(typeWeapon);


		spriteBackground.setTexture(Background);


	
		spriteMapWall.setTexture(mapWall);
		spriteMapPlayer.setTexture(mapPlayer);
	
	
	

	}

	Image openFile(string item) {
		Image image;
		image.loadFromFile(item);
		image.createMaskFromColor(Color(255, 255, 255));
		image.createMaskFromColor(Color(100, 100, 100));
		//ImageBackground.setPixel(10, 10, Color(0, 0, 0));
	
	
		return image;
	}

};


class FloatRectItem {
public:
	float width;
	float height;
	float top;
	float left;

	float reduceWidth;
	float reduceHeight;
	

	FloatRectItem() {
		width = 0.0f;
		height = 0.0f;
		top = 0.0f;
		left = 0.0f;
		reduceWidth = 0.0f;
		reduceHeight = 0.0f;

	}

	FloatRectItem(float rectLeft, float rectTop, float rectWidth = 32.0f, float rectHeight = 32.0f) {
		width = rectWidth;
		height = rectHeight;
		top = rectTop;
		left = rectLeft;

		reduceWidth = rectWidth / 2.0f;
		reduceHeight = rectHeight / 2.0f;

	}

	bool intersects(FloatRectItem item) {

		if (left < item.left + item.width &&
			left + width > item.left &&
			top < item.top + item.height &&
			height + top > item.top) {
			return true;
		}

		else {
			return false;
		}
	}

	float centerX() {return left + reduceWidth;}

	float centerY() {return top + reduceHeight;}

	float right() {return left + width;}

	float down() {return top + height;}



};



namespace ListTextureItems

{
	ClassListTexture Textures = ClassListTexture();

	
	int countCollisionItems = 0;
	int numbersCollisionItems[20000];




	bool triggerMakeMap = true;
	float deltaShift = 0.1f;


	float ScreenHeight = 500;
	float ScreenWidth = 500;

	int countPlayers = 1;
	
	int IdLevelItem = 0;

	#include "ClassObjectBack.h"


	ClassBack ListBack[HEIGHT_LEVEL][WIDHT_LEVEL];

	ClassMapItems ListMapItems[COUNT_LIST];



}
