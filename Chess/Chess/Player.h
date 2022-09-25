#pragma once
#include <vector>
#include <iostream>
#include "chess.h"
#include "Viewer.h"
#include "Board.h"
using std::vector;

class Player
{
protected:
    vector<ChessClass*> pChess;
    bool moved = false;
    bool checked = false;
public:
    Player() {};
    Player(char color) {};
    virtual void OnMove(Board& board/*, Position& outFromPos*/, Viewer& v, int x, int y, Player& p, int op) = 0; // ��ܭn�q fromPos ���� toPos
    virtual void OnMove2(Board& board/*, Position& outFromPos*/, Viewer& v, int nowX, int nowY, int lastX, int lastY, Player& p, int op) = 0; // ��ܭn�q fromPos ���� toPos
    virtual void OnPromote(Board& board, Position& pawnPos/*, PieceType& outType*/, int whichUP) = 0; // ��ܤɶ�����

    //���o��e���a�O�_���ʹL�F
    bool getMoved();

    //���m���ʪ��p
    void resetMoved();

    //�R��pChess����i�ӴѤl
    void eatChess(int i);

    //���opChess����i�ӴѤl����m
    Position istChessPos(int i);

    //���o��i�ӴѤl
    void istChessWay(int i, Viewer& v);

    //���opChess����
    int pChessSize();

    //�ݬݦ��S���N��⪺�x
    void check(int op, Player& p, Viewer& v);

    //�ݬݦۤv���S���Q�N�x
    bool isChecked();

    //�ˬd�ۤv�O�_�i�H�J��
    void castling(Player& p, Viewer& v, int curr);
};

class HumanPlayer : public Player
{
public:
    HumanPlayer();
    HumanPlayer(char color);
    void OnMove(Board& board, Viewer& v, int x, int y, Player& p, int op);
    void OnMove2(Board& board, Viewer& v, int nowX, int nowY, int lastX, int lastY, Player& p, int op);
    void OnPromote(Board& board, Position& pawnPos, int whichUP);
};

//class AIPlayer : public Player
//{
//public:
//    AIPlayer();
//    void OnMove(Board& board, Position& outFromPos, Position& outToPos);
//    void OnPromote(Board& board, Position& pawnPos);
//};
