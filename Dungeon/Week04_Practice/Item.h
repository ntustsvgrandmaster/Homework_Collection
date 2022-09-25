#pragma once
#include "Position.h"
class Item;
#include"Hero.h"
class Item
{
protected:
	Position sPos;
	std::string sIcon;
	bool picked = false;
public:
	Item()
	{
		this->sPos.x = 1;
		this->sPos.y = 1;
		this->sIcon = 'Ｉ';
	}
	// Set position
	void setPos(Position pos) { this->sPos = pos; }
	void setPos(int x, int y) {
		this->sPos.x = x;
		this->sPos.y = y;
	}

	// Set icon
	void setIcon(char& icon) { this->sIcon = icon; }
	// Get position
	Position getPos(void) { return this->sPos; }
	// Get Icon
	std::string getIcon(void) { return this->sIcon; }
	// 檢查有沒有被觸發過了
	bool pick(void) { return this->picked; }

	virtual void update(Hero& h) {}
	//給door用的
	virtual void open() {}
	virtual int getValue() { return 0; }
	virtual bool getOpen() { return false; }
};