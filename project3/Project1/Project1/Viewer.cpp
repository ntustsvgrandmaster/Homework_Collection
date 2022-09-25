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
	cout << "ˊ |   |  |   | ˋ           |  |\t\t\t\t\t       |  |" << endl;
	cout << "|  |   |  |   |  |           |  |\t\t\t\t\t       |  |" << endl;
	cout << "|  |   |  |   |  |    ____   |  |     __       ___      _              ____    |  |" << endl;
	cout << "|  |   |  |   |  |  ˊ __ ˋ |  |  ˊ __ ˋ ˊ ___ ˋ  | ˋˊˋˊˋ  ˊ __ ˋ  |  |" << endl;
	cout << "|  |   |  |   |  |  |ˊ__ˋ| |  | | ˊ  |_| |ˊ   ˋ|  | ˊˋˊˋ |  |ˊ__ˋ|  |  |" << endl;
	cout << "|  |   |  |   |  |  |  ____| |  | | |    _  ||     ||  | |  | | | |  |  ____|  |__|" << endl;
	cout << "|  ˋ_ˊ  ˋ_ˊ  |  | |____  |  | | ˋ__| | |ˋ___ˊ|  | |  | | | |  | |____    __" << endl;
	cout << " ˋ____ˊˋ____ˊ   ˋ____ˊ |__|  ˋ __ ˊ ˋ ___ ˊ  |_|  |_| |_|  ˋ____ˊ  |__|" << endl;
	cout << endl;
	cout << "請輸入帳號，或是輸入";
	SetColor(240);
	cout << "guest";
	SetColor();
	cout << "以進入訪客介面、";
	SetColor(240);
	cout << "new";
	SetColor();
	cout << "以註冊新帳密\n";
}

