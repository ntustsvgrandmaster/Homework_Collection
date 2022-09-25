#pragma once

#include "Position.h"
#include "Viewer.h"

//��Ҥ@�U�n��chess�i�H����viewer���ˤl�������ӭn���
//friend?
//�^�Ǥ@��8*8�������A�M��Aupload��viewer�h?
//�ǤJviewer? <-�o�ӷPı����

bool isPositionValid(Position p);

class ChessClass
{
protected:
    Position pos;
    //�p�L�B�����B����|�Ψ�
    bool moved = false;
    //����|�Ψ�
    bool shortCastling = false;
    bool longCastling = false;
public:
    ChessClass();
    ChessClass(int x, int y);
    //�ھڤ��P�Ѥl���P�W�h�A����ܥX�ӴѤl�i�H�������|
    virtual void getWay(Viewer& v) = 0;
    Position getPos();
    bool getMoved();
    void setShort(bool);
    void setLong(bool);
    void chessMoved();
    void setPos(int x, int y);
    void setPos(Position pos);
};

//���
class King : public ChessClass
{
public:
    King(char color);
    void getWay(Viewer& v);
};

//�ӦZ
class Queen : public ChessClass
{
public:
    Queen(char color);
    Queen(Position p);
    void getWay(Viewer& v);
};

//����
class Rook : public ChessClass
{
public:
    Rook(char color, int num);
    Rook(Position p);
    void getWay(Viewer& v);
};

//�D��
class Bishop : public ChessClass
{
public:
    Bishop(char color, int num);
    Bishop(Position p);
    void getWay(Viewer& v);
};

//�M�h
class Knight : public ChessClass
{
public:
    Knight(char color, int num);
    Knight(Position p);
    void getWay(Viewer& v);
};

//�p�L
class Pawn : public ChessClass
{
private:
    char color;
public:
    Pawn(char color, int num);
    void getWay(Viewer& v);
};