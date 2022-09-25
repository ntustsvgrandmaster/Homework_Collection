#include <string>
#include "BigNum.h"
#include "NumberObject.h"

std::string NumberObject::getName()
{
	return this->name;
}

BigNumber NumberObject::getNum()
{
	return divis(numerator, denominator);
}

NumberObject::NumberObject(BigNumber bg)
{
	numerator = bg;
	denominator = Change("1");
}

NumberObject::NumberObject()
{
	numerator = Change("0");
	denominator = Change("1");
}


NumberObject::NumberObject(BigNumber nu, BigNumber de)
{
	numerator = nu;
	denominator = de;
}

void NumberObject::setName(std::string lname)
{
	this->name = lname;
}

void NumberObject::setNumerator(BigNumber nu)
{
	this->numerator = nu;
}

void NumberObject::setDenominator(BigNumber de)
{
	this->denominator = de;
}

BigNumber NumberObject::getNumerator()
{
	return numerator;
}

BigNumber NumberObject::getDenomiator()
{
	return denominator;
}

void operating(std::string str, std::stack<NumberObject>& NumObStack, std::stack<myOperator> opStack, const std::vector<NumberObject*> NumList)
{
	int curr = 0;
	int subEnd = 0; //子字串的尾端
	numORoperator no = numORoperator::op;

	while (curr < str.length())
	{
		while (str[subEnd] != ' ' && subEnd < str.length())
		{
			subEnd++;
		}
		std::string sub = str.substr(curr, subEnd - curr);

		if (sub == "+")
		{
			//先判斷是s+還是+
			bool sign = false;
			if (no == op)
			{
				sign = true;
			}
			else
			{
				if (!opStack.empty() && (opStack.top().op == ")" || opStack.top().op == "!"))
				{
					sign = true;
				}
			}

			if (sign == true)
			{
				opStack.push(myOperator("s+", 4));
			}
			else if (sign == false)
			{
				while (!opStack.empty() && opStack.top().priority <= 6 && opStack.top().op != "(") //遇到優先順序比自己小、等於自己的就pop
				{
					calculate(opStack.top().op, NumObStack);
					opStack.pop();
				}
				opStack.push(myOperator(sub, 6));
			}
			no = numORoperator::op;
		}
		else if (sub == "-")
		{
			//先判斷是s-還是-			
			bool sign = false;
			if (no == op)
			{
				sign = true;
			}
			else
			{
				if (!opStack.empty() && (opStack.top().op == ")" || opStack.top().op == "!"))
				{
					sign = true;
				}
			}

			if (sign == true)
			{
				opStack.push(myOperator("s-", 4));
			}
			else if (sign == false)
			{
				while (!opStack.empty() && opStack.top().priority <= 6 && opStack.top().op != "(") //遇到優先順序比自己小、等於自己的就pop
				{
					calculate(opStack.top().op, NumObStack);
					opStack.pop();
				}
				opStack.push(myOperator(sub, 6));
			}
			no = numORoperator::op;
		}
		else if (sub == "*")
		{
			try {
				if (NumObStack.empty()) throw "invalid operate";
				if (no == numORoperator::op) throw "invalid op";
			}
			catch (const char* errorOutput) {
				std::cout << errorOutput;
				while (!NumObStack.empty()) NumObStack.pop();
				return;
			}


			while (!opStack.empty() && opStack.top().priority <= 5 && opStack.top().op != "(") //遇到優先順序比自己小、等於自己的就pop
			{
				calculate(opStack.top().op, NumObStack);
				opStack.pop();
			}
			opStack.push(myOperator(sub, 5));
			no = numORoperator::op;
		}
		else if (sub == "/")
		{
			try {
				if (NumObStack.empty()) throw "invalid operate";
				if (no == numORoperator::op) throw "invalid op";
			}
			catch (const char* errorOutput) {
				std::cout << errorOutput;
				while (!NumObStack.empty()) NumObStack.pop();
				return;
			}

			while (!opStack.empty() && opStack.top().priority <= 5 && opStack.top().op != "(") //遇到優先順序比自己小、等於自己的就pop
			{
				calculate(opStack.top().op, NumObStack);
				opStack.pop();
			}
			opStack.push(myOperator(sub, 5));
			no = numORoperator::op;
		}
		else if (sub == "(")
		{
			opStack.push(myOperator(sub, 1)); //無條件push
			no = numORoperator::op;
		}
		else if (sub == ")")
		{
			try {
				if (NumObStack.empty()) throw "invalid operate";
			}
			catch (const char* errorOutput) {
				std::cout << errorOutput;
				while (!NumObStack.empty()) NumObStack.pop();
				return;
			}

			//一直pop直到遇到左括號
			while (opStack.top().op != "(")
			{
				calculate(opStack.top().op, NumObStack);
				opStack.pop();
			}
			opStack.pop(); //把"("給pop出去
			no = numORoperator::num;
		}
		else if (sub == "!")
		{
			try {
				if (NumObStack.empty()) throw "invalid operate";
			}
			catch (const char* errorOutput) {
				std::cout << errorOutput;
				while (!NumObStack.empty()) NumObStack.pop();
				return;
			}

			NumberObject n = NumObStack.top();
			BigNumber i;
			i = divis(n.getNumerator(), n.getDenomiator());
			try
			{
				if (i.hl != -1 || i.neg == 1)       //防呆 -非正整數
				{
					throw"calculate failed\nPlease input again!";
				}

			}
			catch (const char* errorOutput) {
				std::cout << errorOutput << std::endl;
				//出問題了就全Pop讓main可以停止，不然會炸
				while (!NumObStack.empty()) NumObStack.pop();
				return;
			}

			calculate(sub, NumObStack);
			no = numORoperator::op;
		}
		else if (sub == "^")
		{
			try {
				if (NumObStack.empty()) throw "invalid operate";
			}
			catch (const char* errorOutput) {
				std::cout << errorOutput;
				while (!NumObStack.empty()) NumObStack.pop();
				return;
			}

			opStack.push(myOperator(sub, 3));
			no = numORoperator::op;
		}
		else   //是數字或變數
		{
			try
			{
				if (no == numORoperator::num) throw "error, number can't connect with other number.";
			}
			catch (const char* errorOutput)
			{
				std::cout << errorOutput;
				while (!NumObStack.empty()) NumObStack.pop();
				return;
			}

			if (sub[0] >= '0' && sub[0] <= '9') //是數字
			{
				NumObStack.push(NumberObject(Change(sub)));
				no = numORoperator::num;
			}
			else //是變數
			{
				int search = 0;
				for (search = 0; search < NumList.size(); search++)
				{
					if (NumList[search]->getName() == sub)
					{
						break;
					}
				}
				try
				{
					if (search == NumList.size())       //防呆 -變數不存在
					{
						throw"variable does not exist!\nPlease input again!";
					}

				}
				catch (const char* errorOutput) {
					std::cout << errorOutput << std::endl;
					//出問題了就全Pop讓main可以停止，不然會炸
					while (!NumObStack.empty()) NumObStack.pop();
					return;
				}

				//把變數的值取出來，放到stack中
				NumObStack.push(NumberObject(NumList[search]->getNumerator(), NumList[search]->getDenomiator()));
				no = numORoperator::num;
			}
		}

		subEnd++;
		curr = subEnd;
	}

	while (!opStack.empty())
	{
		calculate(opStack.top().op, NumObStack);
		opStack.pop();
	}
}

