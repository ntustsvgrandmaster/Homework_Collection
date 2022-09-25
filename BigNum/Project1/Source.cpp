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
    //����
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
        if (commend.length() >= 4 && commend.substr(0, 4) == "Set ")       // 1. Set �ܼ�
        {
            std::string varibleName;
            int index = 12;                         //�e���Ointeger/decimal
            for (; commend[index] != ' '; index++)  //���o�B�x�s�ܼƦW��
            {
                varibleName.push_back(commend[index]);
            }
            //�ˬd�ܼƦW�٬O�_�X�k
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

            //�ˬd�ܼƬO�_�w�s�b
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

            //��o�᭱���B�⦡string  --calculatePart
            std::string calculatePart;
            index = index + 3;
            for (; commend[index] != '\0'; index++)
            {
                if (commend[index] == '.') dot = true;
                calculatePart.push_back(commend[index]);
            }

            try {

                if (commend.substr(4, 8) == "Integer ")        //Set ��� 
                {
                    /****�ھ�varibleName �Ыؤ@��ƪ���A�s�J vector<NumberObject*> ***/
                    NumList.push_back(new Integer(varibleName));
                    listLen++;
                    dot = false;
                    /*************************************/
                }
                else if (commend.substr(4, 8) == "Decimal ")     //Set �p�� 
                {
                    /****�ھ�varibleName �Ыؤ@�p�ƪ���A�s�J vector<NumberObject*> ***/
                    NumList.push_back(new Decimal(varibleName));
                    listLen++;
                    /*************************************/
                }
                else
                {
                    /*���Ointeger/decimal�A����*/
                    throw"not valid type\n";
                }
            }       //try end
            catch (const char* errorOutput) {
                std::cout << errorOutput;
                continue;
            }

            /**********�N calculatePart �@�@���Ѧs�J�Ʀr���|�βŸ����|*********/
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
        else        // 2. A = �B�⦡�B 3. �¹B�⦡
        {
            /****�B�⦡ (calculatePart) ���x�s****/
            int index = 0;
            int type = 2;
            dot = false;
            for (; index < commend.length() && commend[index] != '='; index++)
            {

            }
            if (commend[index] != '=')      // �ĤT�اΦ�  --�¹B�⦡
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
            /*********�p�� calculatePart ***/

            std::stack<NumberObject> NumObStack;
            std::stack<myOperator> opStack;

            operating(calculatePart, NumObStack, opStack, NumList);

            /******************************/
            if (!NumObStack.empty())
            {
                /***�Y�� A = 1 + 2 �Φ��A�ھ��ܼƦW�٧�쪫��A�N���G�s�J����***/
                if (type == 2)
                {
                    std::string varibleName;
                    for (int i = 0; commend[i] != ' '; i++)      //�x�s�ܼƦW��
                    {
                        varibleName.push_back(commend[i]);
                    }
                    /******�s�J����******/
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
                        if (search == NumList.size())       //���b -�ܼƤ��s�b
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
                else if (type == 3)     /***�Y����¹B�⦡�A�Ыؤ@�p�Ʃξ�ƪ���A�N���G�s�J����A�è̷ӫ��w�榡��X�C***/
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