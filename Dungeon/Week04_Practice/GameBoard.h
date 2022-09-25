#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include <Mmsystem.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include "Hero.h"
#include "Creature.h"
#pragma comment(lib,"winmm.lib")

namespace {
	using namespace std;

	enum class Mode{
		DIFF, ANS
	};

	struct Question
	{
		int answer;		//該題目的答案
		string que;		//該題目的題目敘述
		string ans[4];	//該題目的選項
	};

	class GameBoard {
	private:
		Mode mode;
		char board[30][30];
		string types[6] = { "數學", "英文", "地理", "歷史", "猜謎", "生活" };
		string stars[3] = { "一星", "二星", "三星" };
		Question qs[6][3][10]; //6種類、3顆星、一顆星10題
		int quized[6][3][10] = { 0 };
		int randType[3] = { 0, 1, 2 }; //三個難度分別的類型，用rand抽
		int all_killed[5] = { 0 };
		bool three_star = true;

		int tp = 0;
		int df = 0;
		int qz = 0;
		int ans = 0;
	public:
		GameBoard() 
		{ 
			for (int i = 0; i < 30; i++)
			{
				for (int j = 0; j < 30; j++) 
				{
					board[i][j] = ' ';
				}
			}
			mode = Mode::DIFF;
			srand(time(NULL));
		}

		//版面設計用
		void gotoxy(int xpos, int ypos)
		{
			COORD scrn;
			HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
			scrn.X = xpos; scrn.Y = ypos;
			SetConsoleCursorPosition(hOuput, scrn);
		}

		void SetColor(int color = 7)
		{
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
		}
		//版面設計用

		void Guide(Hero& h, Creature& c) //guide battle
		{
			printCutscenes();
			system("cls");
			printBoard(h, c);
			string word = "\n野生的史萊姆出現了，\n靠你的智慧打倒它吧！\n\n";
			cout << endl;
			for (int i = 0; i < word.size(); i++) 
			{
				cout << word[i];
				Sleep(50);
			}
			cout << "按任意按鍵進入戰鬥 . . ." ;
			system("pause>nul");

			system("cls");
			printBoard(h, c);
			word = "\n使用aswd來操控箭頭方向，並且使用enter鍵選擇\n\n";	
			cout << endl;
			cout << endl;
			for (int i = 0; i < word.size(); i++)
			{
				cout << word[i];
				Sleep(50);
			}
			cout << "按任意按鍵進入戰鬥 . . .";
			system("pause>nul");

			char ch;
			bool end = false;

			//選擇一星、正確答案的範例		
			while (1)
			{
				while (!end)
				{
					system("cls");
					printBoard(h, c);
					gotoxy(1, 18);
					SetColor(225);
					cout << "一星  數學";
					SetColor();
					inputing(end);
				}
				end = false;
				if (df == 0) break;
			}
			tp = randType[df]; //類型 = 隨機抽出的類型中，選定難度對應的類型
			mode = Mode::ANS;
			while (1)
			{
				while (!end)
				{
					system("cls");
					printBoard(h, c);
					gotoxy(25, 22);
					SetColor(225);
					cout << "四";
					SetColor();
					inputing(end);
				}
				end = false;
				if (ans == 3) break;
			}
			heroAttack(h, c);
			creatureAttake(h, c);

			gotoxy(0, 24);
			word = "當選擇正確的答案時，可以攻擊敵人並且削減對方體力\n同時，在回合結束後會受到對方的攻擊";
			for (int i = 0; i < word.size(); i++)
			{
				cout << word[i];
				Sleep(50);
			}
			system("pause>nul");

			//選擇三星、錯誤答案的範例
			df = 0; ans = 0;
			mode = Mode::DIFF;
			while (1)
			{
				while (!end)
				{
					system("cls");
					printBoard(h, c);
					gotoxy(1, 20);
					SetColor(225);
					cout << "三星  地理";
					SetColor();
					inputing(end);
				}
				end = false;
				if (df == 2) break;
			}
			tp = randType[df];
			mode = Mode::ANS;
			while (1)
			{
				while (!end)
				{
					system("cls");
					printBoard(h, c);
					gotoxy(1, 21);
					SetColor(225);
					cout << "亞洲";
					SetColor();
					inputing(end);
				}
				end = false;
				if (ans == 0) break;
			}
			creatureAttake(h, c);

			gotoxy(0, 24);
			word = "當選擇錯誤的答案時，攻擊將無法命中對手並且給予傷害。";			
			for (int i = 0; i < word.size(); i++)
			{
				cout << word[i];
				Sleep(50);
			}
			system("pause>nul");

			//選擇三星、正確答案的範例
			df = 0; ans = 0;
			mode = Mode::DIFF;
			while (1)
			{
				while (!end)
				{
					system("cls");
					printBoard(h, c);
					gotoxy(1, 19);
					SetColor(225);
					cout << "二星  英文";
					SetColor();
					inputing(end);
				}
				end = false;
				if (df == 1) break;
			}
			tp = randType[df];
			mode = Mode::ANS;
			while (1)
			{
				while (!end)
				{
					system("cls");
					printBoard(h, c);
					gotoxy(1, 21);
					SetColor(225);
					cout << "moist";
					SetColor();
					inputing(end);
				}
				end = false;
				if (ans == 0) break;
			}
			heroAttack(h, c);

			gotoxy(0, 24);
			word = "選擇的難度越高，給予對方的傷害也會提升";
			for (int i = 0; i < word.size(); i++)
			{
				cout << word[i];
				Sleep(50);
			}
			system("pause>nul");
			//戰鬥結束文字提示

			SetColor(63);
			gotoxy(10, 5); cout << " __________________________ ";
			gotoxy(10, 6); cout << "|戰鬥勝利！按任意鍵回到地宮|";
			gotoxy(10, 7); cout << " ￣￣￣￣￣￣￣￣￣￣￣￣￣ ";
			SetColor();
			all_killed[0]++;
			system("pause>nul");
			system("cls");
		}

