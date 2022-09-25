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
    //�� = 0�A�� = 1
    int currentPlayer;
    Board board;
    Viewer viewer;
public:
    GameManager();
    GameManager(std::string type);

    //���H
    void changePlayer();

    //�Y�l
    void eat();

    //���ocurrentPlayer
    int getCurrnet();

    //�ˬd�C�������F�S
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
    //��eplayer���X�l��m�W�Y����誺�X�l�A�N��X�l���Y���C
    int size = players[currentPlayer]->pChessSize();

    //player == 0 -> �O��(W)
    if (currentPlayer == 0)
    {
        //�ˬd���Ҧ��Ѥl�A�άO�w�g���Ѥl�Q�Y�F�N���X
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
        /*****�Ĥ@�ر��p : �������*****/
        //�����
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

        //��⪺�Ѥl��
        int size = players[currentPlayer ^ 1]->pChessSize();

        //�M�����i�H�������|
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
        //�ݬݰ�����S����k�z�L�ۤv�������׶}�N��
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

            //�U�@�Ӧ�m�O�X�k���B���O�ۤv����
            if (isPositionValid(next) && kingWay[next.y][next.x] == 1)
            {
                std::string nextName = board.getBoardElement(next.y, next.x);
                board.setBoardElement(nextName, kingPos.y, kingPos.x);
                board.setBoardElement(chessName, next.y, next.x);
                viewer.setViewer(board);

                //��������i�k
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

        /*�ĤG�B�T�ر��p : �Y���¯� / �צ�¯�*/
        int mySize = players[currentPlayer]->pChessSize();
        //�M�X�ۤv�Ҧ����Ѥl(���]�tking)�A�åB�h���Ҧ��i�઺���|�C
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
                    //�o��i�H���ʡA�N���ʬݬ�
                    if (thisChessWay[next.y][next.x] == 1)
                    {
                        std::string cName = board.getBoardElement(next.y, next.x);
                        board.setBoardElement(cName, nowPos.y, nowPos.x);
                        board.setBoardElement(chessName, next.y, next.x);
                        viewer.setViewer(board);

                        for (int z = 0; z < size; z++)
                        {
                            //���L�Q�Y�����Ѥl
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

        //�H�W�T�ر��p���ŦX�h�N��
        gameOver = true;
    }
}