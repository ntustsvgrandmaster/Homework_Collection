#include "pch.h"
#include "Player.h"

bool Player::getMoved()
{
	return this->moved;
}

void Player::resetMoved()
{
	this->moved = false;
}


void Player::eatChess(int i)
{
	vector<ChessClass*>::iterator it = pChess.begin();
	pChess.erase(it + i);
}

Position Player::istChessPos(int i)
{
	return pChess[i]->getPos();
}

int Player::pChessSize()
{
	return pChess.size();
}

HumanPlayer::HumanPlayer()
{
	char color = 'W';

	this->pChess.push_back(new King(color));
	this->pChess.push_back(new Queen(color));
	for (int i = 0; i < 2; i++)
	{
		this->pChess.push_back(new Rook(color, i));
		this->pChess.push_back(new Bishop(color, i));
		this->pChess.push_back(new Knight(color, i));
	}
	for (int i = 0; i < 8; i++)
	{
		this->pChess.push_back(new Pawn(color, i));
	}
}

HumanPlayer::HumanPlayer(char color)
{
	this->pChess.push_back(new King(color));
	this->pChess.push_back(new Queen(color));
	for (int i = 0; i < 2; i++)
	{
		this->pChess.push_back(new Rook(color, i));
		this->pChess.push_back(new Bishop(color, i));
		this->pChess.push_back(new Knight(color, i));
	}
	for (int i = 0; i < 8; i++)
	{
		this->pChess.push_back(new Pawn(color, i));
	}
}

void HumanPlayer::OnMove(Board& board, Viewer& v, int x, int y, Player& p, int op)
{
	//���h���outFromPos�̭����X�l�A�åB�I�s�L��getWay
	char from_x, from_y;
	from_x = x; from_y = y;
	/*std::cout << "please choose from pos: ";
	std::cin >> from_x >> from_y;*/

	//���J�ର�O��m
	Position outFromPos(from_x, from_y);
	int i;
	for (i = 0; i < pChess.size(); i++)
	{
		Position pos = pChess[i]->getPos();
		if (pos.x == outFromPos.x && pos.y == outFromPos.y) break;
	}
	//�䤣��Ӧ�m�W���i�H�ʪ��Ѥl
	if (i == pChess.size())
	{
		//cout << "invalid pos" << endl;
		return;
	}


	//system("cls");
	pChess[i]->getWay(v);
	//��ۤv���Ѥl�Ҧb�����|������
	for (int j = 0; j < pChess.size(); j++)
	{
		Position isMyChess = pChess[j]->getPos();
		v.setWay(0, isMyChess.y, isMyChess.x);
	}
	//set��viewer�C
}