		void Battle(Hero& h, Creature& c) //normal battle
		{
			printCutscenes();

			bool inputed = false;
			while (c.getHealth() > 0 && h.getHealth() > 0) 
			{
				for (int i = 0; i < 3; i++) 
				{
					randType[i] = rand() % 6;
				}
				//選擇難度
				mode = Mode::DIFF;
				while (!inputed) 
				{
					system("cls");
					printBoard(h, c);
					inputing(inputed);
				}
				inputed = false;
				tp = randType[df];
				qz = rand() % 10;
				//選擇答案
				mode = Mode::ANS;
				while (!inputed)
				{
					system("cls");
					printBoard(h, c);
					inputing(inputed);
				}
				inputed = false;

				if (ans == qs[tp][df][qz].answer) 
				{
					heroAttack(h, c);
				}
				if (c.getHealth() > 0) 
				{
					creatureAttake(h, c);
				}
				if (df != 2) three_star = false;

				tp = df = ans = 0; //重製選項
			}
			if (h.getHealth() <= 0) 
			{
				SetColor(63);
				gotoxy(10, 5); cout << " ____________________________ ";
				gotoxy(10, 6); cout << "|你已經死了！按任意鍵回到地宮|";
				gotoxy(10, 7); cout << " ￣￣￣￣￣￣￣￣￣￣￣￣￣￣ ";
				SetColor();
				system("pause>nul");
				system("cls");
			}
			else 
			{
				SetColor(63);
				gotoxy(10, 5); cout << " __________________________ ";
				gotoxy(10, 6); cout << "|戰鬥勝利！按任意鍵回到地宮|";
				gotoxy(10, 7); cout << " ￣￣￣￣￣￣￣￣￣￣￣￣￣ ";
				SetColor();
				if (c.getIcon() == "Ｌ") 
				{
					all_killed[0]++;
				}
				else if (c.getIcon() == "Ｂ")
				{
					all_killed[1]++;
				}
				else if (c.getIcon() == "Ｚ")
				{
					all_killed[2]++;
				}
				else if (c.getIcon() == "Ｅ")
				{
					all_killed[3]++;
				}
				else if (c.getIcon() == "Ｐ")
				{
					all_killed[4]++;
				}
				system("pause>nul");
				system("cls");
			}
		}

		void printCutscenes() //過場動畫
		{
			Sleep(50);
			int x = 0, y = 0;
			int dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
			int di = 0;
			int visit[10][10] = { 0 };
			string wall = "■";

			while (x != 5 || y != 5)
			{
				gotoxy(x * 2, y);
				cout << wall;
				visit[x][y] = 1;
				x += dir[di][0];
				y += dir[di][1];
				if (visit[x][y] == 1 || x >= 10 || y >= 10 || x < 0 || y < 0)
				{
					x -= dir[di][0];
					y -= dir[di][1];
					di++;
					if (di == 4) di = 0;
					x += dir[di][0];
					y += dir[di][1];
				}
				Sleep(1);
			}
			gotoxy(8, 5);
			cout << wall << wall;

			Sleep(20);
		}

