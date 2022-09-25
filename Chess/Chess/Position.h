#pragma once
struct Position {
    Position() {
        x = 0;
        y = 0;
    }

    Position(int _x, int _y) {
        x = _x;
        y = _y;
    }

    int x;
    int y;
};