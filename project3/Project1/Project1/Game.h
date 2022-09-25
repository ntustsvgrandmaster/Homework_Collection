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
	//52張牌 + joker * 2
	int cards[54];
	//0 = 黑桃，1 = 紅心， 2 = 方塊，3 = 梅花
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
		//隨機發牌
		srand(time(NULL));
		int deal = 0;
		bool joker_draw = false;
		while (deal != 5)
		{
			int draw = rand() % 54; //52張牌+joker
			int color = draw / 13;
			int number = draw % 13 + 1;
			if (cards[draw] == 1)
			{
				if (draw > 51) //抽到鬼牌，且一次只能有一張
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
			cout << "請使用a/s移動方向來選擇要保留的卡片，並按下enter保留/取消保留。\n若選擇完畢，請按s。或選擇h顯示教學\n";
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
		//如果手上有鬼牌就不能再抽到鬼牌
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
						if (draw > 51) //鬼牌
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
			cout << "目前獲得獎金: " << award << "，是否要挑戰double chance? (y/n): ";
			char yes;
			while (cin >> yes)
			{
				if (yes == 'y')
				{
					double_chance(award);
					cout << "獲得獎金: " << award << endl;
					break;
				}
				else if (yes == 'n')
				{
					cout << "獲得獎金: " << award << endl;
					break;
				}
			}
		}
		else 
		{
			cout << "沒中獎QQ\n";
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
				cout << "保留!";
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
		bool joker = false; //調整鬼牌出現的情況
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

		if (royal) cout << "royal straight flush!! 拜託快去買樂透\n";
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

			cout << "請以選擇大小 (u/d): ";
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
					cout << "挑戰失敗，獎金歸0\n";
					award = 0;
					return;
				}
				else
				{
					cout << "挑戰成功，獎金加倍!\n";
					award *= 2;
				}
			}
			else 
			{
				cout << "平手!\n";
			}
			card[0][0] = card[1][0]; card[0][1] = card[1][1];
			char yes;
			if (i != 9) 
			{
				cout << "目前獎金: " << award << endl;
				cout << "請問要再挑戰一次嗎? (y/n): ";
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
		cout << "two pair:\t有兩組相同點數的牌。\n";
		cout << "three card:\t有三張卡片一樣數字。\n";
		cout << "straight:\t有連續的數字 (若是K->A不算，例如KA234)。\n";
		cout << "flush:\t\t五張牌相同花色。\n";
		cout << "full house:\t有三張相同點數的牌、配上另外兩張相同點數的牌。\n";
		cout << "four card:\t有四張相同數字的牌。\n";
		cout << "straight flush:\t五張牌相同花色，且數字連續。\n";
		cout << "five card:\t有四張相同數字的牌 + joker。\n";
		cout << "royal straight flush:\t五張相同花色、且為9 10 J Q K。\n\n";

		cout << "double chance:\t猜下一張牌出現的數字比現在大還是小，猜中了獎勵可以翻倍，猜錯了獎勵會歸0。" << endl;
		cout << "順序為 A 2 3 4 5 6 7 8 9 10 J Q K\n";
		cout << "已出現過的牌不會再出現。\n\n";
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
						cout << "獲取了 " << getPcoin(nowCookie) << " P幣!\n";
						pCoin += getPcoin(nowCookie);
						system("pause");
						break;
					}
					else if (ch == 'u')
					{
						int nextGet = getAmtUp(get_amt, nowCookie);
						if (nextGet == 0) {
							info = "餅乾不夠換取效率提升!\n";
						}
						get_amt += nextGet;
					}
					else if (ch == 'a')
					{
						int nextlvl = autoLevelUp(auto_level, nowCookie);
						if (nextlvl == 0) {
							info = "餅乾不夠升級餅乾機器!\n";
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
					cout << "已達倉庫容量上限! 強制出清\n";
					cout << "獲取了 " << 2000 << " P幣!\n";
					pCoin += 2000;
					system("pause");
					break;
				}
				if (move)
				{
					system("cls");
					cout << "按 enter 以獲取餅乾\n";
					cout << "按 u 來提升餅乾製作效率。 目前還需要 " << get_gate << " 塊餅乾才能夠升級\n";
					cout << "按 a 來購買自動製作餅乾機器。 目前還需要 " << auto_gate << " 塊餅乾才能夠升級\n";
					cout << "按 esc 可以把餅乾拿去賣換取P幣。 當前市場行情為500:1\n";
					cout << info;
					cout << "\n目前持有餅乾數量: " << nowCookie << endl << endl;
					cout << "目前的製作效率等級: " << get_level << endl;
					cout << "目前的餅乾製作機等級: " << auto_level << endl;
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