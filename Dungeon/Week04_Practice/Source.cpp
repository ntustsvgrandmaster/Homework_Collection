/************************************************************************
File:        source.cpp

Author:
		鍾賢廣，ea5878158@gmail.com
Modifier:
		賴祐吉，cheeryuchi@gmail.com
		黃欣云，windyhuang6@gmail.com
		陳俊宇，JYCReports@gmail.com
Comment:
		基本輸入方向移動功能，w s a d 移動腳色上下左右，空白改變腳色站立之地板字元，到T上可以增加經驗
		ESC是離開畫面。同時更新圖版上的資訊。

************************************************************************/

#include "main.h"
#include "Hero.h"
#include "Creature.h"
#include "KeyandDoor.h"
#include "Trigger.h"
#include "GameBoard.h"
Hero	 gHero(2, 2);

// Constent value
std::string GWALL = "■";
std::string GNOTHING = "　";
std::string GDOOR = "Ｄ";

int GWIDTH;
int GHEIGHT;
const double gTimeLog = 0.033;

// Distance
const int gDistance = 4;

// 遊戲版面資料
std::string** gBoard;

// 看看是不是在guide模式
bool guide = false;

//看boss是否被擊倒
bool boss_dead = false;

// 定義六種輸入指令與對應陣列index
enum ValidInput
{
	EW = 0,
	ES = 1,
	EA = 2,
	ED = 3,
	ESPACE = 4,
	EESC = 5,
	EHELP = 6,
	INVALID,
};


Creature gCreature;
Bat gBat;
Angle gAngle;
std::vector<Creature*> creatureVec;
std::vector<Item*> itemVec;
std::vector<Stair*> stairVec;
Key gKey;
Door gDoor;
std::ifstream fin;
std::ofstream fout;

// function declare
// 偵測輸入狀態
void keyUpdate(bool key[]);
// 判斷位置是否為空
bool isPositionValid(Position& loc);
// 判斷位置是否為門
bool isDoor(Position& loc);
//設定門的位置
void setupDoor(int x, int y);
// 初始化版面
void setupBoard();
// 輸出版面
void draw(void);
// 輸出說明資訊
void drawInfo(void);
// 設定地圖資訊
void setupMap(std::string dataName);

// 程式主驅動函式
void update(bool key[]);

Trigger  gTrigger(5, 5, 10);
Trigger  gTrigger1;
GameBoard gb;

int main(int argc, char** argv)
{
	gb.printMenu();

	// 用來管理鍵盤輸入狀態的陣列
	bool gKeyState[7];

	// 讀入題庫
	gb.readQuiz();

	cout << "是否跳過新手教學?\n";
	cout << ">yes\n no";
	char j;
	while (j = _getch()) 
	{
		if (j == 'w' || j == 's' || j == -32) 
		{
			guide ^= 1;
		}
		else if (j == 13) 
		{
			break;
		}

		system("cls");
		cout << "是否跳過新手教學?\n";
		if (guide) cout << " yes\n>no";
		else cout << ">yes\n no";
	}
	system("cls");

	// Setup a clear dungeon
	setupMap("./maps/map1.txt");

	// Draw the bord and information
	std::cout << "pick up key to open the door!\n";
	draw();
	drawInfo();

	// Variable for game loop
	clock_t startT, endT;
	startT = clock();
	endT = clock();

	// Get the press key
	keyUpdate(gKeyState);

	// Run the game loop
	while (!gKeyState[ValidInput::EESC]) {
		// Compute the time lap
		double timeFrame = (double)(endT - startT) / CLOCKS_PER_SEC;

		// Execute the game loop
		if (timeFrame >= gTimeLog) {
			update(gKeyState);
			startT = clock();
		}

		// Win
		if (boss_dead)
		{
			break;
		}

		// gameOver
		if (gHero.getHealth() <= 0) {
			system("cls");
			string word = "GAME OVER";
			cout << endl;
			cout << "   ";
			for (int i = 0; i < word.size(); i++)
			{
				cout << word[i];
				Sleep(100);
			}
			cout << endl;
			break;
		}

		// Update the key
		keyUpdate(gKeyState);
		endT = clock();
	}
	system("cls");

	//印出遊戲計算分數的部分
	gb.getPoint(gHero);
	//
	system("pause>nul");
	return 0;
}

