#pragma once
#include<string>
#include "Position.h"
#include "Player.h"
#include "Board.h"
#include "Viewer.h"

class GameManager
{
private:
    Player* players[2];
    //白 = 0，黑 = 1
    int currentPlayer;
    Board board;
    Viewer viewer;
public:
    GameManager();
    GameManager(std::string type);

    //換人
    void changePlayer();

    //吃子
    void eat();

    //取得currentPlayer
    int getCurrnet();

    //檢查遊戲結束了沒
    void checkMate(bool& gameOver);

    Player* getPlayer();
    Player* getOpponent();
    Board* getBoard();
    Viewer* getViewer();
};

GameManager::GameManager()
{
    players[0] = new HumanPlayer('W');
    players[1] = new HumanPlayer('B');
    currentPlayer = 0;
}

GameManager::GameManager(std::string type)
{
    if (type == "human")
    {
        players[0] = new HumanPlayer('W');
        players[1] = new HumanPlayer('B');
        currentPlayer = 0;
    }
    else //type == "CPU"
    {
        players[0] = new HumanPlayer;
        players[1] = new HumanPlayer;
        currentPlayer = 0;
        //players[0] = new HumanPlayer;
        //players[1] = new AIPlayer;
        //currentPlayer = 0;
    }
}

void GameManager::changePlayer()
{
    currentPlayer = currentPlayer ^ 1;
}

Player* GameManager::getPlayer()
{
    return players[currentPlayer];
}

Player* GameManager::getOpponent()
{
    return players[currentPlayer ^ 1];
}


Board* GameManager::getBoard() {
    return &this->board;
}

Viewer* GameManager::getViewer()
{
    return &this->viewer;
}

