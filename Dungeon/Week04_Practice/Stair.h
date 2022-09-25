#pragma once
#include <string>
#include "Hero.h"

class Stair {
private:
	std::string nextFloor;
	Position sPos;
	std::string sIcon;
	bool trans = false; //可不可以傳送了
public:
	Stair()
	{
		this->sPos.x = 1;
		this->sPos.y = 1;
		this->sIcon = "Ｓ";
		nextFloor = "./maps/map1.txt";
	}
	Stair(Position p, std::string des) 
	{
		this->sPos.x = p.x;
		this->sPos.y = p.y;
		this->sIcon = "Ｓ";
		nextFloor = des;
	}

	std::string getIcon() { return this->sIcon; }
	bool isTrans() { return this->trans; }
	std::string getNext() { return this->nextFloor; }
	Position getPos() { return this->sPos; }
	void update(Hero& h) 
	{
		if (this->sPos.x == h.getPos().x && this->sPos.y == h.getPos().y) 
		{
			this->trans = true;
		}
	}
};