		void printBoard(Hero& h, Creature& c)
		{
			printCreature(c.getIcon());

			//印英雄圖樣
			cout << "            ^" << endl;
			cout << "           |||" << endl;
			cout << " ___/￣￣\\ |||" << endl;
			cout << "|  | HERO ||||" << endl;
			cout << "|   \\    /==O==" << endl;
			cout << "\\__/ ￣￣   |" << endl << endl;

			gotoxy(2, 8);
			cout << "HP : " << h.getHealth();
			gotoxy(25, 2);
			cout << "HP : " << c.getHealth();
			gotoxy(0, 15);
			cout << "=================================================" << endl;

			if (mode == Mode::DIFF) //選擇題目難度
			{
				cout << " 請選擇題目難度\n" << endl;
				for (int i = 0; i < 3; i++)
				{
					if (df == i) cout << ">";
					else cout << " ";

					cout << stars[i] << "  " << types[randType[i]] << endl;
				}
				cout << endl;
			}
			else if (mode == Mode::ANS) //選擇答案
			{
				cout << "Q:                                            \n"
					 << qs[tp][df][qz].que << endl;
				cout << "=================================================\n";
				cout << " 請選擇答案\n" << endl;
				for (int i = 0; i < 4; i++)
				{
					if (i == 2) cout << endl;
					if (ans == i) cout << ">";
					else cout << " ";

					cout << qs[tp][df][qz].ans[i] << "\t\t\t";
				}
				cout << endl;
			}
			cout << "=================================================";
		}

		void printCreature(string c) //c = creature的icon，會依據不同的icon印出不同的怪物
		{
			if (c == "Ｌ") //slime
			{
				gotoxy(20, 3); cout << "    __ __   O" << endl;
				gotoxy(20, 4); cout << "  _/  V  \\___  #" << endl;
				gotoxy(20, 5); cout << " C    |  |   \\" << endl;
				gotoxy(20, 6); cout << " \\  ___ w  _ C\\" << endl;
				gotoxy(20, 7); cout << " /_/   \\__/ \\__\\" << endl;
			}
			else if (c == "Ｂ") //bat
			{
				gotoxy(20, 3); cout << "        ^     ^" << endl;
				gotoxy(20, 4); cout << "       / \\___/ \\" << endl;
				gotoxy(20, 5); cout << "  ^___/  |  |   \\____^" << endl;
				gotoxy(20, 6); cout << " /        ___         \\" << endl;
				gotoxy(20, 7); cout << " \\ /\\     V V      /\\ /" << endl;
				gotoxy(20, 8); cout << "  V  V￣\\_____/￣ V  V" << endl;
			}
			else if (c == "Ｚ") //zombie
			{
				gotoxy(20, 3); cout << "   ____   " << endl;
				gotoxy(20, 4); cout << "  /o O \\ " << endl;
				gotoxy(20, 5); cout << "  \\口__/" << endl;
				gotoxy(20, 6); cout << "  __||__" << endl;
				gotoxy(20, 7); cout << " /  || /" << endl;
				gotoxy(20, 8); cout << "   _||_" << endl;
				gotoxy(20, 9); cout << "  |    |" << endl;
			}
			else if (c == "Ｅ") //skeleton
			{
				gotoxy(20, 3); cout << "     ____   " << endl;
				gotoxy(20, 4); cout << "    /O O \\ " << endl;
				gotoxy(20, 5); cout << "    \\ o  /" << endl;
				gotoxy(20, 6); cout << "oo   uuuu" << endl;
				gotoxy(20, 7); cout << " \\ ___||__" << endl;
				gotoxy(20, 8); cout << "  \\   || /" << endl;
				gotoxy(20, 9); cout << "  00 _||_" << endl;
				gotoxy(20, 10); cout << "    |    |" << endl;
			}
			else if (c == "Ｐ") //spider
			{
				gotoxy(20, 3); cout << "    ^___^" << endl;
				gotoxy(20, 4); cout << "   /o o o\\" << endl;
				gotoxy(20, 5); cout << "  /  o o  \\" << endl;
				gotoxy(20, 6); cout << "  \\ o o o↙↗￣￣↘" << endl;
				gotoxy(20, 7); cout << "   V￣￣V  ########|" << endl;
				gotoxy(20, 8); cout << "  / | | \\↖__|__\\↙" << endl;
				gotoxy(20, 9); cout << " /  | | /  / | | \\" << endl;
			}
		}

