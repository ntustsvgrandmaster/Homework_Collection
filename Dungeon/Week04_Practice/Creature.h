#pragma once
#include <string>
#include "Position.h"
#include "main.h"


class Creature;
class WaveAttack;
class Bat;
class Angle;
class Slime;

extern std::vector<Creature*> creatureVec;
extern bool boss_dead;

class Creature {//creature class 
protected:
	Position	sPos;			// Creature position
	std::string sIcon = "��";			// Creature icon
	int atk = 1;
	int hp = 1;
	int exp = 1;
public:
	// Default constructor
	Creature(void) {
		this->sPos.x = 1;
		this->sPos.y = 1;
		//this->sIcon = 'C';
	};
	Creature(Position p) {
		this->sPos.x = p.x;
		this->sPos.y = p.y;
		//this->sIcon = 'C';
	};

	// Set position
	void setPos(Position pos) { this->sPos = pos; }
	void setPos(int x, int y) {
		this->sPos.x = x;
		this->sPos.y = y;
	}

	// Set icon
	void setIcon(char& icon) { this->sIcon = icon; }

	// Get position
	Position getPos(void) { 
		return this->sPos; }

	// Get Icon
	std::string getIcon(void) { return this->sIcon; }

	int getAtk(void) { return this->atk; }

	void getDamage(int d) { this->hp -= d; }
	int getHealth() { return this->hp; }
	int getEXP() { return this->exp; }
	void etHealth(int s) { this->hp = s; }

public:
	virtual void update(Position hPos) {
		Position dir;
		if (canSee(this->sPos, hPos, dir)) {
			std::cout << "Creature has find the Hero in the ( " << dir.x << ", " << dir.y << " ) direction\n";
			this->sIcon = '!';
			int randNum = rand() % 4;
			if (randNum == 0)
			{
				Position test = sPos;
				test.x += dir.x;
				test.y += dir.y;
				if (isPositionValid(test))
				{
					this->sPos.x += dir.x;
					this->sPos.y += dir.y;
				}
			}
		}
		else {
			std::cout << "Creature didn't find the Hero\n";
			this->sIcon = 'C';
			int randNum = rand() % 4;
			if (randNum == 0)
			{
				Position test = sPos;
				test.x += 1;
				if (isPositionValid(test))
				{
					this->sPos.x += 1;
				}
				else
				{
					this->sPos.x -= 1;
				}
			}
			if (randNum == 1)
			{
				Position test = sPos;
				test.x -= 1;
				if (isPositionValid(test))
				{
					this->sPos.x -= 1;
				}
				else
				{
					this->sPos.x += 1;
				}
			}
			if (randNum == 2)
			{
				Position test = sPos;
				test.y += 1;
				if (isPositionValid(test))
				{
					this->sPos.y += 1;
				}
				else
				{
					this->sPos.y -= 1;
				}
			}
			if (randNum == 3)
			{
				Position test = sPos;
				test.y -= 1;
				if (isPositionValid(test))
				{
					this->sPos.y -= 1;
				}
				else
				{
					this->sPos.y += 1;
				}
			}
		}
	}
};

class WaveAttack : public Creature 
{
private:
	Position dir;
public:
	WaveAttack() {
		this->sIcon = "��";
		this->sPos.x = 1;
		this->sPos.y = 1;
		this->dir.x = 1;
		this->dir.y = 1;
		this->atk = 3;
	}
	WaveAttack(char _icon, Position wPos, Position _dir) 
	{
		this->sIcon = _icon;
		this->sPos.x = wPos.x;
		this->sPos.y = wPos.y;
		this->dir.x = _dir.x;
		this->dir.y = _dir.y;
		this->atk = 3;
	}

	void update(Position hPos) {
		if (isPositionValid(this->sPos)) {
			this->sPos.x += dir.x;
			this->sPos.y += dir.y;

			//��m���X�k(����)�N����(������ĦX)
			if (!isPositionValid(sPos))
			{
				this->sIcon = 'O';
			}
		}
	}
};


