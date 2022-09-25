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
	int getPostIDs(int n) { return this->postIDs[n]; }			//回傳第n篇貼文的 postIDs。
	void setPostIDs(int n, int s) { this->postIDs[n] = s; }		//設定第n篇貼文的 postIDs。
	void pushPostIDs(int n) { this->postIDs.push_back(n); }			//添加新 postID
	Post* getPost(int n) { return this->AllPost[n]; }		//回傳第n篇貼文的 post指標。
	vector<Post*>::iterator getAllPostBegin() { return this->AllPost.begin(); }		//得到 AllPost.begin()
	vector<Post*>::iterator getAllPostEnd() { return this->AllPost.end(); }			//得到 AllPost.end()
	void pushAllPost(Post* n) {
		this->AllPost.push_back(n); 
	}		//添加新 post

};