		void inputing(bool &end) 
		{
			char ch;
			ch = _getch();
			if (mode == Mode::DIFF) 
			{
				if (ch == 13) end = true;
				else if (ch == 'w')
				{
					if (df > 0) df --;
				}
				else if (ch == 's')
				{
					if (df < 2) df ++;
				}
			}
			else if (mode == Mode::ANS) 
			{
				if (ch == 13) end = true;
				else if (ch == 'w')
				{
					if (ans >= 2) ans -= 2;
				}
				else if (ch == 'a')
				{
					if (ans != 0 && ans != 2) ans--;
				}
				else if (ch == 's')
				{
					if (ans < 2) ans += 2;
				}
				else if (ch == 'd')
				{
					if (ans != 1 && ans != 3) ans++;
				}
			}
		}

		void heroAttack(Hero& h, Creature& c) //攻擊動畫 
		{
			int x = 23, y = 3;
			gotoxy(x, y);
			cout << "\\";
			gotoxy(x + 1, y + 1);
			cout << "\\";

			Sleep(50);
			for (int i = 0; i < 5; i++) 
			{
				gotoxy(x++, y++);
				cout << " ";
				gotoxy(x + 1, y+ 1);
				cout << "\\";
				Sleep(50);
				gotoxy(25, 2);
				cout << "HP - " << h.getAtk() * (df + 1) << "  ";
			}
			gotoxy(x++, y++);
			cout << " ";
			Sleep(50);
			gotoxy(x++, y++);
			cout << " ";
			Sleep(50);
			c.getDamage(h.getAtk() * (df + 1));
		}
		void creatureAttake(Hero& h, Creature& cr) 
		{
			string c = cr.getIcon();
			if (c == "Ｌ") //slime
			{
				gotoxy(19, 3); cout << "    __ __   O " << endl;
				gotoxy(19, 4); cout << "  _/  V  \\___  # " << endl;
				gotoxy(19, 5); cout << " C    |  |   \\ " << endl;
				gotoxy(19, 6); cout << " \\  ___ w  _ C\\ " << endl;
				gotoxy(19, 7); cout << " /_/   \\__/ \\__\\ " << endl;

				Sleep(50);
				gotoxy(19, 3); cout << "     __ __   O" << endl;
				gotoxy(19, 4); cout << "   _/  V  \\___  #" << endl;
				gotoxy(19, 5); cout << "  C    |  |   \\" << endl;
				gotoxy(19, 6); cout << "  \\  ___ w  _ C\\" << endl;
				gotoxy(19, 7); cout << "  /_/   \\__/ \\__\\" << endl;
			}
			else if (c == "Ｂ") //bat
			{
				gotoxy(19, 3); cout << "        ^     ^ " << endl;
				gotoxy(19, 4); cout << "       / \\___/ \\ " << endl;
				gotoxy(19, 5); cout << "  ^___/  |  |   \\____^ " << endl;
				gotoxy(19, 6); cout << " /        ___         \\ " << endl;
				gotoxy(19, 7); cout << " \\ /\\     V V      /\\ / " << endl;
				gotoxy(19, 8); cout << "  V  V￣\\_____/￣ V  V " << endl;

				Sleep(50);
				gotoxy(19, 3); cout << "         ^     ^" << endl;
				gotoxy(19, 4); cout << "        / \\___/ \\" << endl;
				gotoxy(19, 5); cout << "   ^___/  |  |   \\____^" << endl;
				gotoxy(19, 6); cout << "  /        ___         \\" << endl;
				gotoxy(19, 7); cout << "  \\ /\\     V V      /\\ /" << endl;
				gotoxy(19, 8); cout << "   V  V￣\\_____/￣ V  V" << endl;

				int x = 0, y = 8;
				gotoxy(x, y);
				cout << "\\\\\\";
				gotoxy(x + 1, y + 1);
				cout << "\\\\\\";

				Sleep(50);
				for (int i = 0; i < 5; i++)
				{
					gotoxy(x++, y++);
					cout << "   ";
					gotoxy(x + 1, y + 1);
					cout << "\\\\\\";
					Sleep(50);
					gotoxy(25, 2);
				}
				gotoxy(x++, y++);
				cout << "      ";
				Sleep(50);
				gotoxy(x++, y++);
				cout << "      ";
			}
			else if (c == "Ｚ") //zombie
			{
				gotoxy(19, 3); cout << "   ____    " << endl;
				gotoxy(19, 4); cout << "  /o O \\  " << endl;
				gotoxy(19, 5); cout << "  \\口__/ " << endl;
				gotoxy(19, 6); cout << "  __||__ " << endl;
				gotoxy(19, 7); cout << " /  || / " << endl;
				gotoxy(19, 8); cout << "   _||_ " << endl;
				gotoxy(19, 9); cout << "  |    | " << endl;
				Sleep(50);
				gotoxy(20, 3); cout << "           " << endl;
				gotoxy(20, 4); cout << "   ____    " << endl;
				gotoxy(20, 5); cout << "  /o O \\  " << endl;
				gotoxy(20, 6); cout << "  \\口__/ " << endl;
				gotoxy(20, 7); cout << "  __||__ " << endl;
				gotoxy(20, 8); cout << " /  || / " << endl;
				gotoxy(20, 9); cout << "   _||_ " << endl;
				gotoxy(20, 10); cout << "  |    | " << endl;
				Sleep(50);
				gotoxy(15, 10); cout << "OUCH!";
				Sleep(300);
			}
			else if (c == "Ｅ") //skeleton
			{
				gotoxy(15, 5); cout << "     /" << endl;
				gotoxy(15, 6); cout << "    /" << endl;
				gotoxy(15, 7); cout << " _ /_" << endl;
				gotoxy(15, 8); cout << "/ / /" << endl;
				Sleep(100);

				int x = 14, y = 5;
				for (int i = 0; i < 5; i++)
				{
					gotoxy(x, y); cout << "       " << endl;
					gotoxy(x, y + 1); cout << "     /" << endl;
					gotoxy(x, y + 2); cout << "    / " << endl;
					gotoxy(x, y + 3); cout << " _ /_ " << endl;
					gotoxy(x, y + 4); cout << "/ / / " << endl;
					x--;
					y++;
					Sleep(100);
				}
			}
			else if (c == "Ｐ") //spider
			{
				int x = 4, y = 8;

				for (int i = 0; i < 2; i++)
				{
					gotoxy(x, y);
					cout << "/";
					Sleep(50);
					gotoxy(x - 1, y + 1);
					cout << "/";
					Sleep(50);
					cout << "_";
					Sleep(50);
					cout << "_";
					Sleep(50);
					gotoxy(x + 1, y + 2);
					cout << "/";
					Sleep(50);
					gotoxy(x, y + 3);
					cout << "/";
					Sleep(50);
					x += 3;
				}
			}

			h.damage(cr.getAtk());
			gotoxy(2, 8);
			cout << "HP - " << cr.getAtk() << "  ";
		}

