#pragma once

#include "Position.h"
#include "Viewer.h"

//思考一下要讓chess可以改變viewer的樣子的話應該要怎麼做
//friend?
//回傳一個8*8的版面，然後再upload到viewer去?
//傳入viewer? <-這個感覺不錯

bool isPositionValid(Position p);

class ChessClass
{
protected:
    Position pos;
    //小兵、城堡、國王會用到
    bool moved = false;
    //國王會用到
    bool shortCastling = false;
    bool longCastling = false;
public:
    ChessClass();
    ChessClass(int x, int y);
    //根據不同棋子不同規則，來顯示出該棋子可以走的路徑
    virtual void getWay(Viewer& v) = 0;
    Position getPos();
    bool getMoved();
    void setShort(bool);
    void setLong(bool);
    void chessMoved();
    void setPos(int x, int y);
    void setPos(Position pos);
};

//國王
class King : public ChessClass
{
public:
    King(char color);
    void getWay(Viewer& v);
};

//皇后
class Queen : public ChessClass
{
public:
    Queen(char color);
    Queen(Position p);
    void getWay(Viewer& v);
};

//城堡
class Rook : public ChessClass
{
public:
    Rook(char color, int num);
    Rook(Position p);
    void getWay(Viewer& v);
};

//主教
class Bishop : public ChessClass
{
public:
    Bishop(char color, int num);
    Bishop(Position p);
    void getWay(Viewer& v);
};

//騎士
class Knight : public ChessClass
{
public:
    Knight(char color, int num);
    Knight(Position p);
    void getWay(Viewer& v);
};

//小兵
class Pawn : public ChessClass
{
private:
    char color;
public:
    Pawn(char color, int num);
    void getWay(Viewer& v);
};