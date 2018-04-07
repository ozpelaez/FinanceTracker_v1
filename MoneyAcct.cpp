// MoneyAcct keeps track of the owner of the account, the amount of money 
// available in the account, and tax owed based on transactions made with
// account.

#include "stdafx.h"
#include "MoneyAcct.h"


MoneyAcct::MoneyAcct()
{
	owner = "Change needed";
	currentBalance = 0.00;
	taxBalance = 0.00;
}

MoneyAcct::MoneyAcct(string name)
{
	owner = name;
	currentBalance = 0.00;
	taxBalance = 0.00;
}

void MoneyAcct::setOwner(string name) 
{
	owner = name;
}

void MoneyAcct::setBalance(double funds, double taxable)
{
	currentBalance = funds;
	taxBalance = taxable;
}

// bankMoney adds/removes money from account without affecting tax bill balance
void MoneyAcct::bankMoney(double money)
{
	currentBalance += money;
}

// transaction adds/removes money from account and affects tax bill balance. This is
// representative of a capital gain/loss.
void MoneyAcct::transaction(double money)
{
	currentBalance += money;
	taxBalance += money;
}

double MoneyAcct::getCurBal()
{
	return currentBalance;
}

double MoneyAcct::getTaxBal()
{
	return taxBalance;
}

string MoneyAcct::getOwner()
{
	return owner;
}

MoneyAcct::~MoneyAcct()
{
}