		void getPoint(Hero& h)
		{
			string mons[5] = { "史萊姆", "蝙蝠　", "殭屍　", "骷髏　", "蜘蛛　" };
			for (int i = 0; i < 5; i++)
			{
				cout << mons[i] << " x ";
				cout << 0;
				for (int j = 0; j < all_killed[i]; j++) 
				{
					gotoxy(9, i);
					cout << j + 1;
					Sleep(100);
				}
				cout << endl;
			}
			cout << "英雄剩餘血量: " << h.getHealth() << endl;
			int point = all_killed[0] * 2 + all_killed[1] * 4 + all_killed[2] * 30  + all_killed[3] * 45 + all_killed[4] * 600;
			point += h.getHealth();
			cout << "總獲得分數: " << point << endl << endl;
			getAch(point, h);
		}
		void getAch(int point, Hero& h) 
		{
			string Ach[] = { "屠殺者", "和平主義者", "無敵英雄", "理論最大值", "全部答三星題，你是鬼吧", "超級知識王", "不滅勇者" };
			int getAch[7] = { 0 };
			bool noAch = true;
			int kill = 0;
			for (int i = 0; i < 5; i++) 
			{
				kill += all_killed[i];
			}
			if (kill == 19) getAch[0] = 1; //全敵人擊殺
			if (kill == 10) getAch[1] = 1; //最低限度擊殺
			if (h.getAtk() == 999) getAch[2] = 1; //達到999級
			if (point == 2475) getAch[3] = 1; //拿到理論最高分數
			if (three_star) getAch[4] = 1; //全部題目只做三星題
			if (kill == 10 && (point == 1146 || point == 1106 || point == 821)) getAch[5] = 1; //最低限度擊殺 & 最小限度被攻擊
			if (h.getLevel() == 3) getAch[6] = 1; //英雄3級通關

			for (int i = 0; i < 6; i++) 
			{
				if (getAch[i] == 1) 
				{
					cout << "獲得成就: " << Ach[i] << endl;
					noAch = false;
				}
			}

			if (noAch) cout << "獲得成就:\n無獲得成就。\n";
		}

