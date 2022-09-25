#include "Viewer.h"
#include <Windows.h>

void SetColor(int color)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void Viewer::printMenu(bool& moved)
{
	system("cls");
	using std::cout; using std::endl;
	cout << "  _     __     _              __\t\t\t\t\t        __" << endl;
	cout << "�� |   |  |   | ��           |  |\t\t\t\t\t       |  |" << endl;
	cout << "|  |   |  |   |  |           |  |\t\t\t\t\t       |  |" << endl;
	cout << "|  |   |  |   |  |    ____   |  |     __       ___      _              ____    |  |" << endl;
	cout << "|  |   |  |   |  |  �� __ �� |  |  �� __ �� �� ___ ��  | ����������  �� __ ��  |  |" << endl;
	cout << "|  |   |  |   |  |  |��__��| |  | | ��  |_| |��   ��|  | �������� |  |��__��|  |  |" << endl;
	cout << "|  |   |  |   |  |  |  ____| |  | | |    _  ||     ||  | |  | | | |  |  ____|  |__|" << endl;
	cout << "|  ��_��  ��_��  |  | |____  |  | | ��__| | |��___��|  | |  | | | |  | |____    __" << endl;
	cout << " ��____����____��   ��____�� |__|  �� __ �� �� ___ ��  |_|  |_| |_|  ��____��  |__|" << endl;
	cout << endl;
	cout << "�п�J�b���A�άO��J";
	SetColor(240);
	cout << "guest";
	SetColor();
	cout << "�H�i�J�X�Ȥ����B";
	SetColor(240);
	cout << "new";
	SetColor();
	cout << "�H���U�s�b�K\n";
}

void Viewer::printSelector(int permission, std::vector<Board*>& bv, int nowViewing, int menu)
{
	using std::cout; using std::endl;

	cout << "-\n";
	SetColor(103);
	cout << " �ޢޢޢޡ@�@�������@�������@�@�@���@�@�@�@���@�@�@�@�u�@�@�@�@�u�@�@�@���@���@����������  " << endl;
	cout << " �ޡ@�@�@�ޡ@�������@�������@�����������@���@���@�@�u�@�u�@�u�u�u�u�u�@���@���@���@�@�@�@  " << endl;
	cout << " �ޡ@�@�@�ޡ@�@�@���@�@�@�@�@���@�@�@�@���@���@�����������@�u�u�u�@�u�u�u�u�u�@�������@���@�@�@�@  " << endl;
	cout << " �ޢޢޢޡ@�@�@�@���@�@�@�@�@���@�@�@�@�������@�@���@���@�@�@�u�@�@�u�u�u�u�u�@���@�@�@����������  " << endl;
	cout << " �ޡ@�@�@�@�@�@�@���@�@�@�@�@���@�@�@�@�@���@�@�@���������@�u�u�u�@�@�@�u�@�@�@���@�@�@�����@�@��  " << endl;
	cout << " �ޡ@�@�@�@�@�@�@���@�@�@�@�@���@�@�@�����������@���@���@�@�@�u�@�@�u�u�u�@�u�@�������@���@�����@  " << endl;
	cout << " �ޡ@�@�@�@�@�@�@���@�@�@�@�@���@�@�@���@���@���@���������@�u�u�u�@�@�@�u�u�@�@���@���@���@�����@  " << endl;
	cout << " �ޡ@�@�@�@�@�@�@���@�@�@�@�@���@�@�@�����������@���@���@�@�u�u�u�@�@�u�u�u�@�@���@���@�����@�@��  " << endl;
	cout << " �ޡ@�@�@�@�@�@�@���@�@�@�@�@���@�@�@���@�@�@���@���������@�@�u�@�@�u�@�u�@�u�@���@���@���@�@�@�@��" << endl;
	SetColor();
	cout << "-\n";

	if (nowViewing >= menu) //��ܬݪO
	{
		nowViewing -= menu;
		cout << "�ϥ�(w/s)�Ӳ��ʽb�Y�A�åBenter�i�J�ݪO�C";
		if (permission < 3)
		{
			cout << " �άO�ϥ�(a/d)�Ӷi�X�\����C\n\n";
			/*SetColor(249); cout << "''"; SetColor(); cout << "�i�J�p�C���C\n\n";*/
		}
		else
		{
			cout << " �άO�ϥ�esc��^MENU\n\n";
		}
		for (int i = 0; i < bv.size(); i++)
		{
			if (i == nowViewing)
			{
				cout << ">\t";
			}
			else
			{
				cout << "\t";
			}
			cout << bv[i]->getName() << endl;
		}


		if (permission == 1)
		{
			cout << endl;
			SetColor(225);
			cout << "�b���w�O�� y �i�R�����ݪO ! \n";
			cout << "�� u �i�s�W�ݪO ! \n";
			SetColor();
		}

	}
	else //�\����
	{
		cout << "�ϥ�(w/s)�Ӳ��ʽb�Y�A�åB��ܷQ�n���\��C �άO�ϥ�(a/d)�Ӷi�X�\����C\n\n";
		if (nowViewing == 0) cout << ">\t"; else cout << "\t";
		cout << "Poker Game\n";
		if (nowViewing == 1) cout << ">\t"; else cout << "\t";
		cout << "Mail Box\n";
		if (nowViewing == 2) cout << ">\t"; else cout << "\t";
		cout << "My Posts\n";
		if (nowViewing == 3) cout << ">\t"; else cout << "\t";
			cout << "Cookie making game\n";
		if (nowViewing == menu - 1) cout << ">\t"; else cout << "\t";
		cout << "Log out\n";
	}
}

