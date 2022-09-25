#pragma once
#include <iostream>
#include <conio.h>
#include <fstream>
#include "Board.h"
#include "User.h"

void SetColor(int color = 7);

class Viewer {
private:
public:
    void printMenu(bool& moved);
    void printSelector(int permission, std::vector<Board*>& bv, int nowViewing,int menu);
    void printBoard(int permission, Board& bd, int nowViewing);
    void printPost(int permission, Board& bd, int postID);
    void printDeleteComment(int permission, Board& bd, int postID, int nowViewing);
    void printMailBox(User& us, int now);
    void printMail(Conversation& conv);
    void printPost(User& us, int now);
    void printPostBox(User& us,int now);
    void editMail(bool& edit, bool& send, std::string& str, std::vector<std::string>& content);
    void editPost(bool& edit, bool& send, std::string& str, std::vector<std::string>& content);
};