#pragma once
#include <iostream>
//#include <windows.h>					//�|�Ĭ�A�i�R��
#include "Board.h"
using std::cout;
using std::endl;

class Viewer
{
private:
	std::string vBoard[8][8];
	//�Ψӫ��ܬO���O�i�H������
	int isWay[8][8] = { 0 };
public:
	Viewer() { ; }
	//�L�XViewer������
	void printViewer();
	//�]�wViewer������
	void setViewer(Board& bd);
	//�]�wvBoard[x][y]
	void setVBoard(std::string e, int x, int y);
	//��isWay���s�]�w����0
	void resetWay();
	//�]�wisWay[x][y]
	void setWay(int w, int x, int y);
	//���oisWay[x][y]
	int getWay(int x, int y);
	//���ovBoard[x][y]
	std::string getVBoard(int x, int y);
};

//void SetColor(int color = 7);