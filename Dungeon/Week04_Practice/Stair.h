#pragma once
#include <string>
#include "Hero.h"

class Stair {
private:
	std::string nextFloor;
	Position sPos;
	std::string sIcon;
	bool trans = false; //�i���i�H�ǰe�F
public:
	Stair()
	{
		this->sPos.x = 1;
		this->sPos.y = 1;
		this->sIcon = "��";
		nextFloor = "./maps/map1.txt";
	}
	Stair(Position p, std::string des) 
	{
		this->sPos.x = p.x;
		this->sPos.y = p.y;
		this->sIcon = "��";
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