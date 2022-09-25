#pragma once
#include <string>

class Board {
private:
    std::string gBoard[8][8];
public:
    Board();

    //取得gBoard在[x][y]的內容
    std::string getBoardElement(int x, int y);
    //設定gBoard在[x][y]的內容
    void setBoardElement(std::string e, int x, int y);
};