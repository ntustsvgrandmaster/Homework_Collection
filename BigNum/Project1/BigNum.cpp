#include <string>
#include "BigNum.h"
#include "NumberObject.h"

BigNumber Change(std::string s)      //盢锣bignumberΑ
{
	int a, l = s.length(), cut = l, b, p, h, neg = 0;
	BigNumber C;
	if (s[0] == '-')    neg = 1;
	for (a = 0; a < PL; a++)		C.pv[a] = 0;
	for (a = 0; a < HL; a++)		C.hv[a] = 0;
	for (a = neg; a < l; a++)
		if (s[a] == '.') cut = a;
	for (a = cut - 1, b = 0; a >= neg; a--, b++)
		C.pv[b] = s[a] - '0';
	for (a = cut + 1, b = 0; a < l; a++, b++)
		C.hv[b] = s[a] - '0';
	p = PL - 1, h = HL - 1;
	while (C.pv[p] == 0 && p >= 0) p--;
	while (C.hv[h] == 0 && h >= 0) h--;
	C.pl = p, C.hl = h;
	C.neg = neg;
	return C;
}

void Print(BigNumber A)
{
	int a;
	if (A.neg == 1)    printf("-");
	for (a = A.pl; a >= 0; a--)
	{
		printf("%d", A.pv[a]);
	}
	if (A.pl == -1)    printf("0");
	if ((A.hl != -1) || (dot))		//块Τ计┪块Τ计翴
	{
		if (A.hl != -1)		//块Τ计
		{
			printf(".");
			for (a = 0; a <= A.hl; a++)
			{
				printf("%d", A.hv[a]);
			}
			for (a = 0; a < 99 - A.hl; a++)
			{
				printf("%d", 0);
			}

		}
		else			//块礚计
		{
			if (dot)		//狦块Τ计翴干计翴蛤 0
			{
				printf(".");
				for (a = 0; a <= 99; a++)
				{
					printf("%d", 0);
				}
			}
		}

	}
}
int compare(BigNumber A, BigNumber B)        /*ㄢ常琌タ计*/
{
	int a, h;
	if (A.pl > B.pl) return 1;
	if (A.pl < B.pl) return 0;
	for (a = A.pl; a >= 0; a--)
	{
		if (A.pv[a] > B.pv[a])
			return 1;
		else if (A.pv[a] < B.pv[a])
			return 0;
	}
	for (a = 0; a <= A.hl && a <= B.hl; a++)
	{
		if (A.hv[a] > B.hv[a])
			return 1;
		else if (A.hv[a] < B.hv[a])
			return 0;
	}
	if (A.hl > B.hl) return 1;
	else if (A.hl < B.hl) return 0;
	return 1;
}

BigNumber addit(BigNumber A, BigNumber B)
{
	if (A.neg == 0 && B.neg == 1)
	{
		B.neg = 0; return minus(A, B);
	}
	else if (A.neg == 1 && B.neg == 0)
	{
		A.neg = 0; return minus(B, A);
	}
	int a, p, h;
	BigNumber C;
	C.neg = A.neg;
	for (a = 0; a < PL; a++)		C.pv[a] = 0;
	for (a = 0; a < HL; a++)		C.hv[a] = 0;
	for (a = 0; a <= A.pl; a++)		C.pv[a] += A.pv[a];    /****/
	for (a = 0; a <= B.pl; a++)		C.pv[a] += B.pv[a];
	for (a = 0; a <= A.hl; a++)		C.hv[a] += A.hv[a];
	for (a = 0; a <= B.hl; a++)		C.hv[a] += B.hv[a];

	//秈
	h = (A.hl < B.hl) ? A.hl : B.hl;  /*肚min*/
	if (h == -1)	h = 0;		//タh
	for (a = h; a >= 1; a--)
	{
		C.hv[a - 1] += C.hv[a] / 10, C.hv[a] %= 10;
	}
	C.pv[0] += C.hv[0] / 10, C.hv[0] %= 10;

	p = (A.hl > B.hl) ? A.hl : B.hl;   /*肚max*/
	if (p == -1)	p = 0;		//タp
	for (a = 0; a <= p + 1; a++)
	{
		C.pv[a + 1] += C.pv[a] / 10, C.pv[a] %= 10;
	}

	p = PL - 1, h = HL - 1;         //穝pl,hl
	while (C.pv[p] == 0 && p >= 0)  p--;
	while (C.hv[h] == 0 && h >= 0)  h--;
	C.pl = p, C.hl = h;
	return C;
}

