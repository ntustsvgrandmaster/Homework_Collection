#include "pch.h"
#include "Viewer.h"


////設定顯示出的旗子顏色
//void SetColor(int color)
//{
//    HANDLE hConsole;
//    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleTextAttribute(hConsole, color);
//}

void Viewer::printViewer()
{
    //cout << "  ";
    //for (int i = 0; i < 8; i++)
    //{
    //    cout << char(i + 'a') << " ";
    //}
    //cout << endl;

    //for (int i = 0; i < 8; i++)
    //{
    //    cout << 8 - i << " ";
    //    for (int j = 0; j < 8; j++)
    //    {
    //        if (vBoard[i][j] == "SPACE")
    //        {
    //            //如果是移動路徑上就設定為黃色
    //            if (isWay[i][j])
    //            {
    //               /* SetColor(224);*/
    //            }
    //            cout << ' ';
    //            /*SetColor();*/
    //        }
    //        else
    //        {
    //            //看是甚麼顏色，就顯示甚麼顏色
    //            if (vBoard[i][j][0] == 'W')
    //            {
    //              /*  SetColor(7);*/
    //            }
    //            else if (vBoard[i][j][0] == 'B')
    //            {
    //               /* SetColor(240);*/
    //            }

    //            //如果是移動路徑上就設定為黃色
    //            if (isWay[i][j])
    //            {
    //                /*SetColor(224);*/
    //            }

    //            if (vBoard[i][j].substr(1) == "King")
    //            {
    //                cout << 'K';
    //            }
    //            else if (vBoard[i][j].substr(1) == "Queen")
    //            {
    //                cout << 'Q';
    //            }
    //            else if (vBoard[i][j].substr(1) == "Bishop")
    //            {
    //                cout << 'B';
    //            }
    //            else if (vBoard[i][j].substr(1) == "Rook")
    //            {
    //                cout << 'R';
    //            }
    //            else if (vBoard[i][j].substr(1) == "Knight")
    //            {
    //                cout << 'K';
    //            }
    //            else if (vBoard[i][j].substr(1) == "Pawn")
    //            {
    //                cout << 'P';
    //            }
    //        }

    //        //改回原本的顏色
    //       /* SetColor();*/
    //        cout << ' ';
    //    }
    //    cout << ' ' << 8 - i << endl;
    //}

    //cout << "  ";
    //for (int i = 0; i < 8; i++)
    //{
    //    cout << char(i + 'a') << " ";
    //}
    //cout << endl;
}

void Viewer::setViewer(Board& bd)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            vBoard[i][j] = bd.getBoardElement(i, j);
        }
    }
}

void Viewer::setVBoard(std::string e, int x, int y)
{
    vBoard[x][y] = e;
}

std::string Viewer::getVBoard(int x, int y)
{
    return vBoard[x][y];
}

void Viewer::resetWay()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            isWay[i][j] = 0;
        }
    }
}

int Viewer::getWay(int x, int y)
{
    return isWay[x][y];
}

void Viewer::setWay(int w, int x, int y)
{
    isWay[x][y] = w;
}