#include <iostream>
#include <string>
using namespace std;
const int n = 5;
const int m = 6;

// to-do починить

int translit(char c)
{
	if (c >= '0' && c<='9') return 0;
	if (c == 'e' || c=='E') return 1;
	if (c == '.') return 2;
	if (c == '+' || c == '-') return 3;
	if (c == '\0') return 5;
	return 4;
}

class KA
{
	float RCH, RS, RP, RZ;
	bool flag;
	int state;
	char ch;
	string str;
	void (KA::*table[n][m])();
	void P1()
	{
		RCH = ch - '0';
		state = 1;
	}
	void P2()
	{
		RS = 0;
		RCH = 0;
		state = 3;
	}
	void P3()
	{
		RCH = RCH * 10 + ch - '0';
		state = 1;
	}
	void P4()
	{
		RP = 0;
		RS = 0;
		state = 2;
	}
	void P5()
	{
		RS = 0;
		state = 3;
	}
	void P6()
	{
		RP = RP * 10 + ch - '0';
		RZ = 1;
		state = 4;
	}
	void P7()
	{
		if (ch == '+') RZ = 1;
		else
			RZ = -1;
		state = 4;
	}
	void P8()
	{
		RS++;
		RCH = RCH * 10 + ch - '0';
		state = 3;
	}
	void P9()
	{
		RP = 0;
		state = 2;
	}
	void P10()
	{
		RP = RP * 10 + ch - '0';
		state = 4;
	}
	void Error()
	{
		flag = false;
	}
	void ok() {}

public:

	bool start(string str, float &rez)
	{
		int len = str.size();
	    flag = true;
		for (int i = 0; i <= len; i++)
		{
			ch = str[i];
			int j = translit(ch);
			(this->*table[state][j])();
			if (!flag) return flag;


			if (j == 5)
			{
				switch (state)
				{
				case 1:rez = RCH; break;

				case 3:rez = RCH / pow(10, RS); break;

				case 4:
					if (RZ == 1)
						rez = RCH * pow(10, RP - RS);
					if (RZ == -1)
						rez = RCH / pow(10, RP + RS);
					break;

				default: flag = false;
				}
				return flag;
			}
		}
	}	
	KA()
	{
		state = 0;
		table[0][0] = &KA::P1;
		table[0][1] = &KA::Error;
		table[0][2] = &KA::P2;
		table[0][3] = &KA::Error;
		table[0][4] = &KA::Error;
		table[0][5] = &KA::Error;

		table[1][0] = &KA::P3;
		table[1][1] = &KA::P4;
		table[1][2] = &KA::P5;
		table[1][3] = &KA::Error;
		table[1][4] = &KA::Error;
		table[1][5] = &KA::ok;

		table[2][0] = &KA::P6;
		table[2][1] = &KA::Error;
		table[2][2] = &KA::Error;
		table[2][3] = &KA::P7;
		table[2][4] = &KA::Error;
		table[2][5] = &KA::Error;

		table[3][0] = &KA::P8;
		table[3][1] = &KA::P9;
		table[3][2] = &KA::Error;
		table[3][3] = &KA::Error;
		table[3][4] = &KA::Error;
		table[3][5] = &KA::ok;

		table[4][0] = &KA::P10;
		table[4][1] = &KA::Error;
		table[4][2] = &KA::Error;
		table[4][3] = &KA::Error;
		table[4][4] = &KA::Error;
		table[4][5] = &KA::ok;
	}
};


int main()
{
	string test;
	float rez = 0;
	cin >> test;
	KA P;
	if (P.start(test, rez))
		cout <<  rez << "\n";
	else
		cout << "Error\n";

	system("pause");
}