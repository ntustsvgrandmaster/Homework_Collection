#pragma once
#include"Item.h"

class Door : public Item
{
private:
	int sKeyValue;
	bool opened = false;
public:
	Door(void)
	{
		this->sPos.x = 1;
		this->sPos.y = 1;
		this->sKeyValue = 0;
		this->sIcon = "Ｄ";
	};
	Door(Position p)
	{
		this->sPos.x = p.x;
		this->sPos.y = p.y;
		this->sKeyValue = 0;
		this->sIcon = "Ｄ";
	};

	Door(int i)
	{
		this->sPos.x = 1;
		this->sPos.y = 1;
		this->sKeyValue = i;
		this->sIcon = "Ｄ";
	};

	Door(int x, int y, int i)
	{
		this->sPos.x = x;
		this->sPos.y = y;
		this->sKeyValue = i;
		this->sIcon = "Ｄ";
	};

	//設定鍵值
	void setValue(int v) { this->sKeyValue = v; }
	//開門
	void open() { this->opened = true; }
	//取得鍵值
	int getValue() { return sKeyValue; }
	//查看是否已開門
	bool getOpen() { return opened; }


	void update(Hero& h)
	{
		if (this->sPos.x == h.getPos().x && this->sPos.y == h.getPos().y) {
			this->sIcon = "　";
			this->open();
			h.useKey();
		}
	}
};

class Key : public Item
{
private:
	int sKeyIndex;		//開哪個門的鑰匙
public:
	//default constructor
	Key(void) {
		this->sPos.x = 1;
		this->sPos.y = 1;
		this->sKeyIndex = 0;
		this->sIcon = "Ｋ";
	};
	Key(Position p) {
		this->sPos.x = p.x;
		this->sPos.y = p.y;
		this->sKeyIndex = 0;
		this->sIcon = "Ｋ";
	};
	// Setting constructor
	Key(int x, int y, int index, std::string icon = "Ｋ") {
		this->sPos.x = x;
		this->sPos.y = y;
		this->sKeyIndex = index;
		this->sIcon = icon;
	};

	// Setting constructor
	Key(Position& pos, int index, std::string icon = "Ｋ") {
		this->sPos = pos;
		this->sKeyIndex = index;
		this->sIcon = icon;
	};

	// get the keyIndex
	int getKeyIndex() { return this->sKeyIndex; }

	// Set the keyIndex
	void SetAmount(int index) { this->sKeyIndex = index; }

	//hero拿到鑰匙
	void key(Hero& h) {
		h.SetKeyBox(this->sKeyIndex);
	}

	//判斷hero是不是在這個鑰匙的位置
	void update(Hero& h) {
		if (this->sPos.x == h.getPos().x && this->sPos.y == h.getPos().y && !picked) {
			this->key(h);
			this->sIcon = "　";
			this->picked = true;
			std::cout << "key " << sKeyIndex << " picked up\n";
		}
	}
};
