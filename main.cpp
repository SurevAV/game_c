#include <SFML/Graphics.hpp>
#include <iostream>
#include "ClassObject.h"
#include<windows.h>
#include<fstream>
#include "ClassOpenMap.h"
#include "ClassMenu.h"


using namespace sf;
using namespace std;


int checkBackView(float item, int size) {
	int x = (int)item;
	if (x < 0) {return 0;}
	else if (x > size) {return size;}
	else {return x;};
};

int main()
{
	RenderTexture pictureMap;
	pictureMap.create(500, 500);
	//pictureMap.clear(Color(150, 150, 150));
	Textures.spriteMapWall.setPosition(0, 0);

	pictureMap.draw(Textures.spriteMapWall);
	
	

	
	ClassObject* ListMain = new ClassObject[COUNT_LIST];

	
	//ListMain[3] = ClassObject(10050, 10050, NPC, 3, RIGHT, ListMain, 0);
	float CameraX = rect_left(i_PLAYER1);
	float CameraY = rect_top(i_PLAYER1);


	float MapSizeX = WIDHT_LEVEL * 32 - ScreenWidth;
	float MapSizeY = HEIGHT_LEVEL * 32 - ScreenHeight;



	ClassOpenMap Map(ListMain);
	//Map.openLevel(ListMain);
	Map.makeLevelRandom(ListMain, pictureMap);
	//Map.makeMapRandom(ListMain);




	//_____________________________________________________________


	RenderWindow window(VideoMode((int)ScreenWidth, (int)ScreenHeight), "Caterpillar");

	

	ClassMenu menu = ClassMenu();
	Event key;
	Clock clock;

	float ScreenWidthReduce = ScreenWidth / 2 + 50;
	float ScreenHeightReduce = ScreenHeight / 2 + 50;

	float ScreenWidth2 = ScreenWidth / 2;
	float ScreenHeight2 = ScreenHeight / 2;
	
	//sf::Clock clock2;
	//sf::Time t;
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	while (window.isOpen())
	{

		deltaShift = clock.restart().asSeconds();
		//clock2.restart().asSeconds();
		window.clear();

		while (window.pollEvent(key))
		{
			if (key.type == Event::Closed) window.close();
		}

		
	
		
		if (menu.Esc()) {
			menu.MainMenuView( window);
			menu.ChangeSelected(window, ListMain);
		}
		else if (menu.Map()) {


			

			Sprite item;
			item.setTexture(pictureMap.getTexture());
			item.setPosition(0, 0);
			window.draw(item);

			Textures.spriteMapPlayer.setPosition((float)checkBackView(CameraX / 32.0f, WIDHT_LEVEL)-2,
				(float)checkBackView(CameraY / 32.0f, HEIGHT_LEVEL)-2);
			window.draw(Textures.spriteMapPlayer);


			Textures.spriteMapPlayer.setPosition((float)checkBackView(rect_left(IdLevelItem) / 32.0f, WIDHT_LEVEL)-2,
				(float)checkBackView(rect_top(IdLevelItem) / 32.0f, HEIGHT_LEVEL)-2);
			window.draw(Textures.spriteMapPlayer);
		}


		else {
		


			if (triggerMakeMap) Map.makeLevelRandom(ListMain, pictureMap);// Map.openLevel(ListMain); //Map.makeMapRandom(ListMain);//


			countCollisionItems = 0;
		
			
		
			for (int i = 0; i < COUNT_LIST; ++i) {

				if (ListMain[i].isWork) {
				

					if (abs(rect_centerX(i) - CameraX) <= ScreenWidthReduce && abs(rect_centerY(i) - CameraY) <= ScreenHeightReduce) {
						numbersCollisionItems[countCollisionItems] = i;
						countCollisionItems += 1;
					}
					else {
						if (ListMain[i].typeGroup == WEAPONS) ListMain[i] = ClassObject();
					}
				}
				else if(ListMapItems[i].isRemake())
				{
					ListMain[i] = ClassObject(ListMapItems[i].x, ListMapItems[i].y, ListMapItems[i].type, i, RIGHT, ListMain, 0);
				}
			}
	
			//cout << countCollisionItems << " countCollision" <<  '\n';
			for (MAIN_RANGE) {
				ITEM.update();
				if (ITEM.armor <= 0) { 
					ListMapItems[CN].deleteItem(ITEM.type);
					ITEM.deleteObject();
				}
			};




			if (ListMain[i_PLAYER1].isWork && ListMain[i_PLAYER2].isWork) {
				CameraX = (rect_centerX(i_PLAYER1) + rect_centerX(i_PLAYER2)) / 2.0f;
				CameraY = (rect_centerY(i_PLAYER1) + rect_centerY(i_PLAYER2)) / 2.0f;
			}
			else if (ListMain[i_PLAYER1].isWork && !ListMain[i_PLAYER2].isWork) {
				CameraX = rect_centerX(i_PLAYER1);
				CameraY = rect_centerY(i_PLAYER1);
			}
			else if (ListMain[i_PLAYER2].isWork && !ListMain[i_PLAYER1].isWork) {
				CameraX = rect_centerX(i_PLAYER2);
				CameraY = rect_centerY(i_PLAYER2);
			};

			float ShiftX = CameraX - ScreenWidth2;
			float ShiftY = CameraY - ScreenHeight2;

			if (ShiftX < 0) ShiftX = 0;
			if (ShiftX > MapSizeX) ShiftX = MapSizeX;
			if (ShiftY < 0) ShiftY = 0;
			if (ShiftY > MapSizeY) ShiftY = MapSizeY;

			//Back
			int FromBackCoordinateX = checkBackView((CameraX - ScreenWidthReduce) / 32,WIDHT_LEVEL);
			int ToBackCoordinateX = checkBackView((CameraX + ScreenWidthReduce) / 32, WIDHT_LEVEL);

			int FromBackCoordinateY = checkBackView((CameraY - ScreenHeightReduce) / 32, HEIGHT_LEVEL);
			int ToBackCoordinateY = checkBackView((CameraY + ScreenHeightReduce) / 32, HEIGHT_LEVEL);

			for (int i = FromBackCoordinateY; i < ToBackCoordinateY; ++i) {
				for (int j = FromBackCoordinateX; j < ToBackCoordinateX; ++j) {

					Textures.spriteBackground.setTextureRect(ListBack[i][j].spriteRect);
					Textures.spriteBackground.setPosition(ListBack[i][j].rect.left - ShiftX,
						ListBack[i][j].rect.top - ShiftY);
					window.draw(Textures.spriteBackground);

				}
			}

			//Weapons
			for (MAIN_RANGE) {
				if (ITEM.typeGroup == WEAPONS) {
					ITEM.sprite.setPosition(rect_left(CN) - ShiftX, rect_top(CN) - ShiftY);
					window.draw(ITEM.sprite);
				}
			}


			//Walls
			for (MAIN_RANGE) {

				if (ITEM.typeGroup != WEAPONS && ITEM.typeGroup != DETONATIONS) {
					float x = 0;
					float y = 0;

					if (ITEM.typeGroup == PLAYERS || ITEM.isMoved) {
						x = rect_left(CN) - ShiftX;
						y = rect_top(CN) - ShiftY;
						ITEM.isMoved = false;
					}
					else {
						x = round(rect_left(CN)) - ShiftX;
						y = round(rect_top(CN)) - ShiftY;
					}

					if (ITEM.typeGroup == NPCS || ITEM.typeGroup == PLAYERS) {

						ITEM.spriteSilhouetteNpc.setPosition(x, y);
						ITEM.spriteWeaponNpc.setPosition(x, y);

						window.draw(ITEM.spriteSilhouetteNpc);
						window.draw(ITEM.spriteWeaponNpc);

					}
					else {
						ITEM.sprite.setPosition(x, y);
						window.draw(ITEM.sprite);
					}
				}
			}


	

			//Detonations
			for (MAIN_RANGE) {
				if (ITEM.typeGroup == DETONATIONS) {
					Textures.circle.setOutlineThickness(ITEM.sizeDetonation * 0.1f);
					Textures.circle.setRadius(ITEM.sizeDetonation);
					Textures.circle.setPosition(rect_left(CN) - ShiftX, rect_top(CN) - ShiftY);
					window.draw(Textures.circle);
				}
			}


			menu.ScreenItems(ListMain[i_PLAYER1], 0, window);
			menu.ScreenItems(ListMain[i_PLAYER2], 1, window);


		}

		window.display();
	
		//t = clock2.getElapsedTime();
		//cout << 1.0 / t.asSeconds() << '\n';
	}

	return 0;
}