//******************************************************************
//
// * 偵測輸入狀態
//==================================================================
void keyUpdate(bool key[])
//==================================================================
{
	for (int i = 0; i < ValidInput::INVALID; i++) {
		key[i] = false;
	}
	char input = _getch();
	switch (input) {
	case 'w':
		key[ValidInput::EW] = true;
		break;
	case 's':
		key[ValidInput::ES] = true;
		break;
	case 'a':
		key[ValidInput::EA] = true;
		break;
	case 'd':
		key[ValidInput::ED] = true;
		break;
	case ' ':
		key[ValidInput::ESPACE] = true;
		break;
	case 'h':
		key[ValidInput::EHELP] = true;
		break;
	case 27:
		key[ValidInput::EESC] = true;
		break;
	default:
		break;
	}
}

//******************************************************************
//
// * 判斷位置是否為空
//==================================================================
bool isPositionValid(Position& pos)
//==================================================================
{
	// Check whether it is an empty space
	if (gBoard[pos.y][pos.x] == GNOTHING|| gBoard[pos.y][pos.x] == GDOOR) {
		return true;
	}
	return false;
}
//******************************************************************
//
// * 判斷位置是否為門
//==================================================================
bool isDoor(Position& pos)
//==================================================================
{
	if (gBoard[pos.y][pos.x] == GDOOR) {
		return true;
	}
	return false;
}
void setupDoor(int x, int y)
//==================================================================
{
	gBoard[x][y] = GDOOR;
}
	
//*******************************************************************
//這兩個是為了處理include windows.h會帶來的問題
//*******************************************************************
template<class T>
T my_max(T right, T left) 
{
	if (right > left) return right; return left;
}
//*******************************************************************
template<class T>
T my_min(T right, T left)
{
	if (right < left) return right; return left;
}
//==================================================================

//*******************************************************************
// 美化
//*******************************************************************
void SetColor(int color = 7)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

//******************************************************************
//
// * clip algroithm
//==================================================================
float clip(float n, float minimum, float maximum)
//==================================================================
{
	return my_max(minimum, my_min(n, maximum));
}

//******************************************************************
//
// * 利用 call-by-referce 將計算得到的方向回傳
//==================================================================
bool canSee(Position cPos, Position hPos, Position& dir)
//==================================================================
{
	// the dir_x and dir_y value are call-by-refernce
	dir.x = (int)clip((float)(hPos.x - cPos.x), -1.f, 1.f); // clip the value between -1 ~ 1
	dir.y = (int)clip((float)(hPos.y - cPos.y), -1.f, 1.f);
	int count = 0;
	do {
		// spot the target position
		if (cPos.x + dir.x * count == hPos.x &&
			cPos.y + dir.y * count == hPos.y) {
			return true;
		}
		count++;
	} while (count < gDistance); // check the range in 4 units
	return false;
}

//******************************************************************
//
// * Setup the board
//==================================================================
void setupBoard()
//==================================================================
{
	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			if (i == 0 || i == GHEIGHT - 1) {
				gBoard[i][j] = GWALL;
			}
			else if (j == 0 || j == GWIDTH - 1) {
				gBoard[i][j] = GWALL;
			}
			else {
				gBoard[i][j] = GNOTHING;
			}
		}
	}
}

