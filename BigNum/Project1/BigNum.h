#pragma once
#define HL 100
#define PL 1000
#include <string>

struct BigNumber
{
    char neg = 0;		//�x�s���t��                 /*123.456*/
    int pv[PL] = { 0 }, pl = 0;		//pl �Opv������          /*321*/
    int hv[HL] = { 0 }, hl = 0;		//hl �Ohv������          /*456*/
    //BigNumber operator+(const BigNumber&);
    //BigNumber operator-(const BigNumber&);
    //BigNumber operator*(const BigNumber&);
    //BigNumber operator/(const BigNumber&);
};

BigNumber Change(std::string s);      //�N���ରbignumber�Φ�
void Print(BigNumber A);
int compare(BigNumber A, BigNumber B);
BigNumber addit(BigNumber A, BigNumber B);
BigNumber minus(BigNumber A, BigNumber B);
BigNumber multi(BigNumber A, BigNumber B);
BigNumber divis(BigNumber A, BigNumber B);
BigNumber msqrt(BigNumber A);
BigNumber factorial(BigNumber A);
BigNumber power(BigNumber A, BigNumber B);