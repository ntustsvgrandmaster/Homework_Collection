#pragma once
#include <string>

class Board {
private:
    std::string gBoard[8][8];
public:
    Board();

    //���ogBoard�b[x][y]�����e
    std::string getBoardElement(int x, int y);
    //�]�wgBoard�b[x][y]�����e
    void setBoardElement(std::string e, int x, int y);
};