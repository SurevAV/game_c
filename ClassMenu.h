#pragma once

class ClassMenu {
public:
	int selected = 0;
	bool mainMenu = false;
	float coordinate[2][4];
	Clock clockMenu;
	Font font;
	Text text;
	string ListMenu[5];
	int selectedInMenu = 0;

	bool mapMenu = false;
	bool mapMake = false;

	string instructions = "keys  player1:  S A W D E Q R Z,  keys  player2:  K J I L O U P M       Surev  Alexandr";

	ClassMenu() {
		coordinate[0][0] = 10;
		coordinate[0][1] = ScreenHeight - 15;
		coordinate[0][2] = ScreenHeight - 30;
		coordinate[0][3] = ScreenHeight - 45;

		coordinate[1][0] = ScreenWidth - 70;
		coordinate[1][1] = ScreenHeight - 15;
		coordinate[1][2] = ScreenHeight - 30;
		coordinate[1][3] = ScreenHeight - 45;


		ListMenu[0] = "1   Player";
		ListMenu[1] = "2  Player";
		ListMenu[2] = "Exit";


		
		font.loadFromFile("Letters.ttf");
		text.setFont(font);
		

	}

	void MainMenuView(RenderWindow& window) {
		text.setFillColor(Color(100, 100, 100));
	

		text.setCharacterSize(25);
		text.setString(instructions);
		text.setPosition(50, ScreenHeight-100);
		window.draw(text);

		text.setCharacterSize(50);
		for (int i = 0; i < 3; ++i) {
			text.setString(ListMenu[i]);
			i == selectedInMenu? text.setFillColor(Color(200, 200, 200)) : text.setFillColor(Color(100, 100, 100));
			

			text.setPosition(ScreenWidth/2-50, (float)i*70+300);
			window.draw(text);
		}
		
	}


	void ScreenItems(ClassObject player, int id, RenderWindow& window) {
		if (player.isWork) {

			Textures.spriteArmor.setTextureRect(IntRect(0, 0, (int)(49.0f / player.armorMax * player.armor), 11));
			Textures.spriteArmor.setPosition(coordinate[id][0], coordinate[id][1]);
			window.draw(Textures.spriteArmor);

			Textures.spriteCountWeapons.setTextureRect(IntRect(0, 0, (int)(49.0f / player.countWeaponsMax * player.countWeapons), 11));
			Textures.spriteCountWeapons.setPosition(coordinate[id][0], coordinate[id][2]);
			window.draw(Textures.spriteCountWeapons);

			Textures.spriteTypeWeapon.setTextureRect(IntRect((player.typeWeapon - ARROW) * 11, 0, 11, 11));
			Textures.spriteTypeWeapon.setPosition(coordinate[id][0], coordinate[id][3]);

			if (player.clock.getElapsedTime().asSeconds() < player.WaitWeapon) {
				Textures.spriteTypeWeapon.setColor(Color(100, 100, 100));
			}
			else {
				Textures.spriteTypeWeapon.setColor(Color(250, 250, 250));
			}
			window.draw(Textures.spriteTypeWeapon);

		}
	}

	bool Esc() {
		if (KEYS(Keyboard::Escape) && clockMenu.getElapsedTime().asSeconds() > 0.2) {
			clockMenu.restart().asSeconds();
			mainMenu ? mainMenu = false : mainMenu = true;
		}
		return mainMenu;
	}

	bool Map() {
		if (KEYS(Keyboard::Y) && clockMenu.getElapsedTime().asSeconds() > 0.2) {
			clockMenu.restart().asSeconds();
			mapMenu ? mapMenu = false : mapMenu = true;
		}
		return mapMenu;
	}

	void ChangeSelected(RenderWindow& window, ClassObject* ListMain) {
	
		if (KEYS(Keyboard::Down) && clockMenu.getElapsedTime().asSeconds() > 0.2) {
			clockMenu.restart().asSeconds();
			if (selectedInMenu < 2) selectedInMenu +=1;
			}

		if (KEYS(Keyboard::Up) && clockMenu.getElapsedTime().asSeconds() > 0.2) {
			clockMenu.restart().asSeconds();
			if (selectedInMenu > 0) selectedInMenu -= 1;
			}

		if (KEYS(Keyboard::Enter) && clockMenu.getElapsedTime().asSeconds() > 0.2) {
			clockMenu.restart().asSeconds();

			if (selectedInMenu == 2) window.close();

			if (selectedInMenu == 0) {
				triggerMakeMap = true;
				countPlayers = 1;
				mainMenu = false;
			}


			if (selectedInMenu == 1) {
				triggerMakeMap = true;
				countPlayers = 2;
				mainMenu = false;
			}
		}
	}


};
