#pragma once
#include <string>
#include "Position.h"
class Hero;
#include"Item.h"
#include"main.h"
//************************************************************
// Hero Class, only has requirement part for example
//************************************************************

class Hero {

private:
	Position	sPos;			// Hero location
	std::string sIcon = "Ｈ";	// Hero icon
	int			sLevel = 1;     // Level
	int			sMaxExp;		// Level update experience
	int			sCurrentExp;	// current exp hero has
	int			health = 70;	// health of hero
	int			atk = 1;
	bool sKeyBox[1] = { 0 };

	int lvlTable[5][2]
	{
		{1, 70},
		{5, 100},
		{20, 200},
		{40, 150},
		{999,999}
	};

	int levelGate[4] = { 30, 30, 40, 50 };

public:
	// Default constructor
	Hero() {
		this->sPos.x = 0;
		this->sPos.y = 0;
		this->sLevel = 1;
		this->sCurrentExp = 0;
		this->sMaxExp = 30;
		//this->sIcon = 'H';
	};
	// Setting constructor
	Hero(int x, int y, int level = 1, int maxExp = 30, int currentExp = 0, char icon = 'H') {
		this->sPos.x = x;
		this->sPos.y = y;
		this->sLevel = level;
		this->sCurrentExp = currentExp;
		this->sMaxExp = maxExp;
		//this->sIcon = icon;
	};

	// Setting constructor
	Hero(Position& pos, int level = 1, int maxExp = 30, int currentExp = 0, char icon = 'H') {
		this->sPos = pos;
		this->sLevel = level;
		this->sCurrentExp = currentExp;
		this->sMaxExp = maxExp;
		//this->sIcon = icon;
	};

	// Set position
	void setPos(Position pos) { this->sPos = pos; }
	void setPos(int x, int y) {
		this->sPos.x = x;
		this->sPos.y = y;
	}

	// Set icon
	void setIcon(char& icon) { this->sIcon = icon; }

	// Set level
	void setLevel(int level) { this->sLevel = level; }

	// Set exp
	void setExp(int exp) { this->sCurrentExp = exp; }

	// Set MaxExp
	void SetMaxExp(int maxexp) { this->sMaxExp = maxexp; }

	// Set keyBox
	void SetKeyBox(int keyIndex) { this->sKeyBox[keyIndex] = true; }

	// Use key
	void useKey() { this->sKeyBox[0] = false; }

	//get keyBox
	bool getKeyBox(int keyIndex) { return this->sKeyBox[keyIndex]; }

	// Get position
	Position getPos(void) { return this->sPos; }

	// Get Icon
	std::string getIcon(void) { return this->sIcon; }

	// Get level
	int getLevel(void) { return this->sLevel; }

	// Get Exp
	int getExp(void) { return this->sCurrentExp; }

	// Get Max
	int getMaxExp(void) { return this->sMaxExp; }
	// Get Health
	int getHealth(void) { return this->health; }

	// Get Attack
	int getAtk(void) { return this->atk; }

	// Incrementally move the elements 
	void move(int x, int y, std::vector<Item*> itV) {
		// Compute the next position
		Position next;
		next.x = this->sPos.x + x;
		next.y = this->sPos.y + y;
		try {

			if (isPositionValid(next))
				if (isDoor(next))
				{
					//去itV裡面尋找door
					int i;
					for (i = 0; i < itV.size(); i++)
					{
						if (next.x == itV[i]->getPos().x && next.y == itV[i]->getPos().y) break;
					}

					//如果門還沒開的話就檢查有沒有鑰匙能打開
					if (!itV[i]->getOpen())
					{
						int doorV = itV[i]->getValue();
						if (sKeyBox[doorV])
						{
							itV[i]->open();
							std::cout << "door open!\n";
							this->sPos = next;
						}
						else
						{
							throw "door can't open\n";
						}
					}
					else
					{
						this->sPos = next;
					}
				}
				else
				{
					this->sPos = next;
				}
			else {
				throw "Invalid location\n";
			}
		}
		catch (const char* c) 
		{
			std::cout << c;
		}
	}

	// Calculate Gain of EXP
	void gainEXP(int points) {
		int number = points;
		while (number > 0) {
			if (sCurrentExp + number >= sMaxExp) {//level up
				number -= (sMaxExp - sCurrentExp);
				sCurrentExp = 0;
				sMaxExp = levelGate[sLevel];
				health += lvlTable[sLevel][1];
				atk = lvlTable[sLevel][0];
;				sLevel++;
			}
			else {
				sCurrentExp += number;
				number = 0;
			}
		}
	}

	void damage(int points) {
		// Implement Damage done to Hero
		/*Please implement your code here*/
		this->health -= points;
		/************************************************************************/
	}
};