		void printMenu() 
		{
			PlaySound(TEXT("BGM.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			while (1) 
			{
				gotoxy(0, 0); cout << " ＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿ " << endl;
				gotoxy(0, 1); cout << "|   *             *            |" << endl;
				gotoxy(0, 2); cout << "|   地    宮   知    識   王 * |" << endl;
				gotoxy(0, 3); cout << "|      *        *        *     |" << endl;
				gotoxy(0, 4); cout << " ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣" << endl;
				gotoxy(0, 5); cout << "     按任意鍵開始遊戲. . ." << endl;
				if (_kbhit()) break;
				Sleep(500);
				gotoxy(0, 0); cout << " ＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿ " << endl;
				gotoxy(0, 1); cout << "| *         *          *       |" << endl;
				gotoxy(0, 2); cout << "|*  地    宮   知    識   王   |" << endl;
				gotoxy(0, 3); cout << "|          *         *         |" << endl;
				gotoxy(0, 4); cout << " ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣" << endl;
				gotoxy(0, 5); cout << "     按任意鍵開始遊戲. . ." << endl;
				if (_kbhit()) break;
				Sleep(500);
				gotoxy(0, 0); cout << " ＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿ " << endl;
				gotoxy(0, 1); cout << "|        *                   * |" << endl;
				gotoxy(0, 2); cout << "|   地    宮   知    識   王   |" << endl;
				gotoxy(0, 3); cout << "|  *               *         * |" << endl;
				gotoxy(0, 4); cout << " ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣" << endl;
				gotoxy(0, 5); cout << "     按任意鍵開始遊戲. . ." << endl;
				if (_kbhit()) break;
				Sleep(500);
			}
			char c;
			c = _getch();
			system("cls");
		}

		//讀取題庫用
		vector<string> _csv(string s)
		{
			vector<string> arr;
			istringstream delim(s);
			string token;
			int c = 0;
			while (getline(delim, token, ','))
			{
				arr.push_back(token);
				c++;
			}
			return arr;
		}

		void readQuiz()
		{
			int type = 0;
			int star = 0;
			int quiz = 0;
			string str;
			ifstream fin;

			fin.open("地宮全題庫180題.csv");
			getline(fin, str); //讀走第一行
			getline(fin, str); //讀走第二行
			getline(fin, str); //讀走第行
			while (!fin.eof())
			{
				while (getline(fin, str))
				{
					vector<string> f_Read = _csv(str);

					//讀到的是空白行
					if (f_Read[0].empty()) continue;

					//讀到的是題目類型
					if (f_Read[0] == types[type + 1])
					{
						type++;
						getline(fin, str);
						quiz = 0;
						break;
					}

					//讀到的是星星數的內容	
					if (f_Read[0] == stars[star + 1])
					{
						star++;
						quiz = 0;
						continue;
					}

					for (int i = 0; i < f_Read.size(); i++) 
					{
						for (int j = 0; j < f_Read[i].size(); j++) 
						{
							if (f_Read[i][j] == ';') f_Read[i][j] = ',';
						}
					}

					qs[type][star][quiz].que = f_Read[0];
					qs[type][star][quiz].ans[0] = f_Read[1];
					qs[type][star][quiz].ans[1] = f_Read[2];
					qs[type][star][quiz].ans[2] = f_Read[3];
					qs[type][star][quiz].ans[3] = f_Read[4];
					qs[type][star][quiz].answer = int(f_Read[5][0] - '1');

					quiz++;
				}
				star = 0;
			}
			fin.close();
		}
	};

}