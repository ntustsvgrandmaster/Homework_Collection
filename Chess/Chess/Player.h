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
    virtual void OnMove(Board& board/*, Position& outFromPos*/, Viewer& v, int x, int y, Player& p, int op) = 0; // 選擇要從 fromPos 走到 toPos
    virtual void OnMove2(Board& board/*, Position& outFromPos*/, Viewer& v, int nowX, int nowY, int lastX, int lastY, Player& p, int op) = 0; // 選擇要從 fromPos 走到 toPos
    virtual void OnPromote(Board& board, Position& pawnPos/*, PieceType& outType*/, int whichUP) = 0; // 選擇升階類型

    //取得當前玩家是否移動過了
    bool getMoved();

    //重置移動狀況
    void resetMoved();

    //刪除pChess中第i個棋子
    void eatChess(int i);

    //取得pChess中第i個棋子的位置
    Position istChessPos(int i);

    //取得第i個棋子
    void istChessWay(int i, Viewer& v);

    //取得pChess長度
    int pChessSize();

    //看看有沒有將對手的軍
    void check(int op, Player& p, Viewer& v);

    //看看自己有沒有被將軍
    bool isChecked();

    //檢查自己是否可以入堡
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
