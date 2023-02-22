#pragma once
#include "ClassListTexture.h"



using namespace sf;
using namespace std;
using namespace ListTextureItems;





class ClassItems {
public:

	

	Sprite sprite;


	Sprite spriteSilhouetteNpc;
	Sprite spriteWeaponNpc;

	FloatRectItem rect;
	Clock clock;
	float currentFrame = 0;
	int type;
	int id;
	bool isWork = false;
	int direction;
	float armor;
	float armorMax;
	int IdOwner;
	int SideSizeX;
	int SideSizeY;
	int typeGroup = 0;
	float isMoved = false;
	float remake = 240.0f;

	float x;
	float y;

	//Weapon
	float Shift;
	int priceWeapon = 0;
	bool arrowIsMake = false;
	float arrowDistance = 500; //peredelat
	float weaponReloading = 0;
	//Weapon


	//players
	int typeWeapon= ARROW;
	float countWeapons = 100;
	float countWeaponsMax = 100;
	float WaitWeapon = 2;
	//bool activeArmor = false;
	bool colorChange = false;
	Clock clockChangeWeapon;
	//players

	//npc
	float distanceUseWeapon = 100;
	float viewSize;
	Clock clockView;
	int listTargetTypes[10];
	int sizeListTargetTypes;
	int targetId = 0;
	bool unionPlayer = false;
	//npc


	//detonation
	float sizeDetonation;
	//detonation


	//wall
	bool isMoving = false;
	//float shiftSprite = 0;
	//wall



	void shiftCurrentFrame(float step, float max) {
		currentFrame += step* deltaShift;
		if (currentFrame > max) currentFrame = 0;
	}


};





class ClassObject : public ClassItems
{

public:

	ClassObject* ListMain;

	ClassObject()
	{
	}

	ClassObject(float _x, float _y, int _type, int _id, int _direction, ClassObject* _ListMain, int _IdOwner, float _sizeDetonation = 100)
	{
		isMoved = false;
		isWork = true;
		IdOwner = _IdOwner;
		ListMain = _ListMain;
		direction = _direction;
		type = _type;
		id = _id;
		x = _x;
		y = _y;
		armor = 100;
		armorMax = 100;
		sizeDetonation = _sizeDetonation;
	

		ConstructorBunker();
		ConstructorPlayer();
		ConstructorWall();
		ConstructorWeapon();
		ConstructorNpc();
		ConstructorDetonation();
	}
	//Bunker-----------------------------------------------------------------------------
	void ConstructorBunker();
	void BunkerUpdate();
	//Bunker-----------------------------------------------------------------------------

	//Wall-------------------------------------------------------------------------------
	void ConstructorWall();
	void WallCollision(bool down, bool left, bool up, bool right, int item);
	//Wall-------------------------------------------------------------------------------

	//Weapon-----------------------------------------------------------------------------
	void ConstructorWeapon();
	void WeaponConstructorDirection(int widht, int hight);
	void WeaponCollision(int i);
	void WeaponUpdate();
	//Weapon-----------------------------------------------------------------------------

	//Player-----------------------------------------------------------------------------
	void ConstructorPlayer();
	void PlayerColor(Color color);
	void PlayerKey(bool down, bool left, bool up, bool right, bool weapon, bool changeWeapon, bool kick, bool script);
	void PlayerUpdate();
	void PlayerMakeSprite(Texture& silhouette, Texture& weapon);
	//Player-----------------------------------------------------------------------------

	//Npc--------------------------------------------------------------------------------
	void ConstructorNpc();
	bool NpcCheckUnion(int i);
	void NpcUpdate();
	//Npc--------------------------------------------------------------------------------


	//Detonation-------------------------------------------------------------------------
	void ConstructorDetonation();
	void DetonationUpdate();
	//Detonation-------------------------------------------------------------------------


	
	void update();
	void deleteObject();
	


	
};
#include "ClassObjectWeapon.h"
#include "ClassObjectPlayer.h"
#include "ClassObjectUpdate.h"
#include "ClassObjectWall.h"
#include "ClassObjectBunker.h"
#include "ClassObjectNpc.h"
#include "ClassObjectDetonation.h"
