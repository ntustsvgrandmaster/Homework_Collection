#pragma once
#include <iostream>
//#include <windows.h>					//會衝突，可刪嗎
#include "Board.h"
using std::cout;
using std::endl;

class Viewer
{
private:
	std::string vBoard[8][8];
	//用來指示是不是可以走的路
	int isWay[8][8] = { 0 };
public:
	Viewer() { ; }
	//印出Viewer的版面
	void printViewer();
	//設定Viewer的版面
	void setViewer(Board& bd);
	//設定vBoard[x][y]
	void setVBoard(std::string e, int x, int y);
	//把isWay重新設定全為0
	void resetWay();
	//設定isWay[x][y]
	void setWay(int w, int x, int y);
	//取得isWay[x][y]
	int getWay(int x, int y);
	//取得vBoard[x][y]
	std::string getVBoard(int x, int y);
};

//void SetColor(int color = 7);