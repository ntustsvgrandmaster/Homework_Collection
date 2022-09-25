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
		int answer;		//���D�ت�����
		string que;		//���D�ت��D�رԭz
		string ans[4];	//���D�ت��ﶵ
	};

	class GameBoard {
	private:
		Mode mode;
		char board[30][30];
		string types[6] = { "�ƾ�", "�^��", "�a�z", "���v", "�q��", "�ͬ�" };
		string stars[3] = { "�@�P", "�G�P", "�T�P" };
		Question qs[6][3][10]; //6�����B3���P�B�@���P10�D
		int quized[6][3][10] = { 0 };
		int randType[3] = { 0, 1, 2 }; //�T�����פ��O�������A��rand��
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

		//�����]�p��
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
		//�����]�p��

		void Guide(Hero& h, Creature& c) //guide battle
		{
			printCutscenes();
			system("cls");
			printBoard(h, c);
			string word = "\n���ͪ��v�ܩi�X�{�F�A\n�a�A�����z���˥��a�I\n\n";
			cout << endl;
			for (int i = 0; i < word.size(); i++) 
			{
				cout << word[i];
				Sleep(50);
			}
			cout << "�����N����i�J�԰� . . ." ;
			system("pause>nul");

			system("cls");
			printBoard(h, c);
			word = "\n�ϥ�aswd�Ӿޱ��b�Y��V�A�åB�ϥ�enter����\n\n";	
			cout << endl;
			cout << endl;
			for (int i = 0; i < word.size(); i++)
			{
				cout << word[i];
				Sleep(50);
			}
			cout << "�����N����i�J�԰� . . .";
			system("pause>nul");

			char ch;
			bool end = false;

			//��ܤ@�P�B���T���ת��d��		
			while (1)
			{
				while (!end)
				{
					system("cls");
					printBoard(h, c);
					gotoxy(1, 18);
					SetColor(225);
					cout << "�@�P  �ƾ�";
					SetColor();
					inputing(end);
				}
				end = false;
				if (df == 0) break;
			}
			tp = randType[df]; //���� = �H����X���������A��w���׹���������
			mode = Mode::ANS;
			while (1)
			{
				while (!end)
				{
					system("cls");
					printBoard(h, c);
					gotoxy(25, 22);
					SetColor(225);
					cout << "�|";
					SetColor();
					inputing(end);
				}
				end = false;
				if (ans == 3) break;
			}
			heroAttack(h, c);
			creatureAttake(h, c);

			gotoxy(0, 24);
			word = "���ܥ��T�����׮ɡA�i�H�����ĤH�åB�d������O\n�P�ɡA�b�^�X������|�����誺����";
			for (int i = 0; i < word.size(); i++)
			{
				cout << word[i];
				Sleep(50);
			}
			system("pause>nul");

			//��ܤT�P�B���~���ת��d��
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
					cout << "�T�P  �a�z";
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
					cout << "�Ȭw";
					SetColor();
					inputing(end);
				}
				end = false;
				if (ans == 0) break;
			}
			creatureAttake(h, c);

			gotoxy(0, 24);
			word = "���ܿ��~�����׮ɡA�����N�L�k�R�����åB�����ˮ`�C";			
			for (int i = 0; i < word.size(); i++)
			{
				cout << word[i];
				Sleep(50);
			}
			system("pause>nul");

			//��ܤT�P�B���T���ת��d��
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
					cout << "�G�P  �^��";
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
			word = "��ܪ����׶V���A������誺�ˮ`�]�|����";
			for (int i = 0; i < word.size(); i++)
			{
				cout << word[i];
				Sleep(50);
			}
			system("pause>nul");
			//�԰�������r����

			SetColor(63);
			gotoxy(10, 5); cout << " __________________________ ";
			gotoxy(10, 6); cout << "|�԰��ӧQ�I�����N��^��a�c|";
			gotoxy(10, 7); cout << " �áááááááááááá� ";
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
				//�������
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
				//��ܵ���
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

				tp = df = ans = 0; //���s�ﶵ
			}
			if (h.getHealth() <= 0) 
			{
				SetColor(63);
				gotoxy(10, 5); cout << " ____________________________ ";
				gotoxy(10, 6); cout << "|�A�w�g���F�I�����N��^��a�c|";
				gotoxy(10, 7); cout << " �ááááááááááááá� ";
				SetColor();
				system("pause>nul");
				system("cls");
			}
			else 
			{
				SetColor(63);
				gotoxy(10, 5); cout << " __________________________ ";
				gotoxy(10, 6); cout << "|�԰��ӧQ�I�����N��^��a�c|";
				gotoxy(10, 7); cout << " �áááááááááááá� ";
				SetColor();
				if (c.getIcon() == "��") 
				{
					all_killed[0]++;
				}
				else if (c.getIcon() == "��")
				{
					all_killed[1]++;
				}
				else if (c.getIcon() == "��")
				{
					all_killed[2]++;
				}
				else if (c.getIcon() == "��")
				{
					all_killed[3]++;
				}
				else if (c.getIcon() == "��")
				{
					all_killed[4]++;
				}
				system("pause>nul");
				system("cls");
			}
		}

		void printCutscenes() //�L���ʵe
		{
			Sleep(50);
			int x = 0, y = 0;
			int dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
			int di = 0;
			int visit[10][10] = { 0 };
			string wall = "��";

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

			//�L�^���ϼ�
			cout << "            ^" << endl;
			cout << "           |||" << endl;
			cout << " ___/�á�\\ |||" << endl;
			cout << "|  | HERO ||||" << endl;
			cout << "|   \\    /==O==" << endl;
			cout << "\\__/ �á�   |" << endl << endl;

			gotoxy(2, 8);
			cout << "HP : " << h.getHealth();
			gotoxy(25, 2);
			cout << "HP : " << c.getHealth();
			gotoxy(0, 15);
			cout << "=================================================" << endl;

			if (mode == Mode::DIFF) //����D������
			{
				cout << " �п���D������\n" << endl;
				for (int i = 0; i < 3; i++)
				{
					if (df == i) cout << ">";
					else cout << " ";

					cout << stars[i] << "  " << types[randType[i]] << endl;
				}
				cout << endl;
			}
			else if (mode == Mode::ANS) //��ܵ���
			{
				cout << "Q:                                            \n"
					 << qs[tp][df][qz].que << endl;
				cout << "=================================================\n";
				cout << " �п�ܵ���\n" << endl;
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

		void printCreature(string c) //c = creature��icon�A�|�̾ڤ��P��icon�L�X���P���Ǫ�
		{
			if (c == "��") //slime
			{
				gotoxy(20, 3); cout << "    __ __   O" << endl;
				gotoxy(20, 4); cout << "  _/  V  \\___  #" << endl;
				gotoxy(20, 5); cout << " C    |  |   \\" << endl;
				gotoxy(20, 6); cout << " \\  ___ w  _ C\\" << endl;
				gotoxy(20, 7); cout << " /_/   \\__/ \\__\\" << endl;
			}
			else if (c == "��") //bat
			{
				gotoxy(20, 3); cout << "        ^     ^" << endl;
				gotoxy(20, 4); cout << "       / \\___/ \\" << endl;
				gotoxy(20, 5); cout << "  ^___/  |  |   \\____^" << endl;
				gotoxy(20, 6); cout << " /        ___         \\" << endl;
				gotoxy(20, 7); cout << " \\ /\\     V V      /\\ /" << endl;
				gotoxy(20, 8); cout << "  V  V��\\_____/�� V  V" << endl;
			}
			else if (c == "��") //zombie
			{
				gotoxy(20, 3); cout << "   ____   " << endl;
				gotoxy(20, 4); cout << "  /o O \\ " << endl;
				gotoxy(20, 5); cout << "  \\�f__/" << endl;
				gotoxy(20, 6); cout << "  __||__" << endl;
				gotoxy(20, 7); cout << " /  || /" << endl;
				gotoxy(20, 8); cout << "   _||_" << endl;
				gotoxy(20, 9); cout << "  |    |" << endl;
			}
			else if (c == "��") //skeleton
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
			else if (c == "��") //spider
			{
				gotoxy(20, 3); cout << "    ^___^" << endl;
				gotoxy(20, 4); cout << "   /o o o\\" << endl;
				gotoxy(20, 5); cout << "  /  o o  \\" << endl;
				gotoxy(20, 6); cout << "  \\ o o o�����áá�" << endl;
				gotoxy(20, 7); cout << "   V�á�V  ########|" << endl;
				gotoxy(20, 8); cout << "  / | | \\��__|__\\��" << endl;
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

		void heroAttack(Hero& h, Creature& c) //�����ʵe 
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
			if (c == "��") //slime
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
			else if (c == "��") //bat
			{
				gotoxy(19, 3); cout << "        ^     ^ " << endl;
				gotoxy(19, 4); cout << "       / \\___/ \\ " << endl;
				gotoxy(19, 5); cout << "  ^___/  |  |   \\____^ " << endl;
				gotoxy(19, 6); cout << " /        ___         \\ " << endl;
				gotoxy(19, 7); cout << " \\ /\\     V V      /\\ / " << endl;
				gotoxy(19, 8); cout << "  V  V��\\_____/�� V  V " << endl;

				Sleep(50);
				gotoxy(19, 3); cout << "         ^     ^" << endl;
				gotoxy(19, 4); cout << "        / \\___/ \\" << endl;
				gotoxy(19, 5); cout << "   ^___/  |  |   \\____^" << endl;
				gotoxy(19, 6); cout << "  /        ___         \\" << endl;
				gotoxy(19, 7); cout << "  \\ /\\     V V      /\\ /" << endl;
				gotoxy(19, 8); cout << "   V  V��\\_____/�� V  V" << endl;

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
			else if (c == "��") //zombie
			{
				gotoxy(19, 3); cout << "   ____    " << endl;
				gotoxy(19, 4); cout << "  /o O \\  " << endl;
				gotoxy(19, 5); cout << "  \\�f__/ " << endl;
				gotoxy(19, 6); cout << "  __||__ " << endl;
				gotoxy(19, 7); cout << " /  || / " << endl;
				gotoxy(19, 8); cout << "   _||_ " << endl;
				gotoxy(19, 9); cout << "  |    | " << endl;
				Sleep(50);
				gotoxy(20, 3); cout << "           " << endl;
				gotoxy(20, 4); cout << "   ____    " << endl;
				gotoxy(20, 5); cout << "  /o O \\  " << endl;
				gotoxy(20, 6); cout << "  \\�f__/ " << endl;
				gotoxy(20, 7); cout << "  __||__ " << endl;
				gotoxy(20, 8); cout << " /  || / " << endl;
				gotoxy(20, 9); cout << "   _||_ " << endl;
				gotoxy(20, 10); cout << "  |    | " << endl;
				Sleep(50);
				gotoxy(15, 10); cout << "OUCH!";
				Sleep(300);
			}
			else if (c == "��") //skeleton
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
			else if (c == "��") //spider
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
			string mons[5] = { "�v�ܩi", "�����@", "�L�͡@", "�u�\�@", "�j��@" };
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
			cout << "�^���Ѿl��q: " << h.getHealth() << endl;
			int point = all_killed[0] * 2 + all_killed[1] * 4 + all_killed[2] * 30  + all_killed[3] * 45 + all_killed[4] * 600;
			point += h.getHealth();
			cout << "�`��o����: " << point << endl << endl;
			getAch(point, h);
		}
		void getAch(int point, Hero& h) 
		{
			string Ach[] = { "�O����", "�M���D�q��", "�L�ĭ^��", "�z�׳̤j��", "�������T�P�D�A�A�O���a", "�W�Ū��Ѥ�", "�����i��" };
			int getAch[7] = { 0 };
			bool noAch = true;
			int kill = 0;
			for (int i = 0; i < 5; i++) 
			{
				kill += all_killed[i];
			}
			if (kill == 19) getAch[0] = 1; //���ĤH����
			if (kill == 10) getAch[1] = 1; //�̧C��������
			if (h.getAtk() == 999) getAch[2] = 1; //�F��999��
			if (point == 2475) getAch[3] = 1; //����z�׳̰�����
			if (three_star) getAch[4] = 1; //�����D�إu���T�P�D
			if (kill == 10 && (point == 1146 || point == 1106 || point == 821)) getAch[5] = 1; //�̧C�������� & �̤p���׳Q����
			if (h.getLevel() == 3) getAch[6] = 1; //�^��3�ųq��

			for (int i = 0; i < 6; i++) 
			{
				if (getAch[i] == 1) 
				{
					cout << "��o���N: " << Ach[i] << endl;
					noAch = false;
				}
			}

			if (noAch) cout << "��o���N:\n�L��o���N�C\n";
		}

		void printMenu() 
		{
			PlaySound(TEXT("BGM.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			while (1) 
			{
				gotoxy(0, 0); cout << " �ġġġġġġġġġġġġġġ� " << endl;
				gotoxy(0, 1); cout << "|   *             *            |" << endl;
				gotoxy(0, 2); cout << "|   �a    �c   ��    ��   �� * |" << endl;
				gotoxy(0, 3); cout << "|      *        *        *     |" << endl;
				gotoxy(0, 4); cout << " �áááááááááááááá�" << endl;
				gotoxy(0, 5); cout << "     �����N��}�l�C��. . ." << endl;
				if (_kbhit()) break;
				Sleep(500);
				gotoxy(0, 0); cout << " �ġġġġġġġġġġġġġġ� " << endl;
				gotoxy(0, 1); cout << "| *         *          *       |" << endl;
				gotoxy(0, 2); cout << "|*  �a    �c   ��    ��   ��   |" << endl;
				gotoxy(0, 3); cout << "|          *         *         |" << endl;
				gotoxy(0, 4); cout << " �áááááááááááááá�" << endl;
				gotoxy(0, 5); cout << "     �����N��}�l�C��. . ." << endl;
				if (_kbhit()) break;
				Sleep(500);
				gotoxy(0, 0); cout << " �ġġġġġġġġġġġġġġ� " << endl;
				gotoxy(0, 1); cout << "|        *                   * |" << endl;
				gotoxy(0, 2); cout << "|   �a    �c   ��    ��   ��   |" << endl;
				gotoxy(0, 3); cout << "|  *               *         * |" << endl;
				gotoxy(0, 4); cout << " �áááááááááááááá�" << endl;
				gotoxy(0, 5); cout << "     �����N��}�l�C��. . ." << endl;
				if (_kbhit()) break;
				Sleep(500);
			}
			char c;
			c = _getch();
			system("cls");
		}

		//Ū���D�w��
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

			fin.open("�a�c���D�w180�D.csv");
			getline(fin, str); //Ū���Ĥ@��
			getline(fin, str); //Ū���ĤG��
			getline(fin, str); //Ū���Ħ�
			while (!fin.eof())
			{
				while (getline(fin, str))
				{
					vector<string> f_Read = _csv(str);

					//Ū�쪺�O�ťզ�
					if (f_Read[0].empty()) continue;

					//Ū�쪺�O�D������
					if (f_Read[0] == types[type + 1])
					{
						type++;
						getline(fin, str);
						quiz = 0;
						break;
					}

					//Ū�쪺�O�P�P�ƪ����e	
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