void Viewer::printSelector(int permission, std::vector<Board*>& bv, int nowViewing, int menu)
{
	using std::cout; using std::endl;

	cout << "-\n";
	SetColor(103);
	cout << " ＰＰＰＰ　　ＴＴＴＴＴＴ　ＴＴＴＴＴＴ　　　離　　　　離　　　　線　　　　線　　　版　版　版版版版版  " << endl;
	cout << " Ｐ　　　Ｐ　ＴＴＴＴＴＴ　ＴＴＴＴＴＴ　離離離離離　離　離　　線　線　線線線線線　版　版　版　　　　  " << endl;
	cout << " Ｐ　　　Ｐ　　　ＴＴ　　　　　ＴＴ　　　　離　離　離離離離離　線線線　線線線線線　版版版　版　　　　  " << endl;
	cout << " ＰＰＰＰ　　　　ＴＴ　　　　　ＴＴ　　　　離離離　　離　離　　　線　　線線線線線　版　　　版版版版版  " << endl;
	cout << " Ｐ　　　　　　　ＴＴ　　　　　ＴＴ　　　　　離　　　離離離離　線線線　　　線　　　版　　　版版　　版  " << endl;
	cout << " Ｐ　　　　　　　ＴＴ　　　　　ＴＴ　　　離離離離離　離　離　　　線　　線線線　線　版版版　版　版版　  " << endl;
	cout << " Ｐ　　　　　　　ＴＴ　　　　　ＴＴ　　　離　離　離　離離離離　線線線　　　線線　　版　版　版　版版　  " << endl;
	cout << " Ｐ　　　　　　　ＴＴ　　　　　ＴＴ　　　離離離離離　離　離　　線線線　　線線線　　版　版　版版　　版  " << endl;
	cout << " Ｐ　　　　　　　ＴＴ　　　　　ＴＴ　　　離　　　離　離離離離　　線　　線　線　線　版　版　版　　　　版" << endl;
	SetColor();
	cout << "-\n";

	if (nowViewing >= menu) //選擇看板
	{
		nowViewing -= menu;
		cout << "使用(w/s)來移動箭頭，並且enter進入看板。";
		if (permission < 3)
		{
			cout << " 或是使用(a/d)來進出功能選單。\n\n";
			/*SetColor(249); cout << "''"; SetColor(); cout << "進入小遊戲。\n\n";*/
		}
		else
		{
			cout << " 或是使用esc返回MENU\n\n";
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
			cout << "在指定板按 y 可刪除此看板 ! \n";
			cout << "按 u 可新增看板 ! \n";
			SetColor();
		}

	}
	else //功能選單
	{
		cout << "使用(w/s)來移動箭頭，並且選擇想要的功能。 或是使用(a/d)來進出功能選單。\n\n";
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
	cout << "　　　　 _______"; for (int i = 0; i < bd.getName().size(); i++) { cout << "_"; } cout << " 　　　　　　\n";
	cout << "　　　　|看板 > " << bd.getName() << "|　　　　　　\n";
	cout << "　　　　 ¯¯¯¯¯¯¯"; for (int i = 0; i < bd.getName().size(); i++) { cout << "¯"; } cout << " 　　　　　　\n";
	SetColor();
	cout << "    使用w/s上下瀏覽貼文、a/d到上下一頁\n    或是esc返回前頁。\n";

	if (permission == 1)
	{
		SetColor(225);
		cout << "在指定貼文按 y 可刪除此貼文 ! \n\n\n";
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
					if (pushs >= 10) { SetColor(12); cout << "爆"; SetColor(); }
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
					if (pushs >= 10) { SetColor(12); cout << "爆"; SetColor(); }
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
					if (pushs >= 10) { SetColor(12); cout << "爆"; SetColor(); }
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
					if (pushs >= 10) { SetColor(12); cout << "爆"; SetColor(); }
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
		cout << "\t\t\t\t第 " << page + 1 << "頁 / " << allPage + 1 << "頁\n";
	}
}

void Viewer::printPost(int permission, Board& bd, int postID)
{
	Post *post = bd.getPost(postID);

	if (post->getPostAuthor() == "unKnowed")
	{
		std::cout << post->getPostTitle() << std::endl << std::endl;
		std::cout << "  按任意鍵回到文章選單. . .";
		return;
	}
	if (post->getPostTitle() == "This post was deleted already.") {
		std::cout << "\n  ";
		SetColor(236); std::cout << "此文章已被刪除!\n\n"; SetColor();
		std::cout << "  按任意鍵回到文章選單. . .";
		return;
	}

	using std::cout; using std::endl;
	int longer = post->getPostTitle().length() > post->getPostAuthor().length() ? post->getPostTitle().length() : post->getPostAuthor().length();
	
	SetColor(112);
	cout << "　　　　 看板 > " << bd.getName(); 
	for (int i = 0; i < longer + 9 - bd.getName().length(); i++) { cout << " "; }
	cout << endl;

	SetColor(31);
	cout << "　　 _______"; for (int i = 0; i < longer; i++) { cout << "_"; } cout << " 　　　　　　\n　　|";
	SetColor(121); cout << " 作者 "; SetColor(31); cout << " " << post->getPostAuthor(); 
	for (int i = 0; i < longer - post->getPostAuthor().length(); i++) {cout << " ";} cout << "|　　　　　　\n　　|";
	SetColor(121); cout << " 標題 "; SetColor(31); cout << " " << post->getPostTitle(); 
	for (int i = 0; i < longer - post->getPostTitle().length(); i++) { cout << " "; } cout << "|　　　　　　\n";
	cout << "　　 ¯¯¯¯¯¯¯"; for (int i = 0; i < longer; i++) { cout << "¯"; } cout << " 　　　　　　\n";
	SetColor();

	/*內文*/
	for (int i = 0; i < post->getContentLines(); i++) 
	{
		cout << "　" << post->getPostContent(i) << endl;
	}
	cout << "　--\n";
	/*留言*/
	for(int i = 0; i < post->getCommentAmt();i++)
	{
		Comment *cmt = post->getComment(i);
		cout << "　";
		int PD = cmt->upOrDown;
		if (PD == 1) { cout << "推 "; }
		else if (PD == -1) { SetColor(12); cout << "噓 "; }
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
		cout << "使用快捷鍵";
		SetColor(121);
		cout << " 'c' ";
		SetColor(112);
		cout << "進入留言模式，發表你的想法吧~\n";
		SetColor();
	}
	if (permission == 1)
	{
		cout << "  ";
		SetColor(225);
		cout << "按 x 進入刪除留言模式 \n";
		SetColor();
	}
}

void Viewer::printDeleteComment(int permission, Board& bd, int postID, int nowViewing)
{
	Post* post = bd.getPost(postID);

	using std::cout; using std::endl;
	int longer = post->getPostTitle().length() > post->getPostAuthor().length() ? post->getPostTitle().length() : post->getPostAuthor().length();

	SetColor(112);
	cout << "　　　　 看板 > " << bd.getName();
	for (int i = 0; i < longer + 9 - bd.getName().length(); i++) { cout << " "; }
	cout << endl;

	SetColor(31);
	cout << "　　 _______"; for (int i = 0; i < longer; i++) { cout << "_"; } cout << " 　　　　　　\n　　|";
	SetColor(121); cout << " 作者 "; SetColor(31); cout << " " << post->getPostAuthor();
	for (int i = 0; i < longer - post->getPostAuthor().length(); i++) { cout << " "; } cout << "|　　　　　　\n　　|";
	SetColor(121); cout << " 標題 "; SetColor(31); cout << " " << post->getPostTitle();
	for (int i = 0; i < longer - post->getPostTitle().length(); i++) { cout << " "; } cout << "|　　　　　　\n";
	cout << "　　 ¯¯¯¯¯¯¯"; for (int i = 0; i < longer; i++) { cout << "¯"; } cout << " 　　　　　　\n";
	SetColor();

	/*內文*/
	for (int i = 0; i < post->getContentLines(); i++)
	{
		cout << "　" << post->getPostContent(i) << endl;
	}
	cout << "　--\n";
	/*留言*/
	for (int i = 0; i < post->getCommentAmt(); i++)
	{
		Comment* cmt = post->getComment(i);
		cout << "　";
		int PD = cmt->upOrDown;
		if (i == nowViewing) { cout << "->"; }
		else { cout << "  "; }
		if (PD == 1) { cout << "推 "; }
		else if (PD == -1) { SetColor(12); cout << "噓 "; }
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
	cout << "    使用w/s上下瀏覽信件，或是"; SetColor(240); cout << " esc "; SetColor(); cout << "退出信箱\n";
	cout << "    使用"; SetColor(240); cout << " n "; SetColor(); cout << "開始撰寫信件\n\n\n";;

	if (us.getMailAmt() == 0) 
	{
		cout << "    目前還沒有信件喔!\n";
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
	cout << "　　 _______"; for (int i = 0; i < longer; i++) { cout << "_"; } cout << " 　　　　　　\n　　|";
	SetColor(115); cout << " 作者 "; SetColor(63); cout << " " << conv.receiver;
	for (int i = 0; i < longer - conv.receiver.length(); i++) { cout << " "; } cout << "|　　　　　　\n　　|";
	SetColor(115); cout << " 標題 "; SetColor(63); cout << " " << conv.title;
	for (int i = 0; i < longer - conv.title.length(); i++) { cout << " "; } cout << "|　　　　　　\n";
	cout << "　　 ¯¯¯¯¯¯¯"; for (int i = 0; i < longer; i++) { cout << "¯"; } cout << " 　　　　　　\n";
	SetColor();

	for (int i = 0; i < conv.content.size(); i++)
	{
		cout << "　" << conv.content[i] << endl;
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
			cout << " 請問要 ";
			SetColor(63); cout << "繼續編輯(y)"; SetColor(); cout << " ";
			SetColor(63); cout << "捨棄(n)"; SetColor(); cout << " ";
			SetColor(63); cout << "寄出(s)?"; SetColor(); cout << " : ";
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
					cout << "  信件已送出!\n";
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
	cout << "    使用w/s上下選擇貼文，或是"; SetColor(240); cout << " esc "; SetColor(); cout << "退出瀏覽\n";
	cout << "    使用"; SetColor(240); cout << " enter "; SetColor(); cout << "進入貼文\n";
	cout << "    使用"; SetColor(240); cout << " n "; SetColor(); cout << "開始新增貼文\n";
	cout << "    使用"; SetColor(240); cout << " e "; SetColor(); cout << "開始編輯貼文\n";
	cout << "    使用"; SetColor(240); cout << " d "; SetColor(); cout << "刪除貼文\n\n\n    ";
	SetColor(63);  cout << "板塊\t\t標題"; SetColor(); cout << "\n";
	if (us.getPostnum() == 0)
	{
		cout << "    ";  SetColor(63); cout << "目前還沒有發過貼文喔!\n"; SetColor();
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
			cout << " 請問要 ";
			SetColor(63); cout << "繼續編輯(y)"; SetColor(); cout << " ";
			SetColor(63); cout << "捨棄(n)"; SetColor(); cout << " ";
			SetColor(63); cout << "發布(p)?"; SetColor(); cout << " : ";
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
					cout << "  貼文已發布!\n";
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