void calculate(std::string op, std::stack<NumberObject>& NumObStack)
{
	if (op == "+")
	{
		NumberObject right = NumObStack.top();
		NumObStack.pop();
		NumberObject left = NumObStack.top();
		NumObStack.pop();
		NumObStack.push(left + right);
	}
	else if (op == "-")
	{
		NumberObject right = NumObStack.top();
		NumObStack.pop();
		NumberObject left = NumObStack.top();
		NumObStack.pop();

		NumObStack.push(left - right);
	}
	else if (op == "*")
	{
		NumberObject right = NumObStack.top();
		NumObStack.pop();
		NumberObject left = NumObStack.top();
		NumObStack.pop();

		NumObStack.push(left * right);
	}
	else if (op == "/")
	{
		NumberObject right = NumObStack.top();
		try
		{
			if (right.getNumerator().pl == -1 && right.getNumerator().hl == -1)       //防呆 -分母為0。
			{
				throw"Denomiator cant't be zero!\nPlease input again!";
			}
		}
		catch (const char* errorOutput)
		{
			std::cout << errorOutput;
			//出問題了就全Pop讓main可以停止，不然會炸
			while (!NumObStack.empty()) NumObStack.pop();
			return;
		}
		NumObStack.pop();
		NumberObject left = NumObStack.top();
		NumObStack.pop();

		NumObStack.push(left / right);
	}
	else if (op == "s+")
	{

	}
	else if (op == "s-")
	{
		NumberObject n = NumObStack.top();
		BigNumber bg = n.getNumerator();
		NumObStack.pop();

		if (bg.neg == 1)
		{
			bg.neg = 0;
		}
		else
		{
			bg.neg = 1;
		}

		n.setNumerator(bg);
		NumObStack.push(n);
	}
	else if (op == "!")
	{
		NumberObject n = NumObStack.top();
		NumObStack.pop();

		NumObStack.push(!n);
	}
	else if (op == "^")
	{
		NumberObject right = NumObStack.top();
		NumObStack.pop();
		NumberObject left = NumObStack.top();
		NumObStack.pop();

		NumObStack.push(left ^ right);
	}
}