void GameManager::eat()
{
    //當前player的旗子位置上若有對方的旗子，就把旗子給吃掉。
    int size = players[currentPlayer]->pChessSize();

    //player == 0 -> 是白(W)
    if (currentPlayer == 0)
    {
        //檢查完所有棋子，或是已經有棋子被吃了就跳出
        for (int i = 0; i < size; i++)
        {
            Position cPos = players[currentPlayer]->istChessPos(i);
            if (board.getBoardElement(cPos.y, cPos.x)[0] == 'B')
            {
                players[currentPlayer]->eatChess(i);
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            Position cPos = players[currentPlayer]->istChessPos(i);
            if (board.getBoardElement(cPos.y, cPos.x)[0] == 'W')
            {
                players[currentPlayer]->eatChess(i);
                break;
            }
        }
    }
}

int GameManager::getCurrnet()
{
    return this->currentPlayer;
}



int eight_Dir[8][2] =
{
    {1, 0},
    {1, -1},
    {0, -1},
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1}
};
void GameManager::checkMate(bool& gameOver)
{
    if (players[currentPlayer]->isChecked()) {
        /*****第一種情況 : 國王移動*****/
        //找到國王
        Position kingPos;
        if (currentPlayer == 0)
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (viewer.getVBoard(j, i) == "WKing")
                    {
                        kingPos.x = i;
                        kingPos.y = j;
                    }
                }
            }
        }
        else
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (viewer.getVBoard(j, i) == "BKing")
                    {
                        kingPos.x = i;
                        kingPos.y = j;
                    }
                }
            }
        }

        //對手的棋子數
        int size = players[currentPlayer ^ 1]->pChessSize();

        //尋找國王可以走的路徑
        players[currentPlayer]->istChessWay(0, viewer);
        int my_size = players[currentPlayer]->pChessSize();
        for (int i = 0; i < my_size; i++)
        {
            viewer.setWay(0, players[currentPlayer]->istChessPos(i).y, players[currentPlayer]->istChessPos(i).x);
        }
        int kingWay[8][8] = { 0 };
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                kingWay[i][j] = viewer.getWay(i, j);
            }
        }
        viewer.resetWay();
        //看看國王有沒有辦法透過自己的移動避開將死
        for (int i = 0; i < 8; i++)
        {
            std::string chessName = board.getBoardElement(kingPos.y, kingPos.x);
            Position next(kingPos.x + eight_Dir[i][0], kingPos.y + eight_Dir[i][1]);

            for (int j = 0; j < size; j++)
            {
                if (players[currentPlayer ^ 1]->istChessPos(j).x == next.x &&
                    players[currentPlayer ^ 1]->istChessPos(j).y == next.y)
                {
                    continue;
                }
                players[currentPlayer ^ 1]->istChessWay(i, viewer);
            }

            //下一個位置是合法的且不是自己的棋
            if (isPositionValid(next) && kingWay[next.y][next.x] == 1)
            {
                std::string nextName = board.getBoardElement(next.y, next.x);
                board.setBoardElement(nextName, kingPos.y, kingPos.x);
                board.setBoardElement(chessName, next.y, next.x);
                viewer.setViewer(board);

                //國王有路可逃
                if (viewer.getWay(next.y, next.x) != 1)
                {
                    board.setBoardElement(chessName, kingPos.y, kingPos.x);
                    board.setBoardElement(nextName, next.y, next.x);
                    viewer.resetWay();
                    return;
                }
                else
                {
                    board.setBoardElement(chessName, kingPos.y, kingPos.x);
                    board.setBoardElement(nextName, next.y, next.x);
                }
            }
        }
        viewer.resetWay();
        /***********************************/

        /*第二、三種情況 : 吃掉威脅 / 擋住威脅*/
        int mySize = players[currentPlayer]->pChessSize();
        //尋訪自己所有的棋子(不包含king)，並且去走所有可能的路徑。
        for (int i = 1; i < mySize; i++)
        {
            players[currentPlayer]->istChessWay(i, viewer);
            for (int j = 0; j < mySize; j++)
            {
                Position isMyChess = players[currentPlayer]->istChessPos(j);
                viewer.setWay(0, isMyChess.y, isMyChess.x);
            }
            int thisChessWay[8][8] = { 0 };
            for (int j = 0; j < 8; j++)
            {
                for (int k = 0; k < 8; k++)
                {
                    thisChessWay[j][k] = viewer.getWay(j, k);
                }
            }

            viewer.resetWay();

            Position nowPos = players[currentPlayer]->istChessPos(i);
            std::string chessName = board.getBoardElement(nowPos.y, nowPos.x);
            for (int j = 0; j < 8; j++)
            {
                for (int k = 0; k < 8; k++)
                {
                    Position next(j, k);
                    //這邊可以移動，就移動看看
                    if (thisChessWay[next.y][next.x] == 1)
                    {
                        std::string cName = board.getBoardElement(next.y, next.x);
                        board.setBoardElement(cName, nowPos.y, nowPos.x);
                        board.setBoardElement(chessName, next.y, next.x);
                        viewer.setViewer(board);

                        for (int z = 0; z < size; z++)
                        {
                            //跳過被吃掉的棋子
                            if (players[currentPlayer ^ 1]->istChessPos(z).x == next.x &&
                                players[currentPlayer ^ 1]->istChessPos(z).y == next.y)
                            {
                                continue;
                            }
                            players[currentPlayer ^ 1]->istChessWay(z, viewer);
                        }
                        if (viewer.getWay(kingPos.y, kingPos.x) != 1)
                        {
                            board.setBoardElement(chessName, nowPos.y, nowPos.x);
                            board.setBoardElement(cName, next.y, next.x);
                            viewer.resetWay();
                            return;
                        }


                        board.setBoardElement(chessName, nowPos.y, nowPos.x);
                        board.setBoardElement(cName, next.y, next.x);
                        viewer.resetWay();
                    }
                }
            }
            viewer.resetWay();
        }
        /***********************************/
        viewer.setViewer(board);

        //以上三種情況都符合則將死
        gameOver = true;
    }
}