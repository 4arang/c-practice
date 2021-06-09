#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "acctabc.h"
using std::cout;
using std::endl;
using std::string;
using std::ios_base;

AcctABC::AcctABC(const string & s, long an, double bal)
{
	fullName = s;
	acctNum = an;
	balance = bal;
}
void AcctABC::Deposit(double amt)
{
	if (amt < 0)
		cout << "마이너스 입금은 허용되지 않습니다.\n"
		<< "그래서 입금이 취소되었습니다.\n";
	else
		balance += amt;
}

void AcctABC::Withdraw(double amt)
{
	balance -= amt;
}

AcctABC::Formatting AcctABC::SetFormat() const
{
	Formatting f;
	f.flag = cout.setf(ios_base::fixed, ios_base::floatfield);
	f.pr = cout.precision(2);
	return f;
}
void AcctABC::restore(Formatting & f) const
{
	cout.setf(f.flag, ios_base::floatfield);
	cout.precision(f.pr);
}

void Brass::Withdraw(double amt)
{

	if (amt < 0)
		cout << "마이너스 인출은 허용되지 않습니다.\n"
		<< "그래서 인출이 취소되었습니다.\n";
	else if (amt <= Balance())
		AcctABC::Withdraw(amt);
	else
		cout << "인출을 요구한 금액 $" << amt
		<< "가 현재 잔액을 초과합니다.\n"
		<< "그래서 인출이 취소되었습니다.\n";

}


void Brass::ViewAcct() const
{
	Formatting f = SetFormat();
	cout << "Brass 고객: " << FullName() << endl;
	cout << "계좌 번호: " << AcctNum() << endl;
	cout << "현재 잔액: $" << Balance() << endl;
	restore(f);
}

BrassPlus::BrassPlus(const std::string &s, long an, double bal,
	double ml, double r) : AcctABC(s, an, bal)
{
	maxLoan = ml;
	owesBank = 0.0;
	rate = r;
}

BrassPlus::BrassPlus(const Brass &ba, double ml, double r) : AcctABC(ba)
{
	maxLoan = ml;
	owesBank = 0.0;
	rate = r;
}
void BrassPlus::Withdraw(double amt)
{
	Formatting f = SetFormat();
	double bal = Balance();
	if (amt <= bal)
		AcctABC::Withdraw(amt);
	else if (amt <= bal + maxLoan - owesBank)
	{
		double advance = amt - bal;
		owesBank += advance * (1.0 + rate);
		cout << "당좌 대월 금액: $" << advance << endl;
		cout << "당좌 대월 이자: $" << advance * rate << endl;
		Deposit(advance);
		AcctABC::Withdraw(amt);
	}
	else
		cout << "당좌 대월 한도가 초과되어 거래가 취소되었습니다.\n";
	restore(f);
}
void BrassPlus::ViewAcct() const
{
	Formatting f = SetFormat();

	cout << "BrassPlus 고객: " << FullName() << endl;
	cout << "계좌 번호: " << AcctNum() << endl;
	cout << "현재 잔액: $" << Balance() << endl;
	cout << "당좌 대월 한도액: $" << maxLoan << endl;
	cout << "상환할 원리금: $" << owesBank << endl;
	cout.precision(3);
	cout << "당좌 대월 이자율: " << 100 * rate << "%\n";
	restore(f);
}

