#include "pch.h"
#include "chess.h"

bool isPositionValid(Position p)
{
	if (p.x >= 8 || p.x < 0 || p.y >= 8 || p.y < 0)
	{
		return false;
	}
	return true;
}

ChessClass::ChessClass()
{
	this->pos = Position(0, 0);
}

ChessClass::ChessClass(int x, int y)
{
	this->pos = Position(x, y);
}


void ChessClass::setPos(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
}
void ChessClass::setPos(Position _pos)
{
	this->pos.x = _pos.x;
	this->pos.y = _pos.y;
}

Position ChessClass::getPos()
{
	return this->pos;
}

void ChessClass::chessMoved()
{
	this->moved = true;
}

bool ChessClass::getMoved()
{
	return this->moved;
}

void ChessClass::setShort(bool c)
{
	this->shortCastling = c;
}

void ChessClass::setLong(bool c)
{
	this->longCastling = c;
}

King::King(char color)
{
	if (color == 'W')
	{
		this->pos = Position(4, 7);
	}
	else
	{
		this->pos = Position(4, 0);
	}
}

Queen::Queen(char color)
{
	if (color == 'W')
	{
		this->pos = Position(3, 7);
	}
	else
	{
		this->pos = Position(3, 0);
	}
}

Queen::Queen(Position p)
{
	this->pos.x = p.x;
	this->pos.y = p.y;
}

Rook::Rook(char color, int num)
{
	int rl;
	if (num == 0) rl = 0;
	else		  rl = 7;

	if (color == 'W')
	{
		this->pos = Position(rl, 7);
	}
	else
	{
		this->pos = Position(rl, 0);
	}
}

Rook::Rook(Position p)
{
	this->pos.x = p.x;
	this->pos.y = p.y;
}


Bishop::Bishop(char color, int num)
{
	int rl;
	if (num == 0) rl = 2;
	else		  rl = 5;

	if (color == 'W')
	{
		this->pos = Position(rl, 7);
	}
	else
	{
		this->pos = Position(rl, 0);
	}
}


Bishop::Bishop(Position p)
{
	this->pos.x = p.x;
	this->pos.y = p.y;
}


Knight::Knight(char color, int num)
{
	int rl;
	if (num == 0) rl = 1;
	else		  rl = 6;

	if (color == 'W')
	{
		this->pos = Position(rl, 7);
	}
	else
	{
		this->pos = Position(rl, 0);
	}
}

Knight::Knight(Position p)
{
	this->pos.x = p.x;
	this->pos.y = p.y;
}


Pawn::Pawn(char _color, int num)
{
	if (_color == 'W')
	{
		this->pos = Position(num, 6);
	}
	else
	{
		this->pos = Position(num, 1);
	}
	this->color = _color;
}

int eightDir[8][2] =
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

void King::getWay(Viewer& v)
{
	for (int i = 0; i < 8; i++)
	{
		Position p(this->pos.x + eightDir[i][0], this->pos.y + eightDir[i][1]);
		if (isPositionValid(p))
		{
			v.setWay(1, p.y, p.x);
		}
	}
	//如果可以入堡
	if (shortCastling)
	{
		v.setWay(1, pos.y, pos.x + 2);
	}
	if (longCastling)
	{
		v.setWay(1, pos.y, pos.x - 2);
	}
}

void Queen::getWay(Viewer& v)
{
	for (int i = 0; i < 8; i++)
	{
		Position here(this->pos.x + eightDir[i][0], this->pos.y + eightDir[i][1]);
		while (isPositionValid(here))
		{
			v.setWay(1, here.y, here.x);
			if (v.getVBoard(here.y, here.x) != "SPACE") break;

			here.x += eightDir[i][0];
			here.y += eightDir[i][1];
		}
	}
}

