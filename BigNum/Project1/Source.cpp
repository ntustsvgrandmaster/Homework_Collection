/******************************************************************************
// Date: Aprl 22 , 2021
// Last Update: Aprl 26 , 2021
// Problem statement: This C++ program  is bignumber calculator.
*******************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "BigNum.h"
#include "NumberObject.h"
#include "Integer.h"
#include "Decimal.h"

bool dot = false;
std::vector<NumberObject*> NumList;

int main()
{
    /*Integer i;
    Decimal d;
    std::cin >> i >> d;
    std::cout << i / d;
    char c;
    c = getchar();
    */
    //美化
    system("color 3F");

    std::string commend;
    int listLen = 0;
    while (std::getline(std::cin, commend))
    {
        dot = false;
        int openParenthesis = 0, closeParenthesis = 0;
        for (int i = 0; i < commend.length(); i++) {
            if (commend[i] == '(') {
                openParenthesis++;
            }
            if (commend[i] == ')') {
                closeParenthesis++;
            }
        }
        try {
            if (openParenthesis != closeParenthesis) {
                throw"parenthesis error";
            }
        }
        catch (const char* parenthesisError) {
            std::cout << parenthesisError << std::endl;
            continue;
        }
        if (commend.length() >= 4 && commend.substr(0, 4) == "Set ")       // 1. Set 變數
        {
            std::string varibleName;
            int index = 12;                         //前面是integer/decimal
            for (; commend[index] != ' '; index++)  //取得、儲存變數名稱
            {
                varibleName.push_back(commend[index]);
            }
            //檢查變數名稱是否合法
            try {
                if (varibleName[0] >= '0' && varibleName[0] <= '9')
                {
                    throw "invalid variable name\n";
                }
            }
            catch (const char* errorOutput) {
                std::cout << errorOutput;
                continue;
            }

            //檢查變數是否已存在
            try {
                for (int i = 0; i < NumList.size(); i++)
                {
                    if (varibleName == NumList[i]->getName())
                    {
                        throw "this variable has already existed\n";
                        break;
                    }
                }
            }
            catch (const char* errorOutput) {
                std::cout << errorOutput;
                continue;
            }

            //獲得後面的運算式string  --calculatePart
            std::string calculatePart;
            index = index + 3;
            for (; commend[index] != '\0'; index++)
            {
                if (commend[index] == '.') dot = true;
                calculatePart.push_back(commend[index]);
            }

            try {

                if (commend.substr(4, 8) == "Integer ")        //Set 整數 
                {
                    /****根據varibleName 創建一整數物件，存入 vector<NumberObject*> ***/
                    NumList.push_back(new Integer(varibleName));
                    listLen++;
                    dot = false;
                    /*************************************/
                }
                else if (commend.substr(4, 8) == "Decimal ")     //Set 小數 
                {
                    /****根據varibleName 創建一小數物件，存入 vector<NumberObject*> ***/
                    NumList.push_back(new Decimal(varibleName));
                    listLen++;
                    /*************************************/
                }
                else
                {
                    /*不是integer/decimal，報錯*/
                    throw"not valid type\n";
                }
            }       //try end
            catch (const char* errorOutput) {
                std::cout << errorOutput;
                continue;
            }

            /**********將 calculatePart 一一分解存入數字堆疊或符號堆疊*********/
            std::stack<NumberObject> NumObStack;
            std::stack<myOperator> opStack;

            operating(calculatePart, NumObStack, opStack, NumList);
            if (!NumObStack.empty())
            {
                NumList[listLen - 1]->setNumerator(NumObStack.top().getNumerator());
                NumList[listLen - 1]->setDenominator(NumObStack.top().getDenomiator());
            }
            continue;
            /***************************************************************/
        }
        else        // 2. A = 運算式、 3. 純運算式
        {
            /****運算式 (calculatePart) 的儲存****/
            int index = 0;
            int type = 2;
            dot = false;
            for (; index < commend.length() && commend[index] != '='; index++)
            {

            }
            if (commend[index] != '=')      // 第三種形式  --純運算式
            {
                index = -2;
                type = 3;
            }

            std::string calculatePart;
            index += 2;
            for (; commend[index] != '\0'; index++)
            {
                if (commend[index] == '.') dot = true;
                calculatePart.push_back(commend[index]);
            }

            try
            {
                if (calculatePart.length() == 0) throw "nothing";
                bool onlySpace = true;
                for (int i = 0; i < calculatePart.length(); i++)
                {
                    if (calculatePart[i] != ' ') onlySpace = false;
                }
                if (onlySpace) throw "space";
            }
            catch (const char* errorInfo)
            {
                if (!strcmp(errorInfo, "nothing")) std::cout << "can't assign nothing\n";
                if (!strcmp(errorInfo, "space")) std::cout << "can't assing only space\n";
                continue;
            }
            /**************************************/
            /*********計算 calculatePart ***/

            std::stack<NumberObject> NumObStack;
            std::stack<myOperator> opStack;

            operating(calculatePart, NumObStack, opStack, NumList);

            /******************************/
            if (!NumObStack.empty())
            {
                /***若為 A = 1 + 2 形式，根據變數名稱找到物件，將結果存入物件***/
                if (type == 2)
                {
                    std::string varibleName;
                    for (int i = 0; commend[i] != ' '; i++)      //儲存變數名稱
                    {
                        varibleName.push_back(commend[i]);
                    }
                    /******存入物件******/
                    int search = 0;
                    for (search = 0; search < NumList.size(); search++)
                    {
                        if (NumList[search]->getName() == varibleName)
                        {
                            break;
                        }
                    }
                    try
                    {
                        if (search == NumList.size())       //防呆 -變數不存在
                        {
                            throw"variable does not exist!\nPlease input again!\n";
                        }

                    }
                    catch (const char* errorOutput) {
                        std::cout << errorOutput;
                        continue;
                    }

                    NumList[search]->setNumerator(NumObStack.top().getNumerator());
                    NumList[search]->setDenominator(NumObStack.top().getDenomiator());
                    continue;

                    /*********************/
                }
                else if (type == 3)     /***若為單純運算式，創建一小數或整數物件，將結果存入物件，並依照指定格式輸出。***/
                {
                    Print(NumObStack.top().getNum());
                }
            }
        }
        std::cout << std::endl;
        dot = false;
    }
    for (const auto& num : NumList)
    {
        std::cout << *num << std::endl;
    }
    return 0;
}