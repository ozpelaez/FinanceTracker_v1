// Option 4 asks for an account name and reads in the account's rawinfo.txt file.

#include "stdafx.h"

using namespace std;

void option4() {
	string name;

	cout << "\n \n      Name of account owner: ";
	cin >> name;
	MoneyAcct acct(name);

	Filer go(acct);

	go.readRawTransac();
	go.makeFormTransac();
	go.makeFormAcct(acct);

}