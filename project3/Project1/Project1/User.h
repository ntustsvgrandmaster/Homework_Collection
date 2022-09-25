#pragma once
#include <vector>
#include <string>
#include "Post.h"

struct Conversation
{
    string receiver;
    string title;
    vector<string> content;
    Conversation()
    {

    }
    Conversation(string name)
    {
        this->receiver = name;
    }

};

struct myPost
{
    int  postsID;
    int  postBoxID;
    string boardName;
    string title;
    myPost()
    {
        postsID = 0;
        boardName = "";
    }
    myPost(int a, string text, string text2)
    {
        this->postsID = a;
        this->boardName = text;
        this->title = text2;
    }

};


class User {
protected:
    int pCoin;
    int PermissionLevel;    //AD = 1,MB = 2, GU = 3 
    std::string userName;
    std::string passWord;
    std::vector<myPost> postBox;
    std::vector<Conversation> mailArr;
public:
    bool loaded = false;
public:
    User() {
        pCoin = 0;
        PermissionLevel = 9999999;
    };

    std::string getName() { return this->userName; }
    std::string getPass() { return this->passWord; }
    int getPermission() { return this->PermissionLevel; }
    int getMailAmt() { return this->mailArr.size(); }
    int getCoin() { return this->pCoin; }
    int getPostnum() { return postBox.size(); }
    Conversation* getThisMail(int i) { return &this->mailArr[i]; }
    myPost* getThisPost(int i) { return &this->postBox[i]; }
    void newConv(Conversation conv) { this->mailArr.push_back(conv); }
    void newPost(myPost p) { postBox.push_back(p); }
    void deletePost(int n) { postBox.erase(postBox.begin() + n); }
    void setCoin(int i) { this->pCoin = i; }
    void setPass(std::string p) { this->passWord = p; }
    void setUserName(std::string u) { this->userName = u; }
};

class Administrator : public User
{
public:
    Administrator() {
        pCoin = 0;
        PermissionLevel = 1;
    };
    Administrator(std::string _userName, std::string _passWord);
};

class Member : public User
{
public:
    Member() {
        pCoin = 0;
        PermissionLevel = 2;
    };
    Member(std::string _userName, std::string _passWord);
};

class Guest : public User
{
public:
    Guest();
};