void Viewer::printBoard(int permission, Board& bd, int nowViewing)
{
	using std::cout; using std::endl;
	SetColor(31);
	cout << "�@�@�@�@ _______"; for (int i = 0; i < bd.getName().size(); i++) { cout << "_"; } cout << " �@�@�@�@�@�@\n";
	cout << "�@�@�@�@|�ݪO > " << bd.getName() << "|�@�@�@�@�@�@\n";
	cout << "�@�@�@�@ �¡¡¡¡¡¡�"; for (int i = 0; i < bd.getName().size(); i++) { cout << "��"; } cout << " �@�@�@�@�@�@\n";
	SetColor();
	cout << "    �ϥ�w/s�W�U�s���K��Ba/d��W�U�@��\n    �άOesc��^�e���C\n";

	if (permission == 1)
	{
		SetColor(225);
		cout << "�b���w�K��� y �i�R�����K�� ! \n\n\n";
		SetColor();
	}

	int postNum = bd.getPostNum();
	if (postNum < 10) 
	{
		for (int i = 0; i < bd.getPostNum(); i++)
		{
			int pushs = bd.getPost(i)->getPostUpNum();
			if (i == nowViewing)
			{
				cout << ">    ";
				if (pushs > 0)
				{
					if (pushs >= 10) { SetColor(12); cout << "�z"; SetColor(); }
					else if (pushs >= 5) { SetColor(14); cout << pushs; SetColor(); }
					else { SetColor(10); cout << pushs; SetColor(); }
				}
				cout << "\t";
			}
			else
			{
				cout << "     ";
				if (pushs > 0)
				{
					if (pushs >= 10) { SetColor(12); cout << "�z"; SetColor(); }
					else if (pushs >= 5) { SetColor(14); cout << pushs; SetColor(); }
					else { SetColor(10); cout << pushs; SetColor(); }
				}
				cout << "\t";
			}
			std::string title = bd.getPost(i)->getPostTitle();
			if (title.length() > 25)
			{
				if (bd.getPost(i)->getPostAuthor() == "unKnowed")
				{
					cout << "Post is deleted by admin" << endl;
				}
				else if (title == "This post was deleted already.") 
				{
					cout << "Post is deleted by author" << endl;
				}
				else
				{
					cout << title.substr(0, 25) << "...\n";
				}
			}
			else
			{
				cout << title << endl;
			}
		}
	}
	else 
	{
		int allPage = bd.getPostNum() / 10;
		int page = nowViewing / 10;
		int pageArticle = page == allPage ? (bd.getPostNum() - allPage * 10) : 10;
		nowViewing %= 10;
		for (int i = 0; i < pageArticle; i++)
		{
			int pushs = bd.getPost(i + page * 10)->getPostUpNum();
			if (i == nowViewing)
			{
				cout << ">    ";
				if (pushs > 0)
				{
					if (pushs >= 10) { SetColor(12); cout << "�z"; SetColor(); }
					else if (pushs >= 5) { SetColor(14); cout << pushs; SetColor(); }
					else { SetColor(10); cout << pushs; SetColor(); }
				}
				cout << "\t";
			}
			else
			{
				cout << "     ";
				if (pushs > 0)
				{
					if (pushs >= 10) { SetColor(12); cout << "�z"; SetColor(); }
					else if (pushs >= 5) { SetColor(14); cout << pushs; SetColor(); }
					else { SetColor(10); cout << pushs; SetColor(); }
				}
				cout << "\t";
			}
			std::string title = bd.getPost(i + page * 10)->getPostTitle();
			if (title.length() > 25)
			{
				cout << title.substr(0, 25) << "...\n";
			}
			else
			{
				cout << title << endl;
			}
		}
		cout << "\t\t\t\t�� " << page + 1 << "�� / " << allPage + 1 << "��\n";
	}
}

