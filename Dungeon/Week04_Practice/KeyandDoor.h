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
		this->sIcon = "��";
	};
	Door(Position p)
	{
		this->sPos.x = p.x;
		this->sPos.y = p.y;
		this->sKeyValue = 0;
		this->sIcon = "��";
	};

	Door(int i)
	{
		this->sPos.x = 1;
		this->sPos.y = 1;
		this->sKeyValue = i;
		this->sIcon = "��";
	};

	Door(int x, int y, int i)
	{
		this->sPos.x = x;
		this->sPos.y = y;
		this->sKeyValue = i;
		this->sIcon = "��";
	};

	//�]�w���
	void setValue(int v) { this->sKeyValue = v; }
	//�}��
	void open() { this->opened = true; }
	//���o���
	int getValue() { return sKeyValue; }
	//�d�ݬO�_�w�}��
	bool getOpen() { return opened; }


	void update(Hero& h)
	{
		if (this->sPos.x == h.getPos().x && this->sPos.y == h.getPos().y) {
			this->sIcon = "�@";
			this->open();
			h.useKey();
		}
	}
};

class Key : public Item
{
private:
	int sKeyIndex;		//�}���Ӫ����_��
public:
	//default constructor
	Key(void) {
		this->sPos.x = 1;
		this->sPos.y = 1;
		this->sKeyIndex = 0;
		this->sIcon = "��";
	};
	Key(Position p) {
		this->sPos.x = p.x;
		this->sPos.y = p.y;
		this->sKeyIndex = 0;
		this->sIcon = "��";
	};
	// Setting constructor
	Key(int x, int y, int index, std::string icon = "��") {
		this->sPos.x = x;
		this->sPos.y = y;
		this->sKeyIndex = index;
		this->sIcon = icon;
	};

	// Setting constructor
	Key(Position& pos, int index, std::string icon = "��") {
		this->sPos = pos;
		this->sKeyIndex = index;
		this->sIcon = icon;
	};

	// get the keyIndex
	int getKeyIndex() { return this->sKeyIndex; }

	// Set the keyIndex
	void SetAmount(int index) { this->sKeyIndex = index; }

	//hero�����_��
	void key(Hero& h) {
		h.SetKeyBox(this->sKeyIndex);
	}

	//�P�_hero�O���O�b�o���_�ͪ���m
	void update(Hero& h) {
		if (this->sPos.x == h.getPos().x && this->sPos.y == h.getPos().y && !picked) {
			this->key(h);
			this->sIcon = "�@";
			this->picked = true;
			std::cout << "key " << sKeyIndex << " picked up\n";
		}
	}
};
