#pragma once
#include<string>
#include<vector>
using std::string;
using std::vector;

struct Comment
{
	int seqence;				// 留言順序
	int upOrDown;				//-1是噓 ，1是推，0是不噓不推。
	string commentName;			// 留言者
	string commentContent;		// 留言內容
	Comment()
	{
		seqence = 0;
		upOrDown = 0;
		commentName = "";
		commentContent = "";
	}
	Comment(int lseqence, int lupOrDown, string lcommentName, string lcommentConten)
	{
		seqence = lseqence;
		upOrDown = lupOrDown;
		commentName = lcommentName;
		commentContent = lcommentConten;
	}

};


class Post
{
private:
	int postID;
	string postTitle;
	string postAuthor;
	vector<string> postContent;
	int postUpNum;		//-1是噓 ，1是推，0是不噓不推。
	vector<Comment*> Allcomment;

public:
	Post()
	{
		this->postID = 0;
		this->postTitle = "";
		this->postAuthor = "";
		this->postUpNum = 0;
	}

	Post(int lpostID, string lposttitle, string lpostAuthor, string lpostContent, int lpostUpNum)
	{
		this->postID = lpostID;
		this->postTitle = lposttitle;
		this->postAuthor = lpostAuthor;
		this->postUpNum = lpostUpNum;
	}

	int getPostID() { return this->postID; }
	void setPostID(int n) { this->postID = n; }
	string getPostTitle() { return this->postTitle; }
	void setPostTitle(string n) { this->postTitle = n; }
	string getPostAuthor() { return this->postAuthor; }
	void setPostAuthor(string n) { this->postAuthor = n; }
	string getPostContent(int c) { return this->postContent[c]; }		//得到第幾行的content
	void setPostContent(string n) { this->postContent.push_back(n); }		//輸入content
	void resetPostContent() //重新設定貼文內容
	{
		while (!postContent.empty()) postContent.pop_back();
	}
	void changePostContent(int c, string n) { this->postContent[c] = n; }		//更改第幾行content
	Comment* getComment(int n) { return this->Allcomment[n]; }		//回傳第n個留言的 comment指標。
	void pushAllcomment(Comment* n) { this->Allcomment.push_back(n); }		//添加新 comment
	void deleteComment(int n)		//刪除留言用
	{
		vector< Comment*> ::iterator it;
		it = Allcomment.begin() + n;
		this->Allcomment.erase(it);
	}

	int getContentLines() { return this->postContent.size(); }
	int getCommentAmt() { return this->Allcomment.size(); }
	void setPostUpNum(int n) { this->postUpNum = n; }
	int getPostUpNum() {
		int num = 0;
		for (int i = 0; i < Allcomment.size(); i++)
		{
			if (Allcomment[i]->upOrDown == 1) num++;
		}
		return num;
	}
};
