#pragma once

#define RANDOM1000 (rand() * (int)(10000) / RAND_MAX) 
#define LEVEL_SIZE 500
#define WALL_DELETE levelList[y][x] = 0; levelList[check(y - 1)][x] = 0; levelList[check(y - 1)][check(x - 1)] = 0; levelList[y][check(x - 1)] = 0;

class ClassOpenMap {
public:

	int level = 0;

	string names[2][2] = {
		{"level1.csv", "level1Surface.csv"},
		{"level1.csv", "level1Surface.csv"}, };

	ClassObject* ListMain;

	int levelList[LEVEL_SIZE][LEVEL_SIZE];

	ClassOpenMap(ClassObject* _ListMain) {
		ListMain = _ListMain;
	}



	void openCSVSurface(string name) {

		int x = 0, y = 0;

		ifstream file;
		string line;

		string delim;
		delim = ';';

		file.open(name);
		int row = 0;
		while (!file.eof()) {
			file >> line;

			size_t prev = 0, pos = 0;
			int i = 0;
			do
			{
				pos = line.find(delim, prev);
				if (pos == string::npos) pos = line.length();
				string token = line.substr(prev, pos - prev);

				if (!token.empty()) 
				{

					ListBack[row][i] = ListTextureItems::ClassBack((float)x, (float)y, stoi(token));

					i += 1;
					x += 32;

				}
				
				prev = pos + delim.length();
			} while (pos < line.length() && prev < line.length());

			//cout << row << i <<'\n';

			row += 1;

			y += 32;
			x = 0;

		}
		file.close();
	}

	void openCSVLevel(string name, ClassObject* ListMain) {

		int x = 0, y = 0, index = i_PLAYER1 + 3;

		ifstream file;
		string line;

		string delim;
		delim = ';';

		file.open(name);
		int row = 0;
		while (!file.eof()) {
			file >> line;

			size_t prev = 0, pos = 0;
			int i = 0;
			do
			{
				pos = line.find(delim, prev);
				if (pos == string::npos) pos = line.length();
				string token = line.substr(prev, pos - prev);

				if (!token.empty()) {

					if (stoi(token) != 0)
					{
						ListMain[index] = ClassObject((float)x, (float)y, stoi(token), index, RIGHT, ListMain, 0);
						ListMapItems[index] = ListTextureItems::ClassMapItems((float)x, (float)y, stoi(token), ListMain[index].remake);
						index += 1;
					}

					i += 1;
					x += 32;

				}

				prev = pos + delim.length();
			} while (pos < line.length() && prev < line.length());

			//cout << row << i <<'\n';

			row += 1;

			y += 32;
			x = 0;

		}
		file.close();
	}




	void openLevel(ClassObject* ListMain) {
		openCSVLevel(names[level][0], ListMain);
		openCSVSurface(names[level][1]);
		triggerMakeMap = false;
		level += 1;

	}

	int check(int item) {
		if (item > LEVEL_SIZE - 2) {
			return LEVEL_SIZE - 1;
		}
		else if (item < 1) {
			return 1;
		}
		else{
			return item;
		}
	}

	int randomInt(int from, int to) {
		int item = (int)(rand() * (int)(to) / RAND_MAX);
		if (item < from) {
			return from;
		}
		else {
			return item;
		}

	}

