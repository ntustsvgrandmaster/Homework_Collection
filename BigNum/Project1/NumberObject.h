#pragma once
#include "BigNum.h"
#include "operators.h"
#include <string>
#include <stack>
#include <vector>
#include<iostream>

extern bool dot;  //跨檔案全域變數

enum numORoperator {
    num, op
};

class NumberObject			//數字   --parent型別
{
protected:
    std::string type;
    std::string name;
    BigNumber numerator;		//分子
    BigNumber denominator;		//分母

    //std::stack<myOperator> opStack;
    //std::stack<BigNumber> bgStack;
public:
    NumberObject();
    NumberObject(BigNumber bg);
    NumberObject(BigNumber, BigNumber);
    std::string getName();
    void setName(std::string lname);
    virtual void setNumerator(BigNumber);
    virtual void setDenominator(BigNumber);
    virtual BigNumber getNum();
    virtual BigNumber getNumerator();
    virtual BigNumber getDenomiator();
    NumberObject& operator+(const NumberObject& A);
    NumberObject& operator-(const NumberObject& A);
    NumberObject& operator*(const NumberObject& A);
    NumberObject& operator/(const NumberObject& A);
    NumberObject& operator^(const NumberObject& A);
    NumberObject& operator=(const NumberObject& A);
    NumberObject& operator!();
    friend std::ostream& operator<<(std::ostream& is, NumberObject A);
};


//處理運算
//傳入值為只有運算內容的字串
void operating(std::string, std::stack<NumberObject>& NumObStack, std::stack<myOperator> opStack, const std::vector<NumberObject*> NumList);
//依據運算子來做不同的運算
void calculate(std::string, std::stack<NumberObject>& NumObStack);

extern std::vector<NumberObject*> NumList;