void Viewer::printPost(int permission, Board& bd, int postID)
{
	Post *post = bd.getPost(postID);

	if (post->getPostAuthor() == "unKnowed")
	{
		std::cout << post->getPostTitle() << std::endl << std::endl;
		std::cout << "  �����N��^��峹���. . .";
		return;
	}
	if (post->getPostTitle() == "This post was deleted already.") {
		std::cout << "\n  ";
		SetColor(236); std::cout << "���峹�w�Q�R��!\n\n"; SetColor();
		std::cout << "  �����N��^��峹���. . .";
		return;
	}

	using std::cout; using std::endl;
	int longer = post->getPostTitle().length() > post->getPostAuthor().length() ? post->getPostTitle().length() : post->getPostAuthor().length();
	
	SetColor(112);
	cout << "�@�@�@�@ �ݪO > " << bd.getName(); 
	for (int i = 0; i < longer + 9 - bd.getName().length(); i++) { cout << " "; }
	cout << endl;

	SetColor(31);
	cout << "�@�@ _______"; for (int i = 0; i < longer; i++) { cout << "_"; } cout << " �@�@�@�@�@�@\n�@�@|";
	SetColor(121); cout << " �@�� "; SetColor(31); cout << " " << post->getPostAuthor(); 
	for (int i = 0; i < longer - post->getPostAuthor().length(); i++) {cout << " ";} cout << "|�@�@�@�@�@�@\n�@�@|";
	SetColor(121); cout << " ���D "; SetColor(31); cout << " " << post->getPostTitle(); 
	for (int i = 0; i < longer - post->getPostTitle().length(); i++) { cout << " "; } cout << "|�@�@�@�@�@�@\n";
	cout << "�@�@ �¡¡¡¡¡¡�"; for (int i = 0; i < longer; i++) { cout << "��"; } cout << " �@�@�@�@�@�@\n";
	SetColor();

	/*����*/
	for (int i = 0; i < post->getContentLines(); i++) 
	{
		cout << "�@" << post->getPostContent(i) << endl;
	}
	cout << "�@--\n";
	/*�d��*/
	for(int i = 0; i < post->getCommentAmt();i++)
	{
		Comment *cmt = post->getComment(i);
		cout << "�@";
		int PD = cmt->upOrDown;
		if (PD == 1) { cout << "�� "; }
		else if (PD == -1) { SetColor(12); cout << "�N "; }
		else if (PD == 0) { SetColor(12); cout << "-> "; }
		if (cmt->commentName != "unKnowed")
		{
			SetColor(14);
			cout << cmt->commentName << ": " << cmt->commentContent << endl;
			SetColor();
		}
		else
		{
			SetColor();
			cout << cmt->commentContent << endl;
		}
	}

	if (permission != 3) 
	{
		cout << "  ";
		SetColor(112);
		cout << "�ϥΧֱ���";
		SetColor(121);
		cout << " 'c' ";
		SetColor(112);
		cout << "�i�J�d���Ҧ��A�o��A���Q�k�a~\n";
		SetColor();
	}
	if (permission == 1)
	{
		cout << "  ";
		SetColor(225);
		cout << "�� x �i�J�R���d���Ҧ� \n";
		SetColor();
	}
}