BigNumber minus(BigNumber A, BigNumber B)
{
	if (A.neg == 1 && B.neg == 1)
	{
		B.neg = 0, A.neg = 0; return minus(B, A);
	}
	else if (A.neg == 1 && B.neg == 0)
	{
		A.neg = 0;
		BigNumber C = addit(A, B);
		C.neg = 1;
		return C;
	}
	else if (A.neg == 0 && B.neg == 1)
	{
		B.neg = 0; return addit(A, B);
	}
	if (compare(A, B) == 0)
	{
		A.neg = 0;
		BigNumber C = minus(B, A);
		C.neg = 1;
		return C;
	}
	int a, p, h;            //A-B A>B猵
	BigNumber C;
	for (a = 0; a < PL; a++)		C.pv[a] = 0;
	for (a = 0; a < HL; a++)		C.hv[a] = 0;
	for (a = 0; a <= A.pl; a++)  C.pv[a] = A.pv[a];
	for (a = 0; a <= A.hl; a++)  C.hv[a] = A.hv[a];
	for (a = 0; a <= B.pl; a++)  C.pv[a] -= B.pv[a];
	for (a = 0; a <= B.hl; a++)  C.hv[a] -= B.hv[a];
	for (a = HL - 1; a >= 1; a--)
	{
		while (C.hv[a] < 0)
		{
			C.hv[a - 1]--;
			C.hv[a] += 10;
		}
	}
	while (C.hv[0] < 0)
	{
		C.pv[0]--;
		C.hv[0] += 10;
	}
	for (a = 0; a < PL; a++)
	{
		while (C.pv[a] < 0)
		{
			C.pv[a + 1]--;
			C.pv[a] += 10;
		}
	}
	p = PL - 1, h = HL - 1;
	while (C.pv[p] == 0 && p >= 0)  p--;
	while (C.hv[h] == 0 && h >= 0)  h--;
	C.pl = p, C.hl = h;
	return C;
}

BigNumber multi(BigNumber A, BigNumber B)
{
	BigNumber C;
	int Aa[PL + HL], Bb[PL + HL], Cc[(PL + HL) * 2 + 1] = {};
	int a, b, Al = 0, Bl = 0, p, h;
	for (a = 0; a < PL; a++)
	{
		C.pv[a] = 0;
	}
	for (a = 0; a < HL; a++)
	{
		C.hv[a] = 0;
	}
	for (a = A.hl; a >= 0; a--)    Aa[Al++] = A.hv[a];		//俱计计癬皚
	for (a = 0; a <= A.pl; a++)    Aa[Al++] = A.pv[a];
	for (a = B.hl; a >= 0; a--)    Bb[Bl++] = B.hv[a];
	for (a = 0; a <= B.pl; a++)    Bb[Bl++] = B.pv[a];

	for (a = 0; a < Al; a++)		//AlBl琌计+俱计
	{
		for (b = 0; b < Bl; b++)
		{
			Cc[a + b] += Aa[a] * Bb[b];
		}
	}
	for (a = 0; a < (PL + HL); a++)
	{
		Cc[a + 1] += Cc[a] / 10;
		Cc[a] %= 10;
	}
	int cut = (A.hl + 1) + (B.hl + 1);		//计竚
	for (a = cut, b = 0; a < (PL + HL) * 2 + 1 && b < PL; a++, b++)
	{
		C.pv[b] = Cc[a];
	}
	for (a = cut - 1, b = 0; a >= 0 && b < HL; a--, b++)
	{
		C.hv[b] = Cc[a];
	}

	p = PL - 1, h = HL - 1;
	while (C.pv[p] == 0 && p >= 0)  p--;
	while (C.hv[h] == 0 && h >= 0)  h--;
	C.pl = p, C.hl = h;
	C.neg = A.neg ^ B.neg;
	return C;
}