//******************************************************************
//
// * Draw the board
//==================================================================
void draw()
//==================================================================
{
	// Add the hero into the board
	std::string **drawBoard;
	drawBoard = new string* [GHEIGHT];
	for (int i = 0; i < GHEIGHT; i++)
	{
		drawBoard[i] = new string[GWIDTH];
	}

	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			drawBoard[i][j] = gBoard[i][j];
		}
	}

	for (int i = 0; i < itemVec.size(); i++) {
		Position c = itemVec[i]->getPos();
		drawBoard[c.y][c.x] = itemVec[i]->getIcon();
	}

	for (int i = 0; i < stairVec.size(); i++) 
	{
		Position c = stairVec[i]->getPos();
		drawBoard[c.y][c.x] = stairVec[i]->getIcon();
	}

	// Update the hero information
	Position h = gHero.getPos();
	drawBoard[h.y][h.x] = gHero.getIcon();

	for (int i = 0; i < creatureVec.size(); i++) {
		Position c = creatureVec[i]->getPos();
		drawBoard[c.y][c.x] = creatureVec[i]->getIcon();


		if (h.x == c.x && h.y == c.y && creatureVec[i]->getIcon() == "Ａ")
		{
			gHero.damage(-gHero.getAtk() * 2);
			creatureVec[i]->getDamage(creatureVec[i]->getHealth());
		}
	}
	/************************************************************************/

	// Draw the board
	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			if (drawBoard[i][j] == "Ｔ") 
			{
				SetColor(47);
			}
			else if (drawBoard[i][j] == "Ｌ")
			{
				SetColor(11);
			}
			else if (drawBoard[i][j] == "Ｅ")
			{
				SetColor(8);
			}
			else if (drawBoard[i][j] == "Ｚ")
			{
				SetColor(2);
			}
			else if (drawBoard[i][j] == "Ｂ")
			{
				SetColor(6);
			}
			else if (drawBoard[i][j] == "Ｐ")
			{
				SetColor(12);
			}
			else if (drawBoard[i][j] == "Ｓ")
			{
				SetColor(79);
			}
			else if (drawBoard[i][j] == "Ｋ")
			{
				SetColor(111);
			}
			else if (drawBoard[i][j] == "Ｄ")
			{
				SetColor(111);
			}
			std::cout << drawBoard[i][j]; //  output
			SetColor();
		}
		std::cout << "\n";
	}
}

//******************************************************************
//
// * read and set up map
//==================================================================
void setupMap(std::string dataName)
//==================================================================
{
	fin.open(dataName);
	//先清除原本vector裡的東西
	while (creatureVec.size()) creatureVec.erase(creatureVec.begin());
	while (itemVec.size()) itemVec.erase(itemVec.begin());
	while (stairVec.size()) stairVec.erase(stairVec.begin());

	fin >> GHEIGHT >> GWIDTH;
	gBoard = new string* [GHEIGHT];
	for (int i = 0; i < GHEIGHT; i++)
	{
		gBoard[i] = new string[GWIDTH];
	}
	setupBoard();
	int amt, x, y; //讀取數量、座標用
	char type;
	//設置地宮
	fin >> amt;
	for (int i = 0; i < amt; i++) {
		fin >> x >> y;
		gBoard[x][y] = GWALL;
	}
	//設置英雄
	fin >> x >> y;
	gHero.setPos(y, x);
	//設置creature
	fin >> amt;
	for (int i = 0; i < amt; i++) {
		Position Pos;
		fin >> Pos.y >> Pos.x >> type;
		if (type == 'B')
		{
			creatureVec.push_back(new Bat(Pos));
		}
		else if (type == 'A')
		{
			creatureVec.push_back(new Angle(Pos));
		}
		else if (type == 'L') 
		{
			creatureVec.push_back(new Slime(Pos));
		}
		else if (type == 'E')
		{
			creatureVec.push_back(new Skeleton(Pos));
		}
		else if (type == 'Z')
		{
			creatureVec.push_back(new Zombie(Pos));
		}
		else if (type == 'P')
		{
			creatureVec.push_back(new Spider(Pos));
		}
		else
		{
			creatureVec.push_back(new Creature(Pos));
		}
	}
	//設置item
	fin >> amt;
	for (int i = 0; i < amt; i++) {
		Position Pos;
		fin >> Pos.y >> Pos.x >> type;
		if (type == 'K') 
		{
			itemVec.push_back(new Key(Pos));
		}
		else if (type == 'D')
		{
			itemVec.push_back(new Door(Pos));
			setupDoor(Pos.y, Pos.x);
		}
		else if (type == 'T') 
		{
			itemVec.push_back(new Trigger(Pos));
		}
	}
	//設置stair
	fin >> amt;	
	for (int i = 0; i < amt; i++) {
		Position Pos;
		std::string des;
		fin >> Pos.y >> Pos.x >> des;
		stairVec.push_back(new Stair(Pos, des));
	}
	fin.close();
}

