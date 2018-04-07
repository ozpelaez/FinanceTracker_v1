#pragma once
#include <string>

using namespace std;

class MoneyAcct
{
public:
	MoneyAcct();
	MoneyAcct(string name);
	~MoneyAcct();
	void setOwner(string name);
	void setBalance(double funds, double taxable);
	
	// bankMoney adds/removes money from account without affecting tax bill balance
	void bankMoney(double money);
	
	// transaction adds/removes money from account and affects tax bill balance. This is
	// representative of a capital gain/loss.
	void transaction(double money);
	double getCurBal();
	double getTaxBal();
	string getOwner();

private:
	string owner;
	
	// currentBalance is the amount of equity available. 
	double currentBalance;

	// taxBalance keeps a running tab on taxable income. This ignores deposits/withdrawals from
	// brokerage account.
	double taxBalance;
};