int Check(int a[], int b[], int lb, int lc)
{
	int i;
	for (i = lb - 1; i >= 0; i--)
	{
		if (a[i + lc] < b[i]) return 0;
		if (a[i + lc] > b[i]) return 1;
	}
	return 1;
}

BigNumber divis(BigNumber A, BigNumber B)
{
	BigNumber C;
	int Aa[PL + PL + HL] = {}, Bb[PL + PL + HL] = {}, Cc[(PL + HL) * 2 + 1] = {};
	int a, b, Al = PL, Bl = 0, p, h, i, j;

	for (a = 0; a < PL; a++)		C.pv[a] = 0;
	for (a = 0; a < HL; a++)		C.hv[a] = 0;
	for (a = A.hl; a >= 0; a--)    Aa[Al++] = A.hv[a];     // 俱计计癬皚
	for (a = 0; a <= A.pl; a++)    Aa[Al++] = A.pv[a];
	for (a = B.hl; a >= 0; a--)    Bb[Bl++] = B.hv[a];
	for (a = 0; a <= B.pl; a++)    Bb[Bl++] = B.pv[a];
	Al++;
	Bl++;

	for (i = Al - Bl; i >= 0; i--)			//Al-1Bl-1琌计+俱计
	{
		while (Check(Aa, Bb, Bl, i))
		{
			Cc[i]++;
			for (j = 0; j < Bl; j++)
			{
				Aa[i + j] -= Bb[j];
				if (Aa[i + j] < 0) {
					Aa[i + j] += 10;
					Aa[i + j + 1]--;
				}
			}
		}
	}

	int cut = PL - B.hl + A.hl;
	for (a = cut, b = 0; a < (PL + HL) * 2 && b < PL; a++, b++)
	{
		C.pv[b] = Cc[a];
	}
	for (a = cut - 1, b = 0; a >= 0 && b < HL; a--, b++)
	{
		C.hv[b] = Cc[a];
	}

	p = PL - 1, h = HL - 1;
	while (C.pv[p] == 0 && p >= 0)  p--;
	while (C.hv[h] == 0 && h >= 0)  h--;
	C.pl = p, C.hl = h;
	C.neg = A.neg ^ B.neg;
	return C;
}

BigNumber msqrt(BigNumber A)                //硂琌秨キよ
{
	BigNumber C;
	int Aa[PL + PL + HL + HL + HL] = {}, Cc[(PL + PL + HL + HL + HL) + 1] = {};
	int a, b, c, d, Al = PL - A.hl - 1, Cl = 0, p, h;
	int cut;
	for (a = 0; a < PL; a++)		C.pv[a] = 0;
	for (a = 0; a < HL; a++)		C.hv[a] = 0;
	for (a = A.hl; a >= 0; a--)    Aa[Al++] = A.hv[a];
	for (a = 0; a <= A.pl; a++)    Aa[Al++] = A.pv[a];

	int B[PL + PL + HL + HL + HL] = {}, top = Al, Bl = 1;

	for (a = (Al - 1) / 2 * 2; a >= 0; a -= 2, Bl++)		//Α秨よ猭
	{
		if (top > a + Bl - 2)
		{
			for (b = 9; b >= 0; b--)		//眖9秨﹍┕т
			{
				int T[PL + PL + HL + HL + HL] = { 0 };
				B[0] = b;
				for (d = 0; d <= Bl; d++)
				{
					T[a + d] += (b * B[d]);
					T[a + d + 1] += (T[a + d] / 10);
					T[a + d] %= 10;
				}
				int find = 0;
				for (c = Bl + a + 1; c >= 0; c--)       //ゑ耕 璝碞琌硂计
				{
					if (Aa[c] > T[c]) { find = 1; break; }
					else if (T[c] > Aa[c]) break;
				}

				if (find == 1 || c == -1)
				{
					for (c = 0; c <= top; c++)      //竊
					{
						Aa[c] -= T[c];
						if (Aa[c] < 0)
						{
							int temp = ((-Aa[c]) / 10 + ((-Aa[c]) % 10 != 0));
							Aa[c] += 10 * temp;
							Aa[c + 1] -= temp;
						}
					}
					break;
				}
			}
		}
		else
		{
			b = 0;
		}
		Cc[Cl++] = b;
		if (a == 1000)    cut = Cl;
		if (top != -1)
		{
			B[0] += b;
			for (b = 0; b <= Bl + 1; b++)
			{
				if (B[b] >= 10)
				{
					B[b + 1] += (B[b] / 10);
					B[b] %= 10;
				}
				else break;
			}
			for (b = Bl + 1; b >= 0; b--)    B[b + 1] = B[b];
			B[0] = 0;
			for (b = top; b >= 0; b--)
			{
				if (Aa[b] != 0) { top = b; break; }
			}
			if (b == -1) top = -1;
		}
	}
	//矪瞶块
	for (a = cut - 1, b = 0; a >= 0 && b < (PL); a--, b++)
	{
		C.pv[b] = Cc[a];
	}
	for (a = cut, b = 0; a < (3 * HL) && b < (HL); a++, b++)
	{
		C.hv[b] = Cc[a];
	}

	p = PL - 1, h = HL - 1;
	while (C.pv[p] == 0 && p >= 0)  p--;
	while (C.hv[h] == 0 && h >= 0)  h--;
	C.pl = p, C.hl = h;
	C.neg = A.neg;
	return C;
}

