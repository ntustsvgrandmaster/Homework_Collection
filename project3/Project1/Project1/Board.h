#pragma once
#include <vector>
#include <string>
#include "Post.h"
class Board {
private:
	std::string bName;
	int postNum;
	std::vector<int> postIDs;
	std::vector<Post*> AllPost;
public:
	Board()
	{
		this->bName = "";
		this->postNum = 0;
	}
	Board(std::string n)
	{
		this->bName = n;
		this->postNum = 0;
	}

	int getPostNum() { return this->postNum; }
	void setPostNum(int  n) { this->postNum = n; }
	std::string getName() { return this->bName; }
	void setName(std::string n) { this->bName = n; }
	int getPostIDs(int n) { return this->postIDs[n]; }			//�^�ǲ�n�g�K�媺 postIDs�C
	void setPostIDs(int n, int s) { this->postIDs[n] = s; }		//�]�w��n�g�K�媺 postIDs�C
	void pushPostIDs(int n) { this->postIDs.push_back(n); }			//�K�[�s postID
	Post* getPost(int n) { return this->AllPost[n]; }		//�^�ǲ�n�g�K�媺 post���СC
	vector<Post*>::iterator getAllPostBegin() { return this->AllPost.begin(); }		//�o�� AllPost.begin()
	vector<Post*>::iterator getAllPostEnd() { return this->AllPost.end(); }			//�o�� AllPost.end()
	void pushAllPost(Post* n) {
		this->AllPost.push_back(n); 
	}		//�K�[�s post

};