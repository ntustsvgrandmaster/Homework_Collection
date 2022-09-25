#pragma once
#include "User.h"
#include "Viewer.h"
#include "Game.h"
#include <conio.h>
#include <io.h>      //��o�ɮצW��
#include <fstream>
#include <algorithm>
#include <direct.h>		//������Ƨ������Y��

enum class BoardState {
	MENU,           //�D���
	SELECT_BOARD,   //��ܪ���
	BOARD,          //�d�ݪ��� (���O�K����D�B�K��ɶ��B�o��̵���)
	POST            //�d�ݶK�夺�e
};

class BoardManager {
private:
	std::vector<Board*> boards;
	std::vector<User*> users;
	Viewer viewer;
	int current_User; // guest = 0;
	int current_Board;
	int current_Post;
	BoardState state;
	bool userMoved = false;
	bool lastIsRight; //���ܤW����J���b�K�O�_���T

	const int MENU_SIZE = 5; //�\���檺�\���
public:
	BoardManager();
	void logoutWriteToFile(int currentUser);
	void printContent();
	void setMoved(bool m) { this->userMoved = m; }
	bool isMoved() { return this->userMoved; }
	int  getTheBiggestID()
	{
		int lMax = -1;
		for (int i = MENU_SIZE; i < this->boards.size(); i++)
		{
			vector<Post*>::iterator h, b;
			h = boards[i]->getAllPostBegin();
			b = boards[i]->getAllPostEnd();
			for (; h != b; h++)
			{
				lMax = max(lMax, (*h)->getPostID());
			}
		}
		try
		{
			if (lMax == -1) throw "ID does not exist!";
			else
			{
				return lMax;
			}
		}
		catch (string n) { cout << n << endl; }
	}
};