void Rook::getWay(Viewer& v)
{
	for (int i = 0; i < 4; i++)
	{
		Position here(this->pos.x + eightDir[2 * i][0], this->pos.y + eightDir[2 * i][1]);
		while (isPositionValid(here))
		{
			v.setWay(1, here.y, here.x);
			if (v.getVBoard(here.y, here.x) != "SPACE") break;

			here.x += eightDir[2 * i][0];
			here.y += eightDir[2 * i][1];
		}
	}
}

void Bishop::getWay(Viewer& v)
{
	for (int i = 0; i < 4; i++)
	{
		Position here(this->pos.x + eightDir[2 * i + 1][0], this->pos.y + eightDir[2 * i + 1][1]);
		while (isPositionValid(here))
		{
			v.setWay(1, here.y, here.x);
			if (v.getVBoard(here.y, here.x) != "SPACE") break;

			here.x += eightDir[2 * i + 1][0];
			here.y += eightDir[2 * i + 1][1];
		}
	}
}

int knightDir[8][2] =
{
	{-1, -2},
	{1, -2},
	{2, -1},
	{2, 1},
	{1, 2},
	{-1, 2},
	{-2, 1},
	{-2, -1}
};

void Knight::getWay(Viewer& v)
{
	for (int i = 0; i < 8; i++)
	{
		Position p(this->pos.x + knightDir[i][0], this->pos.y + knightDir[i][1]);
		if (isPositionValid(p))
		{
			v.setWay(1, p.y, p.x);
		}
	}
}

void Pawn::getWay(Viewer& v)
{
	//還沒動過
	if (!moved)
	{
		if (color == 'W')
		{
			Position here = this->pos;
			for (int i = 0; i < 2; i++)
			{
				here.y--;
				if (isPositionValid(here) && v.getVBoard(here.y, here.x) == "SPACE") v.setWay(1, here.y, here.x);
			}

			Position right(pos.x + 1, pos.y - 1), left(pos.x - 1, pos.y - 1);
			if (isPositionValid(right) && v.getVBoard(right.y, right.x) != "SPACE") v.setWay(1, right.y, right.x);
			if (isPositionValid(left) && v.getVBoard(left.y, left.x) != "SPACE") v.setWay(1, left.y, left.x);
		}
		else
		{
			Position here = this->pos;
			for (int i = 0; i < 2; i++)
			{
				here.y++;
				if (isPositionValid(here) && v.getVBoard(here.y, here.x) == "SPACE") v.setWay(1, here.y, here.x);
			}

			Position right(pos.x + 1, pos.y + 1), left(pos.x - 1, pos.y + 1);
			if (isPositionValid(right) && v.getVBoard(right.y, right.x) != "SPACE") v.setWay(1, right.y, right.x);
			if (isPositionValid(left) && v.getVBoard(left.y, left.x) != "SPACE") v.setWay(1, left.y, left.x);
		}
	}
	else
	{
		if (color == 'W')
		{
			Position here(pos.x, pos.y - 1);
			if (isPositionValid(here) && v.getVBoard(here.y, here.x) == "SPACE") v.setWay(1, here.y, here.x);

			Position right(pos.x + 1, pos.y - 1), left(pos.x - 1, pos.y - 1);
			if (isPositionValid(right) && v.getVBoard(right.y, right.x) != "SPACE") v.setWay(1, right.y, right.x);
			if (isPositionValid(left) && v.getVBoard(left.y, left.x) != "SPACE") v.setWay(1, left.y, left.x);
		}
		else
		{
			Position here(pos.x, pos.y + 1);
			if (isPositionValid(here) && v.getVBoard(here.y, here.x) == "SPACE") v.setWay(1, here.y, here.x);

			Position right(pos.x + 1, pos.y + 1), left(pos.x - 1, pos.y + 1);
			if (isPositionValid(right) && v.getVBoard(right.y, right.x) != "SPACE") v.setWay(1, right.y, right.x);
			if (isPositionValid(left) && v.getVBoard(left.y, left.x) != "SPACE") v.setWay(1, left.y, left.x);
		}
	}
}