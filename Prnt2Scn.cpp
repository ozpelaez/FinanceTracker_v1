#include "stdafx.h"

using namespace std;

void prnt2scn(MoneyAcct ozzie, vector<Transaction> first) {
	
	cout << "        " << ozzie.getOwner() << "'s Account \n \n";
	for (int i = 0; i < first.size(); i++) {

		if (first[i].isSale()) ozzie.transaction(first[i].howMuch());
		else ozzie.bankMoney(first[i].howMuch());

		first[i].acctInfo();
		cout << " " << setprecision(2) << fixed << setw(12) << ozzie.getCurBal() << endl;
	}

}