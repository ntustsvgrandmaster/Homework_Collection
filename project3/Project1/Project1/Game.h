#pragma once
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <math.h>
using namespace std;

class PokerGame 
{
private:
	//52�i�P + joker * 2
	int cards[54];
	//0 = �®�A1 = ���ߡA 2 = ����A3 = ����
	int gCards[5][2];
public:
	PokerGame() 
	{
		for (int i = 0; i < 54; i++) 
		{
			cards[i] = 1;
		}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				gCards[i][j] = 0;
			}
		}
	}
	
	void SetColor(int color = 7)
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
	}

	void gameReset() 
	{
		for (int i = 0; i < 54; i++)
		{
			cards[i] = 1;
		}
	}

	void playGame(int& coin)
	{
		//�H���o�P
		srand(time(NULL));
		int deal = 0;
		bool joker_draw = false;
		while (deal != 5)
		{
			int draw = rand() % 54; //52�i�P+joker
			int color = draw / 13;
			int number = draw % 13 + 1;
			if (cards[draw] == 1)
			{
				if (draw > 51) //��찭�P�A�B�@���u�঳�@�i
				{
					if (!joker_draw) 
					{
						cards[draw] = 0;
						gCards[deal][0] = 4;
						gCards[deal][1] = number;
						deal++;
						joker_draw = true;
					}
				}
				else
				{
					cards[draw] = 0;
					gCards[deal][0] = color;
					gCards[deal][1] = number;
					deal++;
				}
			}
		}
		int chosen[5] = { 0 }, nowChoose = 0;
		bool cho = false;
		while (!cho) 
		{
			cout << "�Шϥ�a/s���ʤ�V�ӿ�ܭn�O�d���d���A�ë��Uenter�O�d/�����O�d�C\n�Y��ܧ����A�Ы�s�C�ο��h��ܱо�\n";
			this->printPoke(chosen, nowChoose);
			char c = _getch();
			if (c == 'a') {
				nowChoose--;
				if (nowChoose == -1) nowChoose = 4;
				system("cls");
			}
			else if (c == 'd') 
			{
				nowChoose++;
				if (nowChoose == 5) nowChoose = 0;
				system("cls");
			}
			else if (c == 13) 
			{
				chosen[nowChoose] ^= 1;
				system("cls");
			}
			else if (c == 's') 
			{
				cho = true;
			}
			else if (c == 'h') {
				system("cls");
				this->getHelp();
				system("pause");
				system("cls");
			}
			else 
			{
				system("cls");
			}
		}
		//�p�G��W�����P�N����A��찭�P
		bool joker_drew = false;
		for (int i = 0; i < 5; i++) 
		{
			if (chosen[i] == 1 && gCards[i][0] == 4) joker_drew = true;
		}
		for (int i = 0; i < 5; i++) 
		{
			if (chosen[i] == 0) 
			{
				bool canDeal = false;
				while (!canDeal) {
					int draw = rand() % 54;
					int color = draw / 13;
					int number = draw % 13 + 1;
					if (cards[draw] == 1)
					{
						cards[draw] = 0;
						if (draw > 51) //���P
						{
							if (!joker_drew) 
							{
								gCards[i][0] = 4;
								gCards[i][1] = number;
								canDeal = true;
								joker_drew = true;
							}
						}
						else 
						{
							gCards[i][0] = color;
							gCards[i][1] = number;
							canDeal = true;
						}
					}
				}
			}
		}
		int award = this->check();
		this->gameReset();

		if (award != 0) 
		{
			cout << "�ثe��o����: " << award << "�A�O�_�n�D��double chance? (y/n): ";
			char yes;
			while (cin >> yes)
			{
				if (yes == 'y')
				{
					double_chance(award);
					cout << "��o����: " << award << endl;
					break;
				}
				else if (yes == 'n')
				{
					cout << "��o����: " << award << endl;
					break;
				}
			}
		}
		else 
		{
			cout << "�S����QQ\n";
		}

		coin += award;
	}

	void printPoke(int chosen[5], int now) 
	{
		cout << " ___ " << " ___ " << " ___ " << " ___ " << " ___ " << endl;
		for (int i = 0; i < 5; i++)
		{
			cout << "|";

			if (gCards[i][0] == 0)
			{
				cout << 'S';
			}
			else if (gCards[i][0] == 1)
			{
				SetColor(12);
				cout << 'H';
				SetColor();
			}
			else if (gCards[i][0] == 2)
			{
				SetColor(12);
				cout << 'D';
				SetColor();
			}
			else if(gCards[i][0] == 3)
			{
				cout << 'C';
			}
			else 
			{
				cout << "   |";
				continue;
			}

			if (gCards[i][1] == 10)
			{
				cout << "10|";
			}
			else
			{

				if (gCards[i][1] > 10 || gCards[i][1] < 2)
				{
					if (gCards[i][1] == 11) cout << 'J';
					else if (gCards[i][1] == 12) cout << 'Q';
					else if (gCards[i][1] == 13) cout << 'K';
					else if (gCards[i][1] == 1) cout << 'A';
				}
				else
				{
					cout << gCards[i][1];
				}
				cout << " |";
			}
		}
		cout << endl;
		for (int i = 0; i < 5; i++)
		{
			if (gCards[i][0] != 4) 
			{
				cout << "|   |";
			}
			else 
			{
				cout << "| J |";
			}
		}
		cout << endl;
		for (int i = 0; i < 5; i++)
		{
			if (gCards[i][0] == 4) 
			{
				cout << "|___|";
				continue;
			}

			if (gCards[i][1] == 10)
			{
				cout << "|10";
			}
			else {
				cout << "|_";
				if (gCards[i][1] > 10 || gCards[i][1] < 2)
				{

					if (gCards[i][1] == 11) cout << 'J';
					else if (gCards[i][1] == 12) cout << 'Q';
					else if (gCards[i][1] == 13) cout << 'K';
					else if (gCards[i][1] == 1) cout << 'A';
				}
				else
				{
					cout << gCards[i][1];
				}
			}
			if (gCards[i][0] == 0)
			{
				cout << 'S';
			}
			else if (gCards[i][0] == 1)
			{
				SetColor(12);
				cout << 'H';
				SetColor();
			}
			else if (gCards[i][0] == 2)
			{
				SetColor(12);
				cout << 'D';
				SetColor();
			}
			else
			{
				cout << 'C';
			}
			cout << "|";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) 
		{
			if (chosen[i] == 1) 
			{
				SetColor(207);
				cout << "�O�d!";
				SetColor();
			}
			else 
			{
				cout << "     ";
			}
		}
		cout << endl;
		for (int i = 0; i < 5; i++)
		{
			if (i == now)
			{
				cout << "  ^  ";
			}
			else
			{
				cout << "     ";
			}
		}
		cout << endl;
	}

	int check() {
		int award = 0;
		int choose[5] = { 0 }, now = 5;
		printPoke(choose, now);
		int colorAppear[4] = { 0 }, numAppear[13] = { 0 };
		bool joker = false; //�վ㰭�P�X�{�����p
		for (int i = 0; i < 5; i++) 
		{
			if (gCards[i][0] == 4) 
			{
				joker = true;
			}
			else 
			{
				colorAppear[gCards[i][0]]++;
				numAppear[gCards[i][1] - 1]++;
			}
		}
		//two pair
		bool two_pair = false;
		bool one_pair = false;
		bool joker_used = joker;
		for (int i = 0; i < 13; i++)
		{
			if (numAppear[i] >= 2)
			{
				if (!one_pair) one_pair = true;
				else two_pair = true;
			}
			else if(numAppear[i] == 1 && joker_used)
			{
				joker_used = false;
				one_pair = true;
			}
		}
		if (two_pair) { award = 1;}
		//three card
		bool three_card = false;
		for (int i = 0; i < 5; i++)
		{
			if (numAppear[gCards[i][1] - 1] == 3) three_card = true;
			else if (numAppear[gCards[i][1] - 1] == 2 && joker) three_card = true;
		}
		if (three_card) { award = 1;}
		//straight
		bool straight = false;
		for (int i = 0; i < 9; i++) 
		{
			joker_used = joker;
			if (numAppear[i] >= 2) break;
			if (numAppear[i] == 1) 
			{
				if (numAppear[i + 1] == 1) 
				{
					if (numAppear[i + 2] == 1)
					{
						if (numAppear[i + 3] == 1)
						{
							if (numAppear[i + 4] == 1) straight = true;
							else if(numAppear[i + 4] == 0 && joker) straight = true;
						}
						else if (numAppear[i + 3] == 0 && joker)
						{
							if (numAppear[i + 4] == 1) straight = true;
						}
					}
					else if (numAppear[i + 2] == 0 && joker)
					{
						if (numAppear[i + 3] == 1 && numAppear[i + 4] == 1) straight = true;
					}
				}
				else if (numAppear[i + 1] == 0 && joker) 
				{
					if (numAppear[i + 2] == 1 && numAppear[i + 3] == 1 && numAppear[i + 4] == 1) straight = true;
				}
			}
			else if (numAppear[i] == 0 && joker) 
			{
				if (numAppear[i + 1] == 1 && numAppear[i + 2] == 1 && numAppear[i + 3] == 1 && numAppear[i + 4] == 1) straight = true;
			}
		}
		//10 J Q K + joker;
		if (numAppear[9] == 1 && numAppear[10] == 1 && numAppear[11] == 1 && numAppear[12] == 1 && joker) straight = true;
		if (straight) { award = 3; }
		//flush
		bool flush = false;
		for (int i = 0; i < 4; i++)
		{
			if (colorAppear[i] == 5) flush = true;
			else if (colorAppear[i] == 4 && joker) flush = true;
		}
		if (flush) { award = 4; }
		//full house 10
		bool full_house = false;
		one_pair = false;
		if (two_pair) 
		{
			for (int i = 0; i < 13; i++)
			{
				if (numAppear[i] == 3)
				{
					for (int j = 0; j < 4; j++) 
					{
						if (j != i) 
						{
							if (numAppear[j] == 2) full_house = true;
							else if (numAppear[j] == 1 && joker) full_house = true;
						}
					}
				}
				else if (numAppear[i] == 2 && joker) 
				{
					for (int j = 0; j < 4; j++)
					{
						if (numAppear[j] == 2 && j != i) full_house = true;
					}
				}
			}
		}
		if (full_house) { award = 10; }
		//four card 20
		bool four_card = false;
		for (int i = 0; i < 13; i++)
		{
			if (numAppear[i] == 4) four_card = true;
			else if (numAppear[i] == 3 && joker) four_card = true;
		}
		if (four_card) { award = 20; }
		//straight flush 25
		bool straight_flush = false, sameColor = false;
		for (int i = 0; i < 5; i++) 
		{
			if (colorAppear[i] == 5) sameColor = true;
			else if (colorAppear[i] == 4 && joker) sameColor = true;
		}
		if (sameColor && straight)
		{
			straight_flush = true;
		}
		if (straight_flush) { award = 25; }
		//five card 60
		bool five_card = false;
		for (int i = 0; i < 13; i++) 
		{
			if (numAppear[i] == 4 && joker) five_card = true;
		}
		if (five_card) { award = 60; }
		//royal straight flush 250
		bool royal = false;
		if (straight_flush)
		{
			int i = 8;
			if (numAppear[i] == 1)
			{
				if (numAppear[i + 1] == 1)
				{
					if (numAppear[i + 2] == 1)
					{
						if (numAppear[i + 3] == 1)
						{
							if (numAppear[i + 4] == 1) royal = true;
							else if (numAppear[i + 4] == 0 && joker) royal = true;
						}
						else if (numAppear[i + 3] == 0 && joker)
						{
							if (numAppear[i + 4] == 1) royal = true;
						}
					}
					else if (numAppear[i + 2] == 0 && joker)
					{
						if (numAppear[i + 3] == 1 && numAppear[i + 4] == 1) royal = true;
					}
				}
				else if (numAppear[i + 1] == 0 && joker)
				{
					if (numAppear[i + 2] == 1 && numAppear[i + 3] == 1 && numAppear[i + 4] == 1) royal = true;
				}
			}
			else if (numAppear[i] == 0 && joker)
			{
				if (numAppear[i + 1] == 1 && numAppear[i + 2] == 1 && numAppear[i + 3] == 1 && numAppear[i + 4] == 1) royal = true;

			}
			if (numAppear[9] == 1 && numAppear[10] == 1 && numAppear[11] == 1 && numAppear[12] == 1 && joker) royal = true;
		}

		if (royal) cout << "royal straight flush!! ���U�֥h�R�ֳz\n";
		else if (five_card) cout << "five card!\n";
		else if (straight_flush) cout << "straight flush!\n";
		else if (four_card) cout << "four card!\n";
		else if (full_house) cout << "full house!\n";
		else if (flush) cout << "flush!\n";
		else if (straight) cout << "straight!\n";
		else if (three_card) cout << "three card!\n";
		else if (two_pair) cout << "two pair!\n";

		return award;
	}

	void double_chance(int& award)
	{
		srand(time(NULL));
		int draw = rand() % 52;
		int color = draw / 13;
		int number = draw % 13;
		int card[2][2] = { { color, number }, {4, 13} };
		cards[draw] = 0;

		for (int i = 0; i < 10; i++) 
		{
			system("cls");
			card[1][0] = 4; card[1][1] = 13;
			print_two_card(card);
			bool drew = false;
			while (!drew) 
			{
				draw = rand() % 52;
				color = draw / 13;
				number = draw % 13 + 1;
				if (cards[draw] == 1) 
				{
					cards[draw] = 0;
					card[1][0] = color;
					card[1][1] = number;
					drew = true;
				}
			}

			cout << "�ХH��ܤj�p (u/d): ";
			char ud;
			while (cin >> ud) 
			{
				if (ud == 'u' || ud == 'd') break;
			}

			bool win , draw = false;
			if (card[0][1] > card[1][1]) 
			{
				if (ud == 'd') win = true;
				else win = false;
			}
			else if (card[0][1] < card[1][1]) 
			{
				if (ud == 'u') win = true;
				else win = false;
			}
			else draw = true;

			print_two_card(card);

			if (!draw) 
			{
				if (!win)
				{
					cout << "�D�ԥ��ѡA�����k0\n";
					award = 0;
					return;
				}
				else
				{
					cout << "�D�Ԧ��\�A�����[��!\n";
					award *= 2;
				}
			}
			else 
			{
				cout << "����!\n";
			}
			card[0][0] = card[1][0]; card[0][1] = card[1][1];
			char yes;
			if (i != 9) 
			{
				cout << "�ثe����: " << award << endl;
				cout << "�аݭn�A�D�Ԥ@����? (y/n): ";
				while (cin >> yes)
				{
					if (yes == 'y')
					{
						break;
					}
					else if (yes == 'n')
					{
						return;
					}
				}
			}
		}
	}

	void print_two_card(int gCard[2][2])
	{
		cout << " ___ " << " ___ " << endl;
		for (int i = 0; i < 2; i++)
		{
			cout << "|";

			if (gCard[i][0] == 0)
			{
				cout << 'S';
			}
			else if (gCard[i][0] == 1)
			{
				SetColor(12);
				cout << 'H';
				SetColor();
			}
			else if (gCard[i][0] == 2)
			{
				SetColor(12);
				cout << 'D';
				SetColor();
			}
			else if (gCard[i][0] == 3)
			{
				cout << 'C';
			}
			else
			{
				cout << "   |";
				continue;
			}

			if (gCard[i][1] == 10)
			{
				cout << "10|";
			}
			else
			{

				if (gCard[i][1] > 10 || gCard[i][1] < 2)
				{
					if (gCard[i][1] == 11) cout << 'J';
					else if (gCard[i][1] == 12) cout << 'Q';
					else if (gCard[i][1] == 13) cout << 'K';
					else if (gCard[i][1] == 1) cout << 'A';
				}
				else
				{
					cout << gCard[i][1];
				}
				cout << " |";
			}
		}
		cout << endl;
		for (int i = 0; i < 2; i++)
		{
			if (gCard[i][0] != 4)
			{
				cout << "|   |";
			}
			else
			{
				cout << "|   |";
			}
		}
		cout << endl;
		for (int i = 0; i < 2; i++)
		{
			if (gCard[i][0] == 4)
			{
				cout << "|___|";
				continue;
			}

			if (gCard[i][1] == 10)
			{
				cout << "|10";
			}
			else {
				cout << "|_";
				if (gCard[i][1] > 10 || gCard[i][1] < 2)
				{

					if (gCard[i][1] == 11) cout << 'J';
					else if (gCard[i][1] == 12) cout << 'Q';
					else if (gCard[i][1] == 13) cout << 'K';
					else if (gCard[i][1] == 1) cout << 'A';
				}
				else
				{
					cout << gCard[i][1];
				}
			}
			if (gCard[i][0] == 0)
			{
				cout << 'S';
			}
			else if (gCard[i][0] == 1)
			{
				SetColor(12);
				cout << 'H';
				SetColor();
			}
			else if (gCard[i][0] == 2)
			{
				SetColor(12);
				cout << 'D';
				SetColor();
			}
			else
			{
				cout << 'C';
			}
			cout << "|";
		}
		cout << endl;
	}

	void getHelp() 
	{
		cout << "two pair:\t����լۦP�I�ƪ��P�C\n";
		cout << "three card:\t���T�i�d���@�˼Ʀr�C\n";
		cout << "straight:\t���s�򪺼Ʀr (�Y�OK->A����A�ҦpKA234)�C\n";
		cout << "flush:\t\t���i�P�ۦP���C\n";
		cout << "full house:\t���T�i�ۦP�I�ƪ��P�B�t�W�t�~��i�ۦP�I�ƪ��P�C\n";
		cout << "four card:\t���|�i�ۦP�Ʀr���P�C\n";
		cout << "straight flush:\t���i�P�ۦP���A�B�Ʀr�s��C\n";
		cout << "five card:\t���|�i�ۦP�Ʀr���P + joker�C\n";
		cout << "royal straight flush:\t���i�ۦP���B�B��9 10 J Q K�C\n\n";

		cout << "double chance:\t�q�U�@�i�P�X�{���Ʀr��{�b�j�٬O�p�A�q���F���y�i�H½���A�q���F���y�|�k0�C" << endl;
		cout << "���Ǭ� A 2 3 4 5 6 7 8 9 10 J Q K\n";
		cout << "�w�X�{�L���P���|�A�X�{�C\n\n";
	}
};