NumberObject& NumberObject::operator+(const NumberObject& A)
{
	NumberObject* B = new NumberObject;
	//通分相加
	B->numerator = addit((multi(this->numerator, A.denominator)), (multi(this->denominator, A.numerator)));
	B->denominator = multi(this->denominator, A.denominator);
	return *B;
}
NumberObject& NumberObject::operator-(const NumberObject& A)
{
	NumberObject* B = new NumberObject;
	//通分相減
	B->numerator = minus((multi(this->numerator, A.denominator)), (multi(this->denominator, A.numerator)));
	B->denominator = multi(this->denominator, A.denominator);
	return *B;
}
NumberObject& NumberObject::operator*(const NumberObject& A)
{
	NumberObject* B = new NumberObject;
	//通分，分子乘分子，分母乘分母
	B->numerator = multi(this->numerator, A.numerator);
	B->denominator = multi(this->denominator, A.denominator);
	return *B;
}
NumberObject& NumberObject::operator/(const NumberObject& A)
{
	NumberObject* B = new NumberObject;
	//通分，分子乘分母，分母乘分子
	B->numerator = multi(this->numerator, A.denominator);
	B->denominator = multi(this->denominator, A.numerator);
	return *B;
}
NumberObject& NumberObject::operator^(const NumberObject& A) {
	BigNumber newA;
	newA = divis(A.numerator, A.denominator);
	NumberObject* B = new NumberObject;
	//分子分母各自做指數
	B->numerator = power(this->numerator, newA);
	B->denominator = power(this->denominator, newA);
	return *B;
}
NumberObject& NumberObject::operator=(const NumberObject& A) {
	NumberObject* B = new NumberObject;
	B->numerator = A.numerator;
	B->denominator = A.denominator;
	return *B;
}
NumberObject& NumberObject::operator!()
{
	NumberObject* B = new NumberObject;
	//check 是否為整數做階乘
	BigNumber checkInt = this->getNum();
	for (int i = 0; i < HL; i++) {
		if (checkInt.hv[i] != 0) {
			std::cout << "fractorial must be integer" << std::endl;
			return *B;
		}
	}
	//分子做階乘，分母預設為1
	B->numerator = factorial(checkInt);
	return *B;
}

std::ostream& operator<<(std::ostream& is, NumberObject A)
{
	if (A.type == "Decimal")
	{
		dot = true;
		Print(A.getNum());
		return is;
	}
	else if (A.type == "Integer")
	{
		dot = false;
		Print(A.getNum());
		return is;
	}
	else
	{
		Print(A.getNum());
		is << std::endl;
		return is;
	}
}