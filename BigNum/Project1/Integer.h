#pragma once

#define L 100
#include "NumberObject.h"
#include <string>

class Integer : public NumberObject
{
private:

public:
	Integer();
	Integer(std::string name);
	friend std::istream& operator>>(std::istream& is, Integer& A);
	Integer(const char[]);
	void setNumerator(BigNumber);
	void setDenominator(BigNumber);
	//BigNumber getNum();
	friend std::ostream& operator<<(std::ostream& os, Integer A);
};

Integer::Integer(std::string name)		//初始化變數名字的constructor
{
	this->type = "Integer";
	setName(name);
}

Integer::Integer()
{
}

Integer::Integer(const char a[])
{
	std::string str(a);
	std::stack<NumberObject> NumObStack;
	std::stack<myOperator> opStack;

	operating(str, NumObStack, opStack, NumList);

	this->setNumerator(NumObStack.top().getNumerator());
	this->setDenominator(NumObStack.top().getDenomiator());
}

std::istream& operator>>(std::istream& is, Integer& A)
{
	std::string input1, input2;
	is >> input1;
	int i;
	for (i = 0; i < input1.length(); i++)
	{
		if (input1[i] == '.')
		{
			break;
		}
	}
	for (int j = i; j < input1.length(); j++)
	{
		input1[j] = 0;
	}
	for (int k = 0; input1[k] != '\0'; k++)
	{
		input2 = input2 + input1[k];
	}
	A.setNumerator(Change(input2));
	return is;
}

//
void Integer::setNumerator(BigNumber bg)
{
	this->numerator = bg;
}

//強制將分母設為1
void Integer::setDenominator(BigNumber bg)
{
	this->denominator = bg;

	BigNumber de;
	de = divis(numerator, denominator);
	de.neg = numerator.neg ^ denominator.neg;
	de.hl = -1;
	for (int i = 0; i < HL; i++)
	{
		bg.hv[i] = 0;
	}
	this->numerator = de;
	this->denominator = Change("1");
}

std::ostream& operator<<(std::ostream& os, Integer A)
{
	dot = false;
	Print(A.getNum());
	//dot = false;
	return os;
}