#include "BoardManager.h"

int main()
{
    BoardManager bm;
    bool Exit = false;
    while (!Exit)
    {
        while (!bm.isMoved())
        {
            bm.printContent();
        }
        bm.setMoved(false);
    }
}
