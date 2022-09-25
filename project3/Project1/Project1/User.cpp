#include "User.h"

Administrator::Administrator(std::string _userName, std::string _passWord)
{
    this->pCoin = 0;
    //this->postsID.push_back(postID);
    this->userName = _userName;
    this->passWord = _passWord;
    this->PermissionLevel = 1;
}
Member::Member(std::string _userName, std::string _passWord)
{
    this->pCoin = 0;
    //this->postsID.push_back(postID);
    this->userName = _userName;
    this->passWord = _passWord;
    this->PermissionLevel = 2;
}
Guest::Guest()
{
    this->PermissionLevel = 3;
}