class Bat : public Creature
{
public:
	Bat(void)
	{
		this->sIcon = "��";
		this->sPos.x = 1;
		this->sPos.y = 1;
		this->atk = 3;
		this->hp = 4;
	}	
	Bat(Position p)
	{
		this->sIcon = "��";
		this->sPos.x = p.x;
		this->sPos.y = p.y;
		this->atk = 3;
		this->hp = 4;
	}
	//����update���
	void update(Position hPos) {
		//Position dir;
		//if (canSee(this->sPos, hPos, dir)) {
		//	std::cout << "Bat has find the Hero in the ( " << dir.x << ", " << dir.y << " ) direction\n";
		//	this->sIcon = '!';

		//	Position wPos;
		//	wPos.x = this->sPos.x + dir.x;
		//	wPos.y = this->sPos.y + dir.y;
		//	//�p�G�O�b���u�۹��m���ܴN�o�X���i����
		//	if (dir.x == 1 && dir.y == 0)
		//	{
		//		creatureVec.push_back(new WaveAttack('>', wPos, dir));
		//	}
		//	else if (dir.x == -1 && dir.y == 0)
		//	{
		//		creatureVec.push_back(new WaveAttack('<', wPos, dir));
		//	}
		//	else if (dir.x == 0 && dir.y == 1)
		//	{
		//		creatureVec.push_back(new WaveAttack('v', wPos, dir));
		//	}
		//	else if (dir.x == 0 && dir.y == -1)
		//	{
		//		creatureVec.push_back(new WaveAttack('^', wPos, dir));
		//	}
		//}
		////�S�ݨ�N�H������
		//else {
		//	std::cout << "Bat didn't find the Hero\n";
		//	this->sIcon = 'B';
		//	int randNum = rand() % 4;
		//	if (randNum == 0)
		//	{
		//		Position test = sPos;
		//		test.x += 1;
		//		if (isPositionValid(test))
		//		{
		//			this->sPos.x += 1;
		//		}
		//		else
		//		{
		//			this->sPos.x -= 1;
		//		}
		//	}
		//	if (randNum == 1)
		//	{
		//		Position test = sPos;
		//		test.x -= 1;
		//		if (isPositionValid(test))
		//		{
		//			this->sPos.x -= 1;
		//		}
		//		else
		//		{
		//			this->sPos.x += 1;
		//		}
		//	}
		//	if (randNum == 2)
		//	{
		//		Position test = sPos;
		//		test.y += 1;
		//		if (isPositionValid(test))
		//		{
		//			this->sPos.y += 1;
		//		}
		//		else
		//		{
		//			this->sPos.y -= 1;
		//		}
		//	}
		//	if (randNum == 3)
		//	{
		//		Position test = sPos;
		//		test.y -= 1;
		//		if (isPositionValid(test))
		//		{
		//			this->sPos.y -= 1;
		//		}
		//		else
		//		{
		//			this->sPos.y += 1;
		//		}
		//	}
		//}
	}
};

class Angle : public Creature
{
private:

public:
	// Default constructor
	Angle(void)
	{
		this->sPos.x = 1;
		this->sPos.y = 1;
		this->sIcon = "��";
		this->atk = -1;   //�ڬO��hero�ɦ媺���}�Ǫ���
	};	
	Angle(Position p)
	{
		this->sPos.x = p.x;
		this->sPos.y = p.y;
		this->sIcon = "��";
		this->atk = -1;   //�ڬO��hero�ɦ媺���}�Ǫ���
	};

	void update(Position hPos)
	{
		//int randNum = rand() % 4;
		//if (randNum == 0)
		//{
		//	Position test = sPos;
		//	test.x += 1;
		//	if (isPositionValid(test))
		//	{
		//		this->sPos.x += 1;
		//	}
		//	else
		//	{
		//		this->sPos.x -= 1;
		//	}
		//}
		//if (randNum == 1)
		//{
		//	Position test = sPos;
		//	test.x -= 1;
		//	if (isPositionValid(test))
		//	{
		//		this->sPos.x -= 1;
		//	}
		//	else
		//	{
		//		this->sPos.x += 1;
		//	}
		//}
		//if (randNum == 2)
		//{
		//	Position test = sPos;
		//	test.y += 1;
		//	if (isPositionValid(test))
		//	{
		//		this->sPos.y += 1;
		//	}
		//	else
		//	{
		//		this->sPos.y -= 1;
		//	}
		//}
		//if (randNum == 3)
		//{
		//	Position test = sPos;
		//	test.y -= 1;
		//	if (isPositionValid(test))
		//	{
		//		this->sPos.y -= 1;
		//	}
		//	else
		//	{
		//		this->sPos.y += 1;
		//	}
		//}
		//Position dir;
		//if (canSee(this->sPos, hPos, dir))
		//{
		//	std::cout << "the Hero entered in the sacred circle, so the Hero's health up!\n";
		//	this->sIcon = '@';
		//}
		//else
		//{
		//	this->sIcon = 'A';
		//}
	}
};

class Slime : public Creature 
{
public:
	Slime(Position p) 
	{
		this->sPos.x = p.x;
		this->sPos.y = p.y;
		this->sIcon = "��";
		this->atk = 2;
		this->hp = 2;
		this->exp = 5;
	}

	void update(Position hpos) 
	{
		;
	}
};

class Skeleton : public Creature
{
public:
	Skeleton(Position p)
	{
		this->sPos.x = p.x;
		this->sPos.y = p.y;
		this->sIcon = "��";
		this->atk = 20;
		this->hp = 45;
		this->exp = 5;
	}

	void update(Position hpos)
	{
		;
	}
};

class Zombie : public Creature
{
public:
	Zombie(Position p)
	{
		this->sPos.x = p.x;
		this->sPos.y = p.y;
		this->sIcon = "��";
		this->atk = 10;
		this->hp = 30;
		this->exp = 5;
	}

	void update(Position hpos)
	{
		;
	}
};

class Spider : public Creature
{
public:
	Spider(Position p)
	{
		this->sPos.x = p.x;
		this->sPos.y = p.y;
		this->sIcon = "��";
		this->atk = 35;
		this->hp = 600;
		this->exp = 5;
	}

	void update(Position hpos)
	{
		if (this->hp <= 0) boss_dead = true;
	}
};