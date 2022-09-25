/************************************************************************
File:        source.cpp

Author:
		���s�Aea5878158@gmail.com
Modifier:
		�௧�N�Acheeryuchi@gmail.com
		���Y���Awindyhuang6@gmail.com
		���T�t�AJYCReports@gmail.com
Comment:
		�򥻿�J��V���ʥ\��Aw s a d ���ʸ}��W�U���k�A�ťէ��ܸ}�⯸�ߤ��a�O�r���A��T�W�i�H�W�[�g��
		ESC�O���}�e���C�P�ɧ�s�Ϫ��W����T�C

************************************************************************/

#include "main.h"
#include "Hero.h"
#include "Creature.h"
#include "KeyandDoor.h"
#include "Trigger.h"
#include "GameBoard.h"
Hero	 gHero(2, 2);

// Constent value
std::string GWALL = "��";
std::string GNOTHING = "�@";
std::string GDOOR = "��";

int GWIDTH;
int GHEIGHT;
const double gTimeLog = 0.033;

// Distance
const int gDistance = 4;

// �C���������
std::string** gBoard;

// �ݬݬO���O�bguide�Ҧ�
bool guide = false;

//��boss�O�_�Q����
bool boss_dead = false;

// �w�q���ؿ�J���O�P�����}�Cindex
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
// ������J���A
void keyUpdate(bool key[]);
// �P�_��m�O�_����
bool isPositionValid(Position& loc);
// �P�_��m�O�_����
bool isDoor(Position& loc);
//�]�w������m
void setupDoor(int x, int y);
// ��l�ƪ���
void setupBoard();
// ��X����
void draw(void);
// ��X������T
void drawInfo(void);
// �]�w�a�ϸ�T
void setupMap(std::string dataName);

// �{���D�X�ʨ禡
void update(bool key[]);

Trigger  gTrigger(5, 5, 10);
Trigger  gTrigger1;
GameBoard gb;

int main(int argc, char** argv)
{
	gb.printMenu();

	// �ΨӺ޲z��L��J���A���}�C
	bool gKeyState[7];

	// Ū�J�D�w
	gb.readQuiz();

	cout << "�O�_���L�s��о�?\n";
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
		cout << "�O�_���L�s��о�?\n";
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

	//�L�X�C���p����ƪ�����
	gb.getPoint(gHero);
	//
	system("pause>nul");
	return 0;
}

//******************************************************************
//
// * ������J���A
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
// * �P�_��m�O�_����
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
// * �P�_��m�O�_����
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
//�o��ӬO���F�B�zinclude windows.h�|�a�Ӫ����D
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
// ����
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
// * �Q�� call-by-referce �N�p��o�쪺��V�^��
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


		if (h.x == c.x && h.y == c.y && creatureVec[i]->getIcon() == "��")
		{
			gHero.damage(-gHero.getAtk() * 2);
			creatureVec[i]->getDamage(creatureVec[i]->getHealth());
		}
	}
	/************************************************************************/

	// Draw the board
	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			if (drawBoard[i][j] == "��") 
			{
				SetColor(47);
			}
			else if (drawBoard[i][j] == "��")
			{
				SetColor(11);
			}
			else if (drawBoard[i][j] == "��")
			{
				SetColor(8);
			}
			else if (drawBoard[i][j] == "��")
			{
				SetColor(2);
			}
			else if (drawBoard[i][j] == "��")
			{
				SetColor(6);
			}
			else if (drawBoard[i][j] == "��")
			{
				SetColor(12);
			}
			else if (drawBoard[i][j] == "��")
			{
				SetColor(79);
			}
			else if (drawBoard[i][j] == "��")
			{
				SetColor(111);
			}
			else if (drawBoard[i][j] == "��")
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
	//���M���쥻vector�̪��F��
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
	int amt, x, y; //Ū���ƶq�B�y�Х�
	char type;
	//�]�m�a�c
	fin >> amt;
	for (int i = 0; i < amt; i++) {
		fin >> x >> y;
		gBoard[x][y] = GWALL;
	}
	//�]�m�^��
	fin >> x >> y;
	gHero.setPos(y, x);
	//�]�mcreature
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
	//�]�mitem
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
	//�]�mstair
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
	std::cout << "�^���{�b���Ŭ� " << gHero.getLevel() << "\n";
	std::cout << "�^���{�b�� " << gHero.getExp() << " �g���" << "\n";
	std::cout << "�|�� " << gHero.getMaxExp() - gHero.getExp() << " �Ӵ��ɵ���\n";
	std::cout << "�^���ثe�ѤU " << gHero.getHealth() << " �ͩR��\n\n";
	std::cout << "�ϥ�aswd�Ӿޱ��^��\n";
	std::cout << "�ϥ� h �Ӷi�J��o���U\n";
	std::cout << "�ϥ�Esc�����}�C��\n";
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
	std::cout << "��I����� T �ɡA�^���i�H��o 10 �I�g���\n";
	std::cout << "��I��Ѩ� A �ɡA�^���i�H��_�����O 2 �����ͩR��\n";
	std::cout << "��I���_�� K �ɡA�i�H�߰_�_�ͨåB�h���} D ��\n\n";

	std::cout << "�^����e�������O�� " << gHero.getAtk() << std::endl;
	std::cout << "�������\�ɵ�����⪺�ˮ`�A���^���������O���W�D�جP��\n";
	std::cout << "\n�Ǫ���O�@��:\n";
	std::cout << "�v�ܩi L : �����O 2 �A hp   2\n";
	std::cout << "�����@ B : �����O 3 �A hp   4\n";
	std::cout << "�L�͡@ Z : �����O10 �A hp  30\n";
	std::cout << "�u�\�@ E : �����O20 �A hp  45\n";
	std::cout << "�j��@ P : �����O35 �A hp 600\n";
	std::cout << "==============================================\n";
	std::cout << "�����N��^��C��. . .";
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
	// �M������
	system("CLS");

	// �O�_��input
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
			if ((*it)->getIcon() != "��")
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