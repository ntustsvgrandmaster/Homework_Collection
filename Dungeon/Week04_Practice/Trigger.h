#pragma once
#include <string>
#include <iostream>
#include "Item.h"


//************************************************************
// Trigger Class
//************************************************************
class Trigger : public Item {
private:
	int   sExpAmount;  // Set up the amount gain

public:
	// Default constructor
	Trigger(void) {
		this->sPos.x = 6;
		this->sPos.y = 7;
		this->sExpAmount = 10;
		this->sIcon = "вт";
	};
	Trigger(Position p) {
		this->sPos.x = p.x;
		this->sPos.y = p.y;
		this->sExpAmount = 10;
		this->sIcon = "вт";
	};

	// Setting constructor
	Trigger(int x, int y, int amt, std::string icon = "вт") {
		this->sPos.x = x;
		this->sPos.y = y;
		this->sExpAmount = amt;
		this->sIcon = icon;
	};

	// Setting constructor
	Trigger(Position& pos, int amt, std::string icon = "вт") {
		this->sPos = pos;
		this->sExpAmount = amt;
		this->sIcon = icon;
	};

	// Set the amount
	void SetAmount(int amt) { this->sExpAmount = amt; }

	// Get the amount 
	int getExpAmount(void) { return this->sExpAmount; }

	void trigger(Hero& h) {
		h.gainEXP(sExpAmount);
	}

	void update(Hero& h) {
		if (this->sPos.x == h.getPos().x && this->sPos.y == h.getPos().y && !picked) {
			this->trigger(h);
			picked = true;
		}
	}
};