	void makeLevelRandom(ClassObject* ListMain, RenderTexture& pictureMap) {
		srand(time(NULL));

		
		for (int row = 0; row < LEVEL_SIZE; ++row) {
			for (int col = 0; col < LEVEL_SIZE; ++col) {
				levelList[row][col] = 1;
			}
		}

		int const count = 300;

		int randomList[count][2];

		for (int i = 0; i < count; ++i) {
			randomList[i][0] = randomInt(1, LEVEL_SIZE - 1);
			randomList[i][1] = randomInt(1, LEVEL_SIZE - 1);

			int sizeX = check(randomList[i][0] + randomInt(2, 40));
			int sizeY = check(randomList[i][1] + randomInt(2, 40));

			for (int n = randomList[i][1]; n < sizeY; ++n) {
				for (int j = randomList[i][0]; j < sizeX; j++) {
					levelList[n][j] = 0;
				}
			}
		}


		for (int i = 0; i < count; ++i) {
			int number = i;
			for (int j = i; j < count; ++j) {
				if (i != j) {
					int distanceX = abs(randomList[number][0] - randomList[j][0]);
					int distanceY = abs(randomList[number][1] - randomList[j][1]);

					if (distanceX <= 50 && distanceY <= 50) {
						number = j;
					}
				}
			}

			int itemX = randomList[i][0];
			int itemY = randomList[i][1];

			int ToItemX = randomList[number][0];
			int ToItemY = randomList[number][1];

			int x = itemX;
			int y = itemY;


			if (itemY < ToItemY) {
				for (int j = itemY; j < ToItemY; ++j) {
					y = j;
					WALL_DELETE
				}
			}
			else {
				for (int j = itemY; j > ToItemY; --j) {
					y = j;
					WALL_DELETE
				}
			};

			if (itemX < ToItemX) {
				for (int j = itemX; j < ToItemX; ++j) {
					x = j;
					WALL_DELETE
				}
			}
			else {
				for (int j = itemX; j > ToItemX; --j) {
					x = j;
					WALL_DELETE
				}
			};

		}

		//ofstream myFile("WorkLevel.csv");
		//for (int i = 0; i < LEVEL_SIZE; ++i) {
		//	string row = "";
		//	for (int j = 0; j < LEVEL_SIZE; ++j) {
		//		string itemString = "0";
		//		if (levelList[i][j] == 0) {
		//			itemString = " ";
		//		}
		//		row = row + itemString + ";";
		//	}
		//	myFile << row << "\n";
		//}
		//myFile.close();


		pictureMap.clear(Color(150,150,150));

		int x = 0, y = 0, index = i_PLAYER1 + 3;
		for (int row = 0; row < HEIGHT_LEVEL; row+=2) {
			for (int col = 0; col < WIDHT_LEVEL; col+=2) {
			
				int type = 0;

				if (levelList[row][col] == 1 && 
					levelList[row+1][col+1] == 1 )
				{
				
					//make pictureMap
					Textures.spriteMapWall.setPosition((float)col, (float)(HEIGHT_LEVEL-2 - row));
					pictureMap.draw(Textures.spriteMapWall);
					//make pictureMap

					ListMain[index] = ClassObject((float)x, (float)y, WALLITEM, index, RIGHT, ListMain, 0);
					ListMapItems[index] = ListTextureItems::ClassMapItems((float)x, (float)y, WALLITEM, ListMain[index].remake);
					index += 1;

				}
				x += 64;
			}
			y += 64;
			x = 0;
		}
	


		int wallsCount = index;


		bool playersMake = false;

		x = 0, y = 0;
		for (int row = 0; row < HEIGHT_LEVEL; ++row) {
			for (int col = 0; col < WIDHT_LEVEL; ++col) {

				int type = 0;
				if (RANDOM1000 < 200) type = WALL1;
				if (RANDOM1000 < 200) type = WALL2;
				if (RANDOM1000 < 500) type = NPC;
				if (RANDOM1000 < 100) type = TNT;
				//if (RANDOM1000 < 100) type = WOOD;
				if (RANDOM1000 < 200) type = WALL3;
				if (RANDOM1000 < 500) type = WALL4;
				if (RANDOM1000 < 200) type = NPC2;
				if (RANDOM1000 < 25 ) type = NPC3;
				if (RANDOM1000 < 20 ) type = BUNKER2;
				//if (RANDOM1000 < 5  ) type = MAP;
				if (RANDOM1000 < 100) type = REMONT;

				if (type != 0 && levelList[row][col] != 1 && index < COUNT_LIST)
				{

					if (!playersMake && x > 1000 && y > 1000 ) {
						ListMain[i_PLAYER1] = ClassObject((float)x, (float)y, i_PLAYER1, i_PLAYER1, RIGHT, ListMain, 0);
						ListMain[i_PLAYER2] = ClassObject();
			
						if (countPlayers == 2){
							ListMain[i_PLAYER2] = ClassObject((float)(x+32), (float)y, i_PLAYER2, i_PLAYER2, RIGHT, ListMain, 0);
						};
						playersMake = true;
					}



					ListMain[index] = ClassObject((float)x, (float)y, type, index, RIGHT, ListMain, 0);
					ListMapItems[index] = ListTextureItems::ClassMapItems((float)x, (float)y, type, ListMain[index].remake);
					index += 1;
				}

				type = BACKGROUND2;

				if (RANDOM1000 < 2000) type = BACKGROUND;
				if (RANDOM1000 < 2000) type = BACKGROUND3;
				if (RANDOM1000 < 2000) type = BACKGROUND4;


				ListBack[row][col] = ListTextureItems::ClassBack((float)x, (float)y, type);

				x += 32;
			}
			y += 32;
			x = 0;
		}
		

		IdLevelItem = randomInt(wallsCount+1, index-1);
		x = (int)rect_left(IdLevelItem);
		y = (int)rect_top(IdLevelItem);
		ListMain[IdLevelItem] = ClassObject((float)x, (float)y, MAP, index, RIGHT, ListMain, 0);
		ListMapItems[IdLevelItem] = ListTextureItems::ClassMapItems((float)x, (float)y, MAP, ListMain[IdLevelItem].remake);


		//cout << wallsCount << " " << IdLevelItem << " " << index << '\n';

		//cout << x << " " << y << '\n';
		triggerMakeMap = false;
	}


};