void Viewer::printDeleteComment(int permission, Board& bd, int postID, int nowViewing)
{
	Post* post = bd.getPost(postID);

	using std::cout; using std::endl;
	int longer = post->getPostTitle().length() > post->getPostAuthor().length() ? post->getPostTitle().length() : post->getPostAuthor().length();

	SetColor(112);
	cout << "�@�@�@�@ �ݪO > " << bd.getName();
	for (int i = 0; i < longer + 9 - bd.getName().length(); i++) { cout << " "; }
	cout << endl;

	SetColor(31);
	cout << "�@�@ _______"; for (int i = 0; i < longer; i++) { cout << "_"; } cout << " �@�@�@�@�@�@\n�@�@|";
	SetColor(121); cout << " �@�� "; SetColor(31); cout << " " << post->getPostAuthor();
	for (int i = 0; i < longer - post->getPostAuthor().length(); i++) { cout << " "; } cout << "|�@�@�@�@�@�@\n�@�@|";
	SetColor(121); cout << " ���D "; SetColor(31); cout << " " << post->getPostTitle();
	for (int i = 0; i < longer - post->getPostTitle().length(); i++) { cout << " "; } cout << "|�@�@�@�@�@�@\n";
	cout << "�@�@ �¡¡¡¡¡¡�"; for (int i = 0; i < longer; i++) { cout << "��"; } cout << " �@�@�@�@�@�@\n";
	SetColor();

	/*����*/
	for (int i = 0; i < post->getContentLines(); i++)
	{
		cout << "�@" << post->getPostContent(i) << endl;
	}
	cout << "�@--\n";
	/*�d��*/
	for (int i = 0; i < post->getCommentAmt(); i++)
	{
		Comment* cmt = post->getComment(i);
		cout << "�@";
		int PD = cmt->upOrDown;
		if (i == nowViewing) { cout << "->"; }
		else { cout << "  "; }
		if (PD == 1) { cout << "�� "; }
		else if (PD == -1) { SetColor(12); cout << "�N "; }
		else if (PD == 0) { SetColor(12); cout << "-> "; }
		if (cmt->commentName != "unKnowed")
		{
			SetColor(14);
			cout << cmt->commentName << ": " << cmt->commentContent << endl;
			SetColor();
		}
		else
		{
			SetColor();
			cout << cmt->commentContent << endl;
		}
	}
}


void Viewer::printMailBox(User& us, int now)
{
	using std::cout;
	cout << "    �ϥ�w/s�W�U�s���H��A�άO"; SetColor(240); cout << " esc "; SetColor(); cout << "�h�X�H�c\n";
	cout << "    �ϥ�"; SetColor(240); cout << " n "; SetColor(); cout << "�}�l���g�H��\n\n\n";;

	if (us.getMailAmt() == 0) 
	{
		cout << "    �ثe�٨S���H���!\n";
	}
	else 
	{
		cout << "   ";
		SetColor(63); cout << "sender\ttitle\n"; SetColor();
		for (int i = 0; i < us.getMailAmt(); i++) 
		{
			Conversation* c = us.getThisMail(i);
			if (now == i) cout << ">  ";
			else cout << "   ";

			cout << c->receiver;
			for (int i = 2 - (c->receiver.size()+3) / 8; i > 0 ; i--)
			{
				cout << "\t";
			}
			cout << c->title << "\n";
		}
	}
}

void Viewer::printMail(Conversation& conv)
{
	using std::cout; using std::endl;
	int longer = conv.receiver.length() > conv.title.length() ? conv.receiver.length() : conv.title.length();
	SetColor(63);
	cout << "�@�@ _______"; for (int i = 0; i < longer; i++) { cout << "_"; } cout << " �@�@�@�@�@�@\n�@�@|";
	SetColor(115); cout << " �@�� "; SetColor(63); cout << " " << conv.receiver;
	for (int i = 0; i < longer - conv.receiver.length(); i++) { cout << " "; } cout << "|�@�@�@�@�@�@\n�@�@|";
	SetColor(115); cout << " ���D "; SetColor(63); cout << " " << conv.title;
	for (int i = 0; i < longer - conv.title.length(); i++) { cout << " "; } cout << "|�@�@�@�@�@�@\n";
	cout << "�@�@ �¡¡¡¡¡¡�"; for (int i = 0; i < longer; i++) { cout << "��"; } cout << " �@�@�@�@�@�@\n";
	SetColor();

	for (int i = 0; i < conv.content.size(); i++)
	{
		cout << "�@" << conv.content[i] << endl;
	}
}

