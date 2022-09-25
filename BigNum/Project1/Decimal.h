#pragma once

#define L 100
#include "NumberObject.h"
#include <string>

class Decimal : public NumberObject
{
private:

public:
	Decimal();
	Decimal(std::string name);
	friend std::istream& operator>>(std::istream& is, Decimal& A);
	Decimal(const char[]);
	void setNumerator(BigNumber);
	void setDenominator(BigNumber);
	BigNumber getNum();
	BigNumber getNumerator();
	BigNumber getDenominator();
	friend std::ostream& operator<<(std::ostream& os, Decimal A);
};

Decimal::Decimal(std::string name)		//初始化變數名字的constructor
{
	this->type = "Decimal";
	this->setName(name);
}

Decimal::Decimal()
{
}

Decimal::Decimal(const char a[])
{
	std::string str(a);
	std::stack<NumberObject> NumObStack;
	std::stack<myOperator> opStack;

	operating(str, NumObStack, opStack, NumList);

	this->setNumerator(NumObStack.top().getNumerator());
	this->setDenominator(NumObStack.top().getDenomiator());
}

std::istream& operator>>(std::istream& is, Decimal& A)
{
	std::string input;
	is >> input;
	A.setNumerator(Change(input));
	return is;
}

void Decimal::setNumerator(BigNumber bg) {
	this->numerator = bg;
	this->numerator.hl = 99;
}

void Decimal::setDenominator(BigNumber bg) {
	this->denominator = bg;
	this->denominator.hl = 99;
}

BigNumber Decimal::getNum()
{
	BigNumber bg = divis(numerator, denominator);
	dot = true;
	return bg;
}

BigNumber Decimal::getNumerator() {
	dot = true;
	return this->numerator;
}

BigNumber Decimal::getDenominator() {
	dot = true;
	return this->denominator;
}

std::ostream& operator<<(std::ostream& os, Decimal A)
{
	printf("hi\n");
	dot = true;
	Print(A.getNum());
	//dot = false;
	return os;
}