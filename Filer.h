#pragma once
#include "stdafx.h"

using namespace std;

class Filer
{
public:
	Filer(MoneyAcct owner, vector<Transaction> action);
	Filer(MoneyAcct owner);
	void makeRawTransac();
	void readRawTransac();
	void makeFormTransac();
	void makeFormAcct(MoneyAcct owner);
	void addToBookkeeper(Transaction addition);
	void printBookkeeper();
	~Filer();

private:
	string acctOwner;
	string rawfilename;
	string transfilename;
	string acctfilename;
	vector<Transaction> bookkeeper;
};