void Viewer::editMail(bool& edit, bool& send, std::string& str, std::vector<std::string>& content) 
{
	using namespace std;
	char ch;
	while (ch = _getch())
	{
		if (ch == 27) 
		{
			system("cls");
			cout << " �аݭn ";
			SetColor(63); cout << "�~��s��(y)"; SetColor(); cout << " ";
			SetColor(63); cout << "�˱�(n)"; SetColor(); cout << " ";
			SetColor(63); cout << "�H�X(s)?"; SetColor(); cout << " : ";
			while (cin >> ch)
			{
				if (ch == 'y')
				{
					edit = true;
					send = false;
					system("cls");
					return;
				}
				else if (ch == 'n')
				{
					edit = false;
					send = false;
					return;
				}
				else if (ch == 's') 
				{
					edit = false;
					send = true;
					cout << "  �H��w�e�X!\n";
					system("pause");
					return;
				}
			}
		}
		else if (ch == 13)
		{
			system("cls");
			content.push_back(str);
			str = "";
			return;
		}
		else if (ch == 8)
		{
			if (str.size() != 0)
			{
				str.pop_back();
			}
			else
			{
				if (!content.empty())
				{
					str = *content.rbegin();
					content.pop_back();
				}
			}
			system("cls");
			return;
		}
		else
		{
			str += ch;
			cout << ch;
		}
	}
}

void Viewer::printPostBox(User& us, int now)
{
	using std::cout;
	cout << "    �ϥ�w/s�W�U��ܶK��A�άO"; SetColor(240); cout << " esc "; SetColor(); cout << "�h�X�s��\n";
	cout << "    �ϥ�"; SetColor(240); cout << " enter "; SetColor(); cout << "�i�J�K��\n";
	cout << "    �ϥ�"; SetColor(240); cout << " n "; SetColor(); cout << "�}�l�s�W�K��\n";
	cout << "    �ϥ�"; SetColor(240); cout << " e "; SetColor(); cout << "�}�l�s��K��\n";
	cout << "    �ϥ�"; SetColor(240); cout << " d "; SetColor(); cout << "�R���K��\n\n\n    ";
	SetColor(63);  cout << "�O��\t\t���D"; SetColor(); cout << "\n";
	if (us.getPostnum() == 0)
	{
		cout << "    ";  SetColor(63); cout << "�ثe�٨S���o�L�K���!\n"; SetColor();
	}
	for (int i = 0; i < us.getPostnum(); i++)
	{
		if (i == now) cout << ">  ";
		else cout << "   ";

		myPost* p = us.getThisPost(i);

		cout << p->boardName;
		for (int i = 2 - (p->boardName.size() + 3) / 8; i > 0; i--)
		{
			cout << "\t";
		}
		string title;
		std::ifstream fin;
		fin.open("./Board/" + p->boardName + "/" + std::to_string(p->postsID) + ".txt");
		std::getline(fin, title);
		fin.close();
		cout << title << std::endl;
	}
}



void Viewer::editPost(bool& edit, bool& send, std::string& str, std::vector<std::string>& content)
{
	using namespace std;
	char ch;
	while (ch = _getch())
	{
		if (ch == 27)
		{
			system("cls");
			cout << " �аݭn ";
			SetColor(63); cout << "�~��s��(y)"; SetColor(); cout << " ";
			SetColor(63); cout << "�˱�(n)"; SetColor(); cout << " ";
			SetColor(63); cout << "�o��(p)?"; SetColor(); cout << " : ";
			while (cin >> ch)
			{
				if (ch == 'y')
				{
					edit = true;
					send = false;
					system("cls");
					return;
				}
				else if (ch == 'n')
				{
					edit = false;
					send = false;
					return;
				}
				else if (ch == 'p')
				{
					edit = false;
					send = true;
					cout << "  �K��w�o��!\n";
					system("pause");
					return;
				}
			}
		}
		else if (ch == 13)
		{
			system("cls");
			content.push_back(str);
			str = "";
			return;
		}
		else if (ch == 8)
		{
			if (str.size() != 0)
			{
				str.pop_back();
			}
			else
			{
				if (!content.empty())
				{
					str = *content.rbegin();
					content.pop_back();
				}
			}
			system("cls");
			return;
		}
		else
		{
			str += ch;
			cout << ch;
		}
	}
}