class cookieMaker {
	private:
		int get_amt;
		int get_level;
		int get_gate;
		int auto_level;
		int auto_gate;
		int nowCookie;
	public:
		cookieMaker() {
			auto_level = 0;
			get_amt = 1;
			get_level = 1;
			get_gate = 10;
			nowCookie = 0;
			auto_gate = 100;
		}

		void game(int& pCoin)
		{
			double start = clock(), end;
			double second = 0;
			char ch;
			string info = "";
			bool move = true;
			while (1)
			{
				if (_kbhit())
				{
					ch = _getch();
					if (ch == 27)
					{
						system("cls");
						cout << "����F " << getPcoin(nowCookie) << " P��!\n";
						pCoin += getPcoin(nowCookie);
						system("pause");
						break;
					}
					else if (ch == 'u')
					{
						int nextGet = getAmtUp(get_amt, nowCookie);
						if (nextGet == 0) {
							info = "�氮���������Ĳv����!\n";
						}
						get_amt += nextGet;
					}
					else if (ch == 'a')
					{
						int nextlvl = autoLevelUp(auto_level, nowCookie);
						if (nextlvl == 0) {
							info = "�氮�����ɯŻ氮����!\n";
						}
						auto_level += nextlvl;
					}
					else if (ch == 13)
					{
						nowCookie += get_amt;
						info = "";
					}
					move = true;
				}
				end = clock();
				if (((end - start) / CLOCKS_PER_SEC) > second + 1)
				{
					nowCookie += get_amt * auto_level;
					second++;
					move = true;
				}
				if (nowCookie >= 1000000) 
				{
					system("cls");
					cout << "�w�F�ܮw�e�q�W��! �j��X�M\n";
					cout << "����F " << 2000 << " P��!\n";
					pCoin += 2000;
					system("pause");
					break;
				}
				if (move)
				{
					system("cls");
					cout << "�� enter �H����氮\n";
					cout << "�� u �Ӵ��ɻ氮�s�@�Ĳv�C �ثe�ٻݭn " << get_gate << " ���氮�~����ɯ�\n";
					cout << "�� a ���ʶR�۰ʻs�@�氮�����C �ثe�ٻݭn " << auto_gate << " ���氮�~����ɯ�\n";
					cout << "�� esc �i�H��氮���h�洫��P���C ��e�����污��500:1\n";
					cout << info;
					cout << "\n�ثe�����氮�ƶq: " << nowCookie << endl << endl;
					cout << "�ثe���s�@�Ĳv����: " << get_level << endl;
					cout << "�ثe���氮�s�@������: " << auto_level << endl;
					move = false;
				}
				Sleep(50);
			}
		}

		int getPcoin(int cookies)
		{
			return cookies / 500;
		}

		int autoLevelUp(int nowlvl, int& nowCookie)
		{
			if (nowCookie >= auto_gate)
			{
				nowCookie -= auto_gate;
				auto_gate = pow((auto_level + 1), 2) * 100;
				return 1;
			}
			return 0;
		}

		int getAmtUp(int now_amt, int& nowCookie)
		{
			if (nowCookie >= get_gate)
			{
				nowCookie -= get_gate;
				get_gate = pow(get_level + 1, 2) * 10;
				return ++get_level / 2;
			}
			return 0;
		}
};