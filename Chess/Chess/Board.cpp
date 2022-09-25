#include "pch.h"
#include "Board.h"

Board::Board() {
    for (int i = 0; i < 8; i++)
    {
        for (int j = 1; j < 7; j++)
        {
            gBoard[j][i] = "SPACE";
        }
    }

    for (int i = 0; i < 8; i++)
    {
        gBoard[1][i] = "BPawn";
        gBoard[6][i] = "WPawn";
    }
    gBoard[0][0] = "BRook";     gBoard[0][7] = "BRook";
    gBoard[0][1] = "BKnight";   gBoard[0][6] = "BKnight";
    gBoard[0][2] = "BBishop";   gBoard[0][5] = "BBishop";
    gBoard[0][3] = "BQueen";
    gBoard[0][4] = "BKing";

    gBoard[7][0] = "WRook";     gBoard[7][7] = "WRook";
    gBoard[7][1] = "WKnight";   gBoard[7][6] = "WKnight";
    gBoard[7][2] = "WBishop";   gBoard[7][5] = "WBishop";
    gBoard[7][3] = "WQueen";
    gBoard[7][4] = "WKing";
}

std::string Board::getBoardElement(int x, int y)
{
    return gBoard[x][y];
}

void Board::setBoardElement(std::string e, int x, int y)
{
    gBoard[x][y] = e;
}