void HumanPlayer::OnMove2(Board& board, Viewer& v, int nowX, int nowY, int lastX, int lastY, Player& p, int op)
{
	/*   ��l�]�w   */
	Position outFromPos;
	outFromPos.x = lastX;
	outFromPos.y = lastY;
	int i;
	for (i = 0; i < pChess.size(); i++)
	{
		Position pos = pChess[i]->getPos();
		if (pos.x == outFromPos.x && pos.y == outFromPos.y) break;
	}
	/****************/

	//��ܿ�w���Ѥl�n�쪺�a��
	char to_x, to_y;
	to_x = nowX; to_y = nowY;
	Position to_pos(to_x, to_y);
	//�O�i�H������!
	if (v.getWay(to_pos.y, to_pos.x) == 1 && isPositionValid(to_pos))
	{
		/*���ʴѤl*/
		pChess[i]->setPos(to_pos.x, to_pos.y);
		std::string chessName = board.getBoardElement(outFromPos.y, outFromPos.x);
		std::string covered = board.getBoardElement(to_pos.y, to_pos.x);
		board.setBoardElement(chessName, to_pos.y, to_pos.x);
		board.setBoardElement("SPACE", outFromPos.y, outFromPos.x);
		//�p�G�Q�N�x�F�A�N�h�ˬd�o�Ӳ��ʥi���i�H�����Q�N�x�����p
		Position kingPos;
		if (/*checked*/1)
		{
			v.setViewer(board);
			v.resetWay();
			//���o�ﭱ���Ҧ��i���ʸ��|
			int size = p.pChessSize();
			for (int i = 0; i < size; i++)
			{
				//���]�t�n�Q�Y�����l
				if (p.istChessPos(i).x == to_pos.x && p.istChessPos(i).y == to_pos.y) continue;
				p.istChessWay(i, v);
			}
			//�������ﭱ����ﭱ�l������
			for (int i = 0; i < size; i++)
			{
				//���]�t�n�Q�Y�����l
				v.setWay(0, p.istChessPos(i).y, p.istChessPos(i).x);
			}
			if (op == 1)
			{
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						if (v.getVBoard(j, i) == "WKing")
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
						if (v.getVBoard(j, i) == "BKing")
						{
							kingPos.x = i;
							kingPos.y = j;
						}
					}
				}
			}

			//�p�G���ʫ�|�Q�N�x�A�N��������
			if (v.getWay(kingPos.y, kingPos.x) == 1)
			{
				pChess[i]->setPos(outFromPos.x, outFromPos.y);
				board.setBoardElement(chessName, outFromPos.y, outFromPos.x);
				board.setBoardElement(covered, to_pos.y, to_pos.x);
			}
			else
			{
				this->checked = false;
				this->moved = true;
				pChess[i]->chessMoved();

				//�p�G�o��O����J���A�N���K���ʫ���
				if (board.getBoardElement(to_pos.y, to_pos.x).substr(1) == "King")
				{
					//��ܤF�ۤvx+2����m�A�ݩ�u����
					if (to_pos.x - outFromPos.x == 2)
					{
						std::string rName = board.getBoardElement(to_pos.y, to_pos.x + 1);
						pChess[5]->setPos(to_pos.x - 1, to_pos.y);
						board.setBoardElement("SPACE", to_pos.y, to_pos.x + 1);
						board.setBoardElement(rName, to_pos.y, to_pos.x - 1);
						pChess[5]->chessMoved();
					}
					//��ܤF�ۤvx-2����m�A�ݩ������
					else if (to_pos.x - outFromPos.x == -2)
					{
						std::string rName = board.getBoardElement(to_pos.y, to_pos.x - 2);
						pChess[2]->setPos(to_pos.x - 1, to_pos.y);
						board.setBoardElement("SPACE", to_pos.y, to_pos.x - 2);
						board.setBoardElement(rName, to_pos.y, to_pos.x + 1);
						pChess[2]->chessMoved();
					}
				}
			}
		}
		else
		{
			this->moved = true;
			pChess[i]->chessMoved();
		}
	}

	//system("cls");
	v.setViewer(board);
	v.resetWay();
	//v.printViewer();

	//if (board.getBoardElement(to_pos.y, to_pos.x).substr(1) == "Pawn")
	//{
	//	OnPromote(board, to_pos);
	//}

	//if (!this->moved)
	//{
	//	/*cout << "invalid way, please choose again" << endl;*/
	//}
}


void HumanPlayer::OnPromote(Board& board, Position& pawnPos, int whichUP)
{
	if (pawnPos.y == 0 /* && �ѬO��*/)
	{
		vector<ChessClass*>::iterator it = pChess.begin();
		int i;
		for (i = 0; i < pChess.size(); i++)
		{
			if (pChess[i]->getPos().x == pawnPos.x && pChess[i]->getPos().y == pawnPos.y)
			{
				pChess.erase(it + i);
				break;
			}
		}

		if (whichUP == 81)
		{
			board.setBoardElement("WQueen", pawnPos.y, pawnPos.x);
			this->pChess.push_back(new Queen(pawnPos));
		}
		else if (whichUP == 82)
		{
			board.setBoardElement("WRook", pawnPos.y, pawnPos.x);
			this->pChess.push_back(new Rook(pawnPos));
		}
		else if (whichUP == 84)
		{
			board.setBoardElement("WBishop", pawnPos.y, pawnPos.x);
			this->pChess.push_back(new Bishop(pawnPos));
		}
		else if (whichUP == 83)
		{
			board.setBoardElement("WKnight", pawnPos.y, pawnPos.x);
			this->pChess.push_back(new Knight(pawnPos));

		}
		else
		{
		}

	}
	else if (pawnPos.y == 7 /* && �ѬO��*/)
	{
		vector<ChessClass*>::iterator it = pChess.begin();
		int i;
		for (i = 0; i < pChess.size(); i++)
		{
			if (pChess[i]->getPos().x == pawnPos.x && pChess[i]->getPos().y == pawnPos.y)
			{
				pChess.erase(it + i);
				break;
			}
		}

		if (whichUP == 81)
		{
			board.setBoardElement("BQueen", pawnPos.y, pawnPos.x);
			this->pChess.push_back(new Queen(pawnPos));

		}
		else if (whichUP == 82)
		{
			board.setBoardElement("BRook", pawnPos.y, pawnPos.x);
			this->pChess.push_back(new Rook(pawnPos));

		}
		else if (whichUP == 84)
		{
			board.setBoardElement("BBishop", pawnPos.y, pawnPos.x);
			this->pChess.push_back(new Bishop(pawnPos));

		}
		else if (whichUP == 83)
		{
			board.setBoardElement("BKnight", pawnPos.y, pawnPos.x);
			this->pChess.push_back(new Knight(pawnPos));

		}
		else
		{
			/*cout << "Invalid choice. Please choose again." << endl;*/
		}

	}
}

