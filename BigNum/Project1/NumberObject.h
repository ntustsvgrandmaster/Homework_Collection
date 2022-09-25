#pragma once
#include "BigNum.h"
#include "operators.h"
#include <string>
#include <stack>
#include <vector>
#include<iostream>

extern bool dot;  //���ɮץ����ܼ�

enum numORoperator {
    num, op
};

class NumberObject			//�Ʀr   --parent���O
{
protected:
    std::string type;
    std::string name;
    BigNumber numerator;		//���l
    BigNumber denominator;		//����

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


//�B�z�B��
//�ǤJ�Ȭ��u���B�⤺�e���r��
void operating(std::string, std::stack<NumberObject>& NumObStack, std::stack<myOperator> opStack, const std::vector<NumberObject*> NumList);
//�̾ڹB��l�Ӱ����P���B��
void calculate(std::string, std::stack<NumberObject>& NumObStack);

extern std::vector<NumberObject*> NumList;