void getFiles(string path, vector<string>& files)
{
	//�ɮױ���N�X  
	long   hFile = 0;
	//�ɮ׸�T  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�p�G�O�ؿ�,���N��  
				//�p�G���O,�[�J�C��  
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					files.push_back(fileinfo.name);
				}
			}
			else
			{
				files.push_back(fileinfo.name);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

bool compare(Post* s1, Post* s2)
{
	if (s1->getPostID() < s2->getPostID())
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

BoardManager::BoardManager() {
	this->current_User = 0;
	this->current_Board = MENU_SIZE;
	this->current_Post = 0;
	this->state = BoardState::MENU;
	this->lastIsRight = true;
	this->users.push_back(new Guest);
	ifstream fin;
	fin.open("./User/all_users.txt");
	char type;
	string userName, passWord;
	while (fin >> type >> userName >> passWord)
	{
		if (type == 'A') users.push_back(new Administrator(userName, passWord));
		else if (type == 'M') users.push_back(new Member(userName, passWord));
	}
	fin.close();

	/**********************************  Ū�J�ɮװ���l�]�w ***************************************/
	//Ū�Jboard
	string boardFilePath = ".\\Board";
	vector<string> boardFiles;
	//����Ӹ��|�U���Ҧ��ɮת��W�١A��Ƨ��S�����ɦW��!
	getFiles(boardFilePath, boardFiles);
	int boardSize = boardFiles.size();
	for (int i = 0; i < boardSize; i++)		//�C�@�Ӱj��N�O�C�@board
	{
		boards.push_back(new Board);
		boards[i]->setName(boardFiles[i]);

		//Ū�Jpost
		string test = boardFiles[i];
		string postFilePath = ".\\Board\\" + test;		//test = board name
		vector<string> postFiles;
		//����Ӹ��|�U���Ҧ��ɮת��W�١Apost�����ɦW.txt ��!
		getFiles(postFilePath, postFiles);
		int postSize = postFiles.size();
		for (int k = 0; k < postSize; k++)
		{
			string a;
			for (int j = 0; postFiles[k][j] != '.'; j++)
			{
				a = a + postFiles[k][j];        //�h�����ɦW�C
			}
			int b = 0;
			for (int n = 0; n < a.length(); n++)
			{
				b = b * 10 + a[n] - '0';
			}


			Post* p = new Post;
			boards[i]->pushAllPost(p);
			boards[i]->pushPostIDs(b);
			boards[i]->getPost(k)->setPostID(b);
			boards[i]->setPostNum(boards[i]->getPostNum() + 1);
			ifstream pFile(".\\Board\\" + test + "\\" + postFiles[k]);
			string title;
			getline(pFile, title);
			boards[i]->getPost(k)->setPostTitle(title);
			string author;
			getline(pFile, author);
			boards[i]->getPost(k)->setPostAuthor(author);
			string content;
			while (1)
			{
				getline(pFile, content);
				if (content == "*************************contentend*********************************") break;
				boards[i]->getPost(k)->setPostContent(content);
			}
			int upNum;
			pFile >> upNum;
			boards[i]->getPost(k)->setPostUpNum(upNum);
			int commentSeq;
			int upOrDown;
			string commentName;
			string commentContent;
			while (1)		//Ū�J�d��
			{
				pFile >> commentSeq;
				if (commentSeq == -99999) break;
				Comment* sCom = new Comment;
				sCom->seqence = commentSeq;
				pFile >> upOrDown;
				sCom->upOrDown = upOrDown;
				pFile >> commentName;
				sCom->commentName = commentName;
				getline(pFile, commentContent);
				sCom->commentContent = commentContent;
				boards[i]->getPost(k)->pushAllcomment(sCom);
			}
			//Ūpost ����
			pFile.close();		//�����o��post
		}
		/******** �Npost ���Ӯɶ����ǱƧ� *********/
		vector<Post*>::iterator h, b;
		h = boards[i]->getAllPostBegin();
		b = boards[i]->getAllPostEnd();
		sort(h, b, compare);
		/******************************************/
	}
}

void BoardManager::logoutWriteToFile(int currentUser)
{
	ofstream outFile1;
	/************************ �g�J�ϥΪ̱b�K�� *************************/
	outFile1.open(".\\User\\all_users.txt", ios::out);   //�}�� all_users.txt�A�]�w����X�A�æP�ɲM�Ť��e�C
	for (int i = 1; i < users.size(); i++)
	{
		if (users[i]->getPermission() == 1)	outFile1 << "A" << " ";
		else if (users[i]->getPermission() == 2) outFile1 << "M" << " ";
		outFile1 << users[i]->getName() << " " << users[i]->getPass() << endl;
	}
	outFile1.close();
	/*******************************************************************/
	/************** �g�J�����ϥΪ̸�� ***************/
	ofstream outFile2;
	outFile2.open(".\\User\\" + users[currentUser]->getName() + ".txt", ios::out);		//���s�b�N�Ы�  �ϥΪ̦W��.txt�C
	outFile2 << users[currentUser]->getCoin() << endl;
	for (int j = 0; j < users[currentUser]->getPostnum(); j++)		//�����ƧǪ��g�J
	{
		outFile2 << users[currentUser]->getThisPost(j)->boardName << " " << users[currentUser]->getThisPost(j)->postsID << endl;
	}
	outFile2 << "/********myPostEnd*******/" << endl;
	for (int j = 0; j < users[currentUser]->getMailAmt(); j++)
	{
		outFile2 << users[currentUser]->getThisMail(j)->receiver << endl;
		outFile2 << users[currentUser]->getThisMail(j)->title << endl;
		for (int k = 0; k < users[currentUser]->getThisMail(j)->content.size(); k++)
		{
			outFile2 << users[currentUser]->getThisMail(j)->content[k] << endl;
		}
		outFile2 << "/*EndOfMail*/" << endl;
	}
	outFile2.close();
	/***************************************************/
	/********** �ݪO �� �K�媺�g�J ************/
	for (int i = 0; i < this->boards.size(); i++)
	{
		//�P�_�o��board����Ƨ��s���s�b�A���s�b�h�ЫءC
		string n = ".\\Board\\" + boards[i]->getName();
		if (0 != _access(n.c_str(), 0))
		{
			// if this folder not exist, create a new one.
			_mkdir(n.c_str());
		}
		for (int j = 0; j < this->boards[i]->getPostNum(); j++)
		{
			ofstream outPostFile;
			outPostFile.open(".\\Board\\" + boards[i]->getName() + "\\" + to_string(boards[i]->getPost(j)->getPostID()) + ".txt", ios::out);
			outPostFile << boards[i]->getPost(j)->getPostTitle() << endl;
			outPostFile << boards[i]->getPost(j)->getPostAuthor() << endl;
			for (int k = 0; k < boards[i]->getPost(j)->getContentLines(); k++)
			{
				outPostFile << boards[i]->getPost(j)->getPostContent(k) << endl;
			}
			outPostFile << "*************************contentend*********************************" << endl;
			outPostFile << boards[i]->getPost(j)->getPostUpNum() << endl;
			for (int k = 0; k < boards[i]->getPost(j)->getCommentAmt(); k++)
			{
				outPostFile << boards[i]->getPost(j)->getComment(k)->seqence << " " << boards[i]->getPost(j)->getComment(k)->upOrDown
					<< " " << boards[i]->getPost(j)->getComment(k)->commentName << " " << boards[i]->getPost(j)->getComment(k)->commentContent << endl;
			}
			outPostFile << "-99999" << endl;
			outPostFile.close();
		}
	}
}

void BoardManager::printContent()
{
	using std::cin;
	using std::cout;
	using std::endl;
	if (state == BoardState::MENU)
	{
		viewer.printMenu(userMoved);

		SetColor(207);
		if (!lastIsRight) cout << "�ϥΪ̦W�٩αK�X���~�I�Э��s��J\n";
		SetColor();

		std::string username, password;

		cout << "UserName: ";
		cin >> username;

		//�]�w���X�ȼҦ�
		if (username == "guest")
		{
			this->userMoved = true;
			lastIsRight = true;
			state = BoardState::SELECT_BOARD;
			current_User = 0;

			return;
		}
		//���U�s�b��
		else if (username == "new")
		{
			std::string newUserN;
			bool validUserN = false;
			while (!validUserN)
			{
				cout << "�п�J�n���U���b��: ";
				cin >> newUserN;
				//�ˬd���S���M��L�H�Ĭ�
				bool collide = false;
				for (int i = 0; i < users.size(); i++)
				{
					if (newUserN == users[i]->getName()) collide = true;
				}
				if (!collide)
				{
					validUserN = true;
				}
				else
				{
					cout << "���ϥΪ̤w�s�b�A";
				}
			}
			cout << "�п�J�n�ϥΪ��K�X: ";
			cin >> password;
			users.push_back(new Member(newUserN, password));
			lastIsRight = true;
			int n = users.size() - 1;
			this->logoutWriteToFile(n);
			return;
		}

		cout << "PassWord: ";
		SetColor(255);
		cin >> password;
		SetColor();

		//�h�M�������user�A���ˬdpassword
		bool foundUser = false;
		for (; current_User < users.size(); current_User++)
		{
			if (users[current_User]->getName() == username)
			{
				if (users[current_User]->getPass() == password)
				{
					foundUser = true;
				}
				break;
			}
		}

		if (foundUser)
		{
			this->userMoved = true;
			lastIsRight = true;
			state = BoardState::SELECT_BOARD;

			if (!users[current_User]->loaded)
			{
				/*Ū�J�ϥΪ̸�T*/
				ifstream fin;
				fin.open("./User/" + username + ".txt");
				int coin, id;
				fin >> coin;
				users[current_User]->setCoin(coin);
				myPost p;
				while (fin >> p.boardName) {
					if (p.boardName == "/********myPostEnd*******/") break;
					else fin >> p.postsID;
					users[current_User]->newPost(p);
				}
				string receiv, content;
				while (fin >> receiv)
				{
					Conversation c;
					c.receiver = receiv;
					getline(fin, c.title); //Ū���ť�
					getline(fin, c.title);
					while (1)
					{
						getline(fin, content);
						if (content == "/*EndOfMail*/")
						{
							break;
						}
						else c.content.push_back(content);
					}
					users[current_User]->newConv(c);
					while (!c.content.empty())c.content.pop_back();
				}
				fin.close();
				users[current_User]->loaded = true;
				/*Ū�J�ϥΪ̸�T����*/
			}
		}
		else
		{
			lastIsRight = false;
			current_User = 0;
		}
	}
	else if (state == BoardState::SELECT_BOARD)
	{
		system("cls");
		if (current_User != 0)
		{
			std::cout << "�w��ϥΪ� " << users[current_User]->getName() << " �^��!\n";
			viewer.printSelector(users[current_User]->getPermission(), boards, current_Board, MENU_SIZE);
		}
		else
		{
			std::cout << "�w��ϥ�PTT�X�Ȫ�!\n";
			viewer.printSelector(3, boards, current_Board, MENU_SIZE);
		}

		char c;
		c = _getch();
		if (c == 'w')
		{
			if (current_Board != MENU_SIZE && current_Board > 0)
			{
				current_Board--;
			}
		}
		else if (c == 's')
		{

			if (current_Board != MENU_SIZE - 1 && current_Board < boards.size() - 1 + MENU_SIZE) //+MENU_SIZE���\���檺����
			{
				current_Board++;
			}
		}
		else if (c == 'a' && current_User != 0)
		{
			if (current_Board < MENU_SIZE)
			{
				current_Board = MENU_SIZE;
			}
		}
		else if (c == 'd' && current_User != 0)
		{
			if (current_Board >= MENU_SIZE)
			{
				current_Board = 0;
			}
		}
		else if (c == 'y' && users[current_User]->getPermission() == 1 && current_Board >= MENU_SIZE)
		{
			//�R���ݪO
			/*�O�@���*/
			char check;
			SetColor(225); cout << "�T�w�n�R���ݪO " << boards[current_Board - MENU_SIZE]->getName() << " ��? (y/n): "; SetColor();
			while (cin >> check)
			{
				if (check == 'y')
				{
					vector<Board*>::iterator it;
					it = boards.begin() + (current_Board - MENU_SIZE);
					boards.erase(it);
					current_Board = MENU_SIZE;
					break;
				}
				else if (check == 'n')
				{
					break;
				}
			}
			/*�O�@���*/
		}
		else if (c == 'u' && users[current_User]->getPermission() == 1 && current_Board >= MENU_SIZE)
		{
			//�s�W�ݪO
			std::string name;
			SetColor(225);
			std::cout << "�п�J���Ыت��ݪO�W�١G";
			SetColor();
			std::cin >> name;
			boards.push_back(new Board(name));
		}
		else if (c == 13) //�ڬOenter��
		{
			userMoved = true;
			if (current_Board == 0) //�p�C��
			{
				system("cls");
				PokerGame g;
				while (1)
				{
					int myCoin = users[current_User]->getCoin() - 1;
					if (myCoin >= 0)
					{
						g.playGame(myCoin);
						users[current_User]->setCoin(myCoin);
						cout << "�{�b�� " << myCoin << " P��\n";
						cout << "�ٷQ�n�A���@����? (y/n) ";
						char yes;
						while (cin >> yes) if (yes == 'y' || yes == 'n') { break; }

						if (yes == 'n') break;
						else system("cls");
					}
					else
					{
						cout << "�l�B����! �L�k�i��C��\n";
						system("pause");
						break;
					}
				}
			}


			else if (current_Board == 1) //�H��c
			{
				bool Editing = true;
				int current_Mail = 0;
				int all_Mail = users[current_User]->getMailAmt();
				while (1)
				{
					system("cls");
					viewer.printMailBox(*users[current_User], current_Mail);
					char comm; comm = _getch();
					if (comm == 13)
					{
						system("cls");
						viewer.printMail(*users[current_User]->getThisMail(current_Mail));
						SetColor(240);
						cout << "  �����N��^��H�c  \n";
						SetColor();
						comm = _getch();
					}
					if (comm == 'w')
					{
						if (current_Mail > 0)
						{
							current_Mail--;
						}
					}
					else if (comm == 's')
					{
						if (current_Mail < all_Mail - 1)
						{
							current_Mail++;
						}
					}
					else if (comm == 'n')
					{
						system("cls");
						string to, title;
						bool isUserExist = false;
						SetColor(225); cout << "����HID��Jquit���}�H�H" << endl; SetColor();
						cout << "�п�J����HID: ";
						while (!isUserExist) {
							cin >> to;
							if (to == "quit") break;
							for (int i = 1; i < users.size(); i++)
							{
								if (i == current_User) continue;
								if (users[i]->getName() == to) isUserExist = true;
							}
							if (!isUserExist) cout << "����H���s�b! �Э��s��J����HID: ";
						}
						if (isUserExist)
						{
							getline(cin, title); //�B�z����
							cout << "�п�J�H����D: ";
							getline(cin, title);
							bool send = true;
							string str = "";
							vector<string> content;
							system("cls");
							while (Editing)
							{
								SetColor(63); cout << "  �Ӧ��J������Ы�enter�C��esc�����s�� / �e�X  \n"; SetColor();
								cout << "  ����H: " << to << endl << "  ���D: " << title << endl;
								cout << "  �п�J����: \n";
								for (int i = 0; i < content.size(); i++)
								{
									cout << "  " << content[i] << endl;
								}
								cout << "  " << str;
								viewer.editMail(Editing, send, str, content);
							}
							if (send)
							{
								ofstream fout;
								fout.open("./User/" + to + ".txt", ios::app);
								fout << users[current_User]->getName() << endl;
								fout << title << endl;
								for (int i = 0; i < content.size(); i++)
								{
									fout << content[i] << endl;
								}
								fout << "/*EndOfMail*/" << endl;
								fout.close();
							}
						}
					}
					else if (comm == 27) break;

				}
			}


			else if (current_Board == 2) //�d�ݦۤv�o�L���峹
			{
				int _myPost = 0;
				int allPost = users[current_User]->getPostnum();
				bool Editing = true;
				while (1)
				{
					system("cls");
					viewer.printPostBox(*users[current_User], _myPost);
					char choice;
					choice = _getch();
					if (choice == 'w')
					{
						if (_myPost > 0) _myPost--;
					}
					else if (choice == 's')
					{
						if (_myPost < allPost - 1) _myPost++;
					}
					else if (choice == 'e' && users[current_User]->getPostnum())
					{
						Post* p = new Post;
						string bdName = users[current_User]->getThisPost(_myPost)->boardName;
						int pID = users[current_User]->getThisPost(_myPost)->postsID;
						int i, j;
						for (i = 0; i < boards.size(); i++)
						{
							if (boards[i]->getName() == bdName) {
								for (j = 0; j < boards[i]->getPostNum(); j++)
								{
									if (boards[i]->getPost(j)->getPostID() == pID) break;
								}
								break;
							}
						}
						p = boards[i]->getPost(j);
						vector<string> newCont;
						for (int k = 0; k < p->getContentLines(); k++) 
						{
							newCont.push_back(p->getPostContent(k));
						}
						system("cls");

						bool post = false;
						string str = "";
						while (Editing)
						{
							SetColor(63); cout << "  �Ӧ��J������Ы�enter�C��esc�����s�� / �e�X  \n"; SetColor();
							cout << "  �ݪO�G " << boards[i]->getName() << endl << "  ���D�G " << p->getPostTitle() << endl;
							cout << "  �п�J����: \n";
							for (int i = 0; i < newCont.size(); i++)
							{
								cout << "  " << newCont[i] << endl;
							}
							cout << "  " << str;
							viewer.editPost(Editing, post, str, newCont);
						}
						p->resetPostContent();
						for (int k = 0; k < newCont.size(); k++)
						{
							p->setPostContent(newCont[k]);
						}
						p->setPostContent("(Edited by author)\n");
						Editing = true;
					}
					else if (choice == 'd' && users[current_User]->getPostnum())
					{
						system("cls");
						cout << "�T�w�n�R�����K��ܡH�]y/n�^" << endl;
						char command;
						while (command = _getch()) 
						{
							if (command == 'y')
							{
								//Post* p = new Post;
								string bdName = users[current_User]->getThisPost(_myPost)->boardName;
								string postTitle = users[current_User]->getThisPost(_myPost)->title;
								int pID = users[current_User]->getThisPost(_myPost)->postsID;
								int i, j;
								for (i = 0; i < boards.size(); i++)
								{
									if (boards[i]->getName() == bdName) {
										for (j = 0; j < boards[i]->getPostNum(); j++)
										{
											if (boards[i]->getPost(j)->getPostID() == pID) break;
										}
										break;
									}
								}
								string newTitle = "This post was deleted already.";
								boards[i]->getPost(j)->setPostTitle(newTitle);
								//p = boards[i]->getPost(j);
								//p->setPostTitle(newTitle);

								int postBoxID;
								for (int k = 0; k < users[current_User]->getPostnum(); k++)
								{
									if (users[current_User]->getThisPost(k)->postsID == users[current_User]->getThisPost(_myPost)->postsID) {
										postBoxID = k;
										break;
									}
								}
								users[current_User]->deletePost(postBoxID);
								state = BoardState::POST;
								break;
							}
							else if (command == 'n')
							{
								state = BoardState::POST;
								break;
							}
						}

					}
					else if (choice == 'n')
					{
						system("cls");
						string postBoard, postTitle, postContent;
						bool isBoardExist = false;
						SetColor(225); cout << "�ݪO�W�ٿ�Jquit���}�s�W�K��" << endl; SetColor();
						cout << "�п�J�ݪO�W��: ";
						while (!isBoardExist) {
							cin >> postBoard;
							if (postBoard == "quit") break;
							for (int i = 0; i < boards.size(); i++)
							{
								//if (i == current_Board) continue;
								if (boards[i]->getName() == postBoard) isBoardExist = true;
							}
							if (!isBoardExist) cout << "�ݪO���s�b�I �Э��s��J�ݪO�W�١G ";
						}
						if (isBoardExist)
						{
							getline(cin, postTitle); //�B�z����
							cout << "�п�J�K����D�G ";
							getline(cin, postTitle);
							bool post = true;
							string str = "";
							vector<string> content;
							system("cls");
							while (Editing)
							{
								SetColor(63); cout << "  �Ӧ��J������Ы�enter�C��esc�����s�� / �e�X  \n"; SetColor();
								cout << "  �ݪO�G " << postBoard << endl << "  ���D�G " << postTitle << endl;
								cout << "  �п�J����: \n";
								for (int i = 0; i < content.size(); i++)
								{
									cout << "  " << content[i] << endl;
								}
								cout << "  " << str;
								viewer.editPost(Editing, post, str, content);
							}
							if (post)
							{
								Post *p = new Post;
								int i;
								for (i = 0; i < boards.size(); i++)
								{
									if (boards[i]->getName() == postBoard) {
										break;
									}
								}
								int allPostNum = 0;
								for (int j = 0; j < boards.size(); j++)
								{
									allPostNum += boards[j]->getPostNum();
								}
								int myPostID = allPostNum + 1;

								p->setPostAuthor(users[current_User]->getName());
								for (int c = 0; c < content.size(); c++) 
								{
									p->setPostContent(content[c]);
								}
								p->setPostID(myPostID);
								p->setPostTitle(postTitle);
								boards[i]->pushPostIDs(myPostID);
								boards[i]->pushAllPost(p);
								boards[i]->setPostNum(boards[i]->getPostNum() + 1);

								myPost myNewPost(myPostID, postBoard, postTitle);
								
								users[current_User]->newPost(myNewPost);
								Editing = true;
								break;
							}
						}
					}

					else if (choice == 27)
					{
						
						state = BoardState::SELECT_BOARD;
						break;
					}
					else if (choice == 13)
					{
						if (users[current_User]->getPostnum() && users[current_User]->getThisPost(_myPost)->title[0] != -90)
						{

							state = BoardState::POST;
							string bdName = users[current_User]->getThisPost(_myPost)->boardName;
							int pID = users[current_User]->getThisPost(_myPost)->postsID;
							for (int i = 0; i < boards.size(); i++)
							{
								if (boards[i]->getName() == bdName) {
									for (int j = 0; j < boards[i]->getPostNum(); j++)
									{
										if (boards[i]->getPost(j)->getPostID() == pID) {
											current_Board = i;
											current_Board += MENU_SIZE;
											current_Post = j;
											return;
										}
									}
								}
							}
						}
					}
				}
			}
			else if (current_Board == 3) 
			{
				cookieMaker cm;
				int coins = users[current_User]->getCoin();
				cm.game(coins);
				users[current_User]->setCoin(coins);
			}

			else if (current_Board == MENU_SIZE - 1) //�n�X
			{
				this->logoutWriteToFile(current_User);
				system("cls");
				cout << "  �n�X�I\n\n";
				current_Board = MENU_SIZE;
				current_Post = 0;
				current_User = 0;
				system("pause");
				state = BoardState::MENU;

			}
			else
			{
				state = BoardState::BOARD;
			}
		}
		else if (c == 27 && current_User == 0) //�ڬOesc
		{
			state = BoardState::MENU;
		}
	}
	else if (state == BoardState::BOARD)
	{
		system("cls");
		viewer.printBoard(users[current_User]->getPermission(), *boards[current_Board - MENU_SIZE], current_Post); //-MENU_SIZE���\���檺����

		char c;
		c = _getch();
		if (c == 'w')
		{
			if (current_Post > 0)
			{
				current_Post--;
			}
		}
		else if (c == 's')
		{

			if (current_Post < boards[current_Board - MENU_SIZE]->getPostNum() - 1)
			{
				current_Post++;
			}
		}
		else if (c == 'a')
		{
			if (current_Post - 10 >= 0) //���O�b�̭���
			{
				int nowPage = current_Post / 10;
				current_Post = (nowPage - 1) * 10;
			}
		}
		else if (c == 'd')
		{
			int nowPage = current_Post / 10;
			int allPage = boards[current_Board - MENU_SIZE]->getPostNum() / 10;
			if (nowPage != allPage) //���O�b�̧���
			{
				current_Post = (nowPage + 1) * 10;
			}
		}
		else if (c == 'y' && users[current_User]->getPermission() == 1)
		{
				string why;
				char de;
				SetColor(225);
				cout << "�T�w�R���o�h�K��? (y/n):"; //�����
				SetColor();
				cout << " ";
				while (cin >> de)
				{
					if (de == 'y') break;
					else if (de == 'n') return;
				}
				string buffer; //�B�z����
				getline(cin, buffer);
				SetColor(225);
				cout << "�Яd�U�R�����h�K�媺��]�G";
				SetColor();
				getline(cin, why);
				why = "���K��w�Q�޲z���R���A�]���G" + why;
				int postBoxID = 0;
				int nameNum = 0;
				for (int k = 0; k < this->users.size(); k++)
				{
					if (users[k]->getName() == boards[current_Board - MENU_SIZE]->getPost(current_Post)->getPostAuthor())
					{
						nameNum = k;
						break;
					}
				}
				for (int k = 0; k < users[nameNum]->getPostnum(); k++)
				{
					if (users[nameNum]->getThisPost(k)->postsID == boards[current_Board - MENU_SIZE]->getPost(current_Post)->getPostID()) {
						postBoxID = k;
						break;
					}
				}
				boards[current_Board - MENU_SIZE]->getPost(current_Post)->setPostTitle(why);
				boards[current_Board - MENU_SIZE]->getPost(current_Post)->setPostAuthor("unKnowed");
		}
		else if (c == 13) //�ڬOenter��
		{
			if (boards[current_Board - MENU_SIZE]->getPostNum() != 0 /*&& boards[current_Board - MENU_SIZE]->getPost(current_Post)->getPostAuthor()!= "unKnowed"*/)
			{
				userMoved = true;
				state = BoardState::POST;
			}
		}
		else if (c == 27) //�ڬOesc��
		{
			userMoved = true;
			state = BoardState::SELECT_BOARD;
			current_Post = 0;
		}

	}
	else if (state == BoardState::POST) {
		system("cls");
		viewer.printPost(users[current_User]->getPermission(), *boards[current_Board - MENU_SIZE], current_Post);
		if (boards[current_Board - MENU_SIZE]->getPost(current_Post)->getPostTitle() == "This post was deleted already." || 
			boards[current_Board - MENU_SIZE]->getPost(current_Post)->getPostAuthor() == "unKnowed" )
		{
			system("pause>nul");
			state = BoardState::BOARD;
			userMoved = true;
			return;
		}
		char c = _getch();
		if (c == 'c' && current_User != 0)  //�� C �d��
		{
			int upOrDown;
			string comment;
			bool alreadyUpOrDown = false;
			for (int i = 0; i < boards[current_Board - MENU_SIZE]->getPost(current_Post)->getCommentAmt(); i++)
			{
				if (users[current_User]->getName() == boards[current_Board - MENU_SIZE]->getPost(current_Post)->getComment(i)->commentName)
				{
					if (boards[current_Board - MENU_SIZE]->getPost(current_Post)->getComment(i)->upOrDown != 0)
					{
						upOrDown = 0;
						alreadyUpOrDown = true;
					}
				}
			}
			if (!alreadyUpOrDown)
			{
				std::cout << "�A�Q�N�٬O���O? ( �N -1 / �� 1 / �L�Q�k 0 )" << endl;
				cin >> upOrDown;
				//�����J���~
				while (cin.fail() || (upOrDown != -1 && upOrDown != 0 && upOrDown != 1))
				{
					cin.clear();
					cin.ignore();
					cin >> upOrDown;
				}
				//�����J���~
				getchar(); //Ū�� \n 
			}
			std::cout << "�п�J�d�����e" << endl;
			getline(cin, comment);
			//����ťտ�J
			while (comment.length() == 0)
			{
				getline(cin, comment);
			}
			//����ťտ�J
			Comment* a = new Comment(0, upOrDown, users[current_User]->getName(), comment);
			Post* post = boards[current_Board - MENU_SIZE]->getPost(current_Post);
			post->pushAllcomment(a);
		}
		else if (c == 'x' && users[current_User]->getPermission() == 1)  //�R���d���Ҧ�
		{
			int current_Comment = 0;
			while (1)
			{
				system("cls");
				viewer.printDeleteComment(users[current_User]->getPermission(), *boards[current_Board - MENU_SIZE], current_Post, current_Comment); //-MENU_SIZE���\���檺����
				SetColor(128);
				cout << "�� w/s �ӿ�ܱ��R�����d���A��esc�h�X�R���d���Ҧ��C\n";
				SetColor();
				char w = _getch();
				if (w == 'w')
				{
					if (current_Comment > 0)
					{
						current_Comment--;
					}
				}
				else if (w == 's')
				{

					if (current_Comment < boards[current_Board - MENU_SIZE]->getPost(current_Post)->getCommentAmt() - 1)
					{
						current_Comment++;
					}
				}
				else if (w == 13 && boards[current_Board - MENU_SIZE]->getPost(current_Post)->getCommentAmt() > 0 && boards[current_Board - MENU_SIZE]->getPost(current_Post)->getComment(current_Comment)->commentName != "unKnowed") //�ڬOenter��
				{
					string why;
					char de;
					SetColor(225);
					cout << "�T�w�R���o�h�d��? (y/n):"; //�����
					SetColor();
					cout << " ";
					while (cin >> de)
					{
						if (de == 'y') break;
						else if (de == 'n') return;
					}
					string buffer; //�B�z����
					getline(cin, buffer);

					SetColor(225);
					cout << "�Яd�U�R���d������]�G";
					SetColor();
					getline(cin, why);
					why = "���d���w�Q�޲z���R���A�]���G" + why;
					boards[current_Board - MENU_SIZE]->getPost(current_Post)->getComment(current_Comment)->commentContent = why;
					boards[current_Board - MENU_SIZE]->getPost(current_Post)->getComment(current_Comment)->commentName = "unKnowed";
				}
				else if (w == 27) //�ڬOesc��
				{
					break;
				}
			}

		}
		else if (c == 27) //�ڬOesc��
		{
			state = BoardState::BOARD;
		}
	}
}

class MiniGame {

};