//******************************************************************
//
// * Output information
//==================================================================
void drawInfo(void)
//==================================================================
{
	std::cout << "==============================================\n";
	std::cout << "英雄現在等級為 " << gHero.getLevel() << "\n";
	std::cout << "英雄現在有 " << gHero.getExp() << " 經驗值" << "\n";
	std::cout << "尚須 " << gHero.getMaxExp() - gHero.getExp() << " 來提升等級\n";
	std::cout << "英雄目前剩下 " << gHero.getHealth() << " 生命值\n\n";
	std::cout << "使用aswd來操控英雄\n";
	std::cout << "使用 h 來進入獲得幫助\n";
	std::cout << "使用Esc來離開遊戲\n";
	std::cout << "==============================================\n";
}

//******************************************************************
//
// * Output helping information
//==================================================================
void drawHelpInfo(void)
//==================================================================
{
	std::cout << "==============================================\n";
	std::cout << "當碰到機關 T 時，英雄可以獲得 10 點經驗值\n";
	std::cout << "當碰到天使 A 時，英雄可以恢復攻擊力 2 倍的生命值\n";
	std::cout << "當碰到鑰匙 K 時，可以撿起鑰匙並且去打開 D 門\n\n";

	std::cout << "英雄當前的攻擊力為 " << gHero.getAtk() << std::endl;
	std::cout << "攻擊成功時給予對手的傷害，為英雄的攻擊力乘上題目星數\n";
	std::cout << "\n怪物能力一覽:\n";
	std::cout << "史萊姆 L : 攻擊力 2 ， hp   2\n";
	std::cout << "蝙蝠　 B : 攻擊力 3 ， hp   4\n";
	std::cout << "殭屍　 Z : 攻擊力10 ， hp  30\n";
	std::cout << "骷髏　 E : 攻擊力20 ， hp  45\n";
	std::cout << "蜘蛛　 P : 攻擊力35 ， hp 600\n";
	std::cout << "==============================================\n";
	std::cout << "按任意鍵回到遊戲. . .";
	system("pause>nul");
	system("cls");
}

//******************************************************************
//
// * Update the board state
//==================================================================
void update(bool key[])
//==================================================================
{
	// 清除版面
	system("CLS");

	// 是否有input
	bool hasInput = false;
	try {
		if (key[ValidInput::EW]) {
			gHero.move(0, -1, itemVec);
			hasInput = true;
		}
		else if (key[ValidInput::ES]) {
			gHero.move(0, 1, itemVec);
			hasInput = true;
		}
		else if (key[ValidInput::EA]) {
			gHero.move(-1, 0, itemVec);
			hasInput = true;
		}
		else if (key[ValidInput::ED]) {
			gHero.move(1, 0, itemVec);
			hasInput = true;
		}
		else if (key[ValidInput::EHELP]) {
			drawHelpInfo();
			hasInput = true;
		}
		else {
			throw "invalid input\n";
		}
	}
	catch (const char* c) 
	{
		std::cout << c;
	}
	for (vector<Creature*>::iterator it = creatureVec.begin(); it != creatureVec.end();)
	{
		if ((*it)->getPos().x == gHero.getPos().x && (*it)->getPos().y == gHero.getPos().y)
		{
			draw();
			if ((*it)->getIcon() != "Ａ")
			{
				if (guide)
				{
					gb.Guide(gHero, **it);
					guide = false;
				}
				else gb.Battle(gHero, **it);
			}
			else 
			{
				system("cls");
			}
		}
		(*it)->update(gHero.getPos());
		if ((*it)->getHealth() <= 0)
		{
			it = creatureVec.erase(it);
		}
		else it++;
	}
	for (vector<Item*>::iterator it = itemVec.begin(); it != itemVec.end();)
	{
		(*it)->update(gHero);
		if ((*it)->pick())
		{
			it = itemVec.erase(it);
		}
		else it++;
	}
	for (int i = 0; i < stairVec.size(); i++) 
	{
		stairVec[i]->update(gHero);
		if (stairVec[i]->isTrans()) 
		{
			setupMap(stairVec[i]->getNext());
			break;
		}
	}
	draw();
	drawInfo();
}