int checkPvEmpty(const BigNumber& A)
{
	for (int i = PL - 1; i >= 0; i--)
	{
		if (A.pv[i] != 0)
		{
			return 0;
		}
	}
	return 1;
}

BigNumber factorial(BigNumber A)        //顶糷笲衡肚 だ埃だダ BigNumber肚bignumber 砞だbignumberだダ1
{
	BigNumber outputNum;
	BigNumber basicMinus;
	std::string s = "1";
	basicMinus = Change(s);
	outputNum = A;
	if (A.neg == '-')
	{
		//ぃ絋﹚或快
	}
	else
	{
		while (1)
		{
			A = minus(A, basicMinus);
			if (checkPvEmpty(A) == 1)
			{
				break;
			}
			outputNum = multi(outputNum, A);
		}

		return outputNum;
	}
}
BigNumber power(BigNumber A, BigNumber B)
{
	BigNumber C = A;
	BigNumber tmp = B;
	BigNumber one;
	std::string lone = "1";
	one = Change(lone);
	BigNumber two;
	std::string ltwo = "2";
	two = Change(ltwo);
	if (B.hv[0] == 0 && B.neg == 0) {     //Ωよ俱计タ
		while (tmp.neg == 0) {
			C = multi(C, A);
			tmp = minus(tmp, one);
		}
		C = divis(C, A);
		C = divis(C, A);
		return C;
	}
	else if (B.hv[0] == 0 && B.neg == 1) {     //Ωよ俱计璽
		tmp.neg = 0;
		while (tmp.neg == 0) {
			C = multi(C, A);
			tmp = minus(tmp, one);
		}
		C = divis(C, A);
		C = divis(C, A);
		C = divis(one, C);
		return C;
	}
	else if (B.hv[0] == 5 && B.neg == 0) {        //Ωよ计0.5nタ
		tmp = multi(tmp, two);
		while (tmp.neg == 0) {
			C = multi(C, A);
			tmp = minus(tmp, one);
		}
		C = divis(C, A);
		C = divis(C, A);
		C = msqrt(C);
		return C;
	}
	else if (B.hv[0] == 5 && B.neg == 1) {        //Ωよ计0.5n璽
		tmp = multi(tmp, two);
		tmp.neg = 0;
		while (tmp.neg == 0) {
			C = multi(C, A);
			tmp = minus(tmp, one);
		}
		C = divis(C, A);
		C = divis(C, A);
		C = msqrt(C);
		C = divis(one, C);
		return C;
	}
}