// �M�X�ۤv�Ҧ����X�l�A�ݬݦ��S�����|�O�g�L�ﭱking���A�����ܴN����]�w checked = true;
void Player::check(int op, Player& p, Viewer& v)
{
	//�M����king����m
	Position kingPos;
	if (op == 0)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (v.getVBoard(j, i) == "WKing")
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
				if (v.getVBoard(j, i) == "BKing")
				{
					kingPos.x = i;
					kingPos.y = j;
				}
			}
		}
	}

	//���o��e�L���Ҧ��Ѥl�����ʸ��|
	int size = this->pChess.size();
	for (int i = 0; i < size; i++)
	{
		pChess[i]->getWay(v);
	}

	//�T�{���|�O�_�[�\��誺king
	if (v.getWay(kingPos.y, kingPos.x) == 1)
	{
		p.checked = true;
	}

	v.resetWay();
}

void Player::istChessWay(int i, Viewer& v)
{
	this->pChess[i]->getWay(v);
}

bool Player::isChecked()
{
	return this->checked;
}

void Player::castling(Player& p, Viewer& v, int curr)
{
	bool canShort = true, canLong = true;
	int mySize = this->pChessSize();
	int opSize = p.pChessSize();

	//�p�G������ʹL�B�άO�Q�N�x�F�N����J���o
	if (this->pChess[0]->getMoved() || checked)
	{
		pChess[0]->setShort(false);
		pChess[0]->setLong(false);
		return;
	}
	//���䪺�ʹL�F�N��Llong castling�]�w��false
	if (this->pChess[2]->getMoved())
	{
		pChess[0]->setLong(false);
		canLong = false;
	}
	//�k�䪺�ʹL�F�N��Lshort castling�]�w��false
	if (this->pChess[5]->getMoved())
	{
		pChess[0]->setShort(false);
		canShort = false;
	}
	if (!canShort && !canLong) return;

	/*�ˬd���|�O�_�i�H��*/
	//�ˬd���|�W�O�_����ê��
	for (int i = 1; i < 3; i++)
	{
		if (v.getVBoard(pChess[0]->getPos().y, pChess[0]->getPos().x + i) != "SPACE")
		{
			pChess[0]->setShort(false);
			canShort = false;
		}
		if (v.getVBoard(pChess[0]->getPos().y, pChess[0]->getPos().x - i) != "SPACE")
		{
			pChess[0]->setLong(false);
			canLong = false;
		}
	}
	if (!canShort && !canLong) return;

	//�ˬd���|�O�_�|�Q����
	for (int i = 0; i < opSize; i++)
	{
		p.istChessWay(i, v);
	}

	for (int i = 1; i < 3; i++)
	{
		if (v.getWay(pChess[0]->getPos().y, pChess[0]->getPos().x + i) == 1)
		{
			pChess[0]->setShort(false);
			canShort = false;
		}
		if (v.getWay(pChess[0]->getPos().y, pChess[0]->getPos().x - i) == 1)
		{
			pChess[0]->setLong(false);
			canLong = false;
		}
	}

	if (canShort)
	{
		pChess[0]->setShort(true);
	}
	if (canLong)
	{
		pChess[0]->setLong(true);
	}
	v.resetWay();
}