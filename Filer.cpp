// Filer is a class that serves as the file I/O for FinanceTracker v1. It can be
// initialized with a MoneyAcct and a Transaction vector, or just a MoneyAcct.

#include "stdafx.h"
#include "Filer.h"


Filer::Filer(MoneyAcct owner, vector<Transaction> action)
{
	acctOwner = owner.getOwner();
	bookkeeper = action;
	rawfilename = acctOwner + "rawinfo.txt";
	transfilename = acctOwner + "transacinfo.txt";
	acctfilename = acctOwner + "acctinfo.txt";
}

Filer::Filer(MoneyAcct owner)
{
	acctOwner = owner.getOwner();
	vector<Transaction> bookkeeper;
	rawfilename = acctOwner + "rawinfo.txt";
	transfilename = acctOwner + "transacinfo.txt";
	acctfilename = acctOwner + "acctinfo.txt";
}

// This function reads in the rawinfo.txt file for a given account. This is the main 
// file input for FinanceTracker v1.
void Filer::readRawTransac()
{
	ifstream reader(rawfilename);
	string dummy;
	int linecheck = 0;

	getline(reader, dummy);
	while (getline(reader, dummy)) linecheck++;
	reader.clear();
	reader.seekg(0, reader.beg);
	
	bookkeeper.resize(linecheck, Transaction());

	getline(reader, dummy);

	for (int i = 0; i < linecheck; i++) {
		string symb;
		string date1;
		string date2;
		int shrs;
		double price1;
		double price2;
		bool check;

		reader >> symb;

		if (symb == "Depo" || symb == "With") {
			reader >> date1 >> price1;
			if (symb == "Depo") bookkeeper[i].bankDepo(date1, price1);
			else bookkeeper[i].bankWith(date1, price1*-1.00);
		}

		else {
			reader >> shrs >> date1 >> price1 >> date2 >> price2 >> check;
			if (check) bookkeeper[i].setShared();
			bookkeeper[i].stockTrade(symb, shrs, date1, price1, date2, price2);
			
		}
	}

}

// This function makes the rawinfo.txt file for a given account. This is the
// main file output for FinanceTracker v1.
void Filer::makeRawTransac()
{
	ofstream worker;
	worker.open(rawfilename, ios::trunc);
	worker << acctOwner << " Raw Transaction Data *WARNING: DO NOT MODIFY TEXT FILE* \n";
	for (int i = 0; i < bookkeeper.size(); i++) {
		
		if (bookkeeper[i].stockSale) {
			worker << bookkeeper[i].activity << " " << bookkeeper[i].shares << " " << bookkeeper[i].buyDate << " ";
			worker << setprecision(6) << bookkeeper[i].buyPrice << " " << bookkeeper[i].sellDate << " " << bookkeeper[i].sellPrice<< " " << bookkeeper[i].shared << endl;
		}

		else {
			worker << bookkeeper[i].activity << " " << setprecision(6) << bookkeeper[i].sellDate << " " << bookkeeper[i].acctChange << endl;
		}
	}
	worker.close();
}

// This function makes a formatted list of all transactions and their
// associated details with a given account.
void Filer::makeFormTransac()
{
	ofstream worker;
	worker.open(transfilename, ios::trunc);
	worker << "                           "<< acctOwner << "'s Transactions \n \n";
	worker << "                     Buy Info             Sell Info      Percent   Change to \n";
	worker << "Symb    Shrs      Date       Price     Date       Price   Change    Account \n";
	worker << "-------------------------------------------------------------------------------- \n";
	for (int i = 0; i < bookkeeper.size(); i++) {

		if (bookkeeper[i].stockSale) {
			worker << setw(5) << left << bookkeeper[i].activity << setw(7) << right << bookkeeper[i].shares << "   " << bookkeeper[i].buyDate << "  ";
			worker << setprecision(2) << fixed << setw(7) << bookkeeper[i].buyPrice << "  " << bookkeeper[i].sellDate << "  " << setw(7) << bookkeeper[i].sellPrice;
			worker << setw(8) << setprecision(2) << fixed << bookkeeper[i].prcntChange << setw(12) << bookkeeper[i].acctChange << endl ;
		}

		else {
			worker << bookkeeper[i].activity << "                                " << bookkeeper[i].sellDate; 
			worker << "  " << setw(27) << setprecision(2) << fixed << bookkeeper[i].acctChange << endl ;
		}
	}
	worker.close();
}

// This function makes a formatted list of transactions and their effects on
// the account balance. This also outputs an account's tax due on capital gains.
void Filer::makeFormAcct(MoneyAcct owner)
{
	ofstream worker;
	worker.open(acctfilename, ios::trunc);
	worker << "           " << acctOwner << "'s Account \n \n";
	worker << "Symbol         Change        Balance   \n";
	worker << "--------------------------------------- \n";
	for (int i = 0; i < bookkeeper.size(); i++) {

		if (bookkeeper[i].stockSale) {
			owner.transaction(bookkeeper[i].acctChange);
			worker << setw(6) << left << bookkeeper[i].activity << "   " ;
			worker << setprecision(2) << fixed << setw(12) << right << bookkeeper[i].acctChange ;
			worker << "   " << setprecision(2) << fixed << setw(12) << owner.getCurBal() << endl;
		}

		else {
			owner.bankMoney(bookkeeper[i].acctChange);
			worker << "*" << bookkeeper[i].activity << "* " << right;
			worker << "  " << setw(12) << setprecision(2) << fixed << bookkeeper[i].acctChange ;
			worker << "   " << setprecision(2) << fixed << setw(12) << owner.getCurBal() << endl;
		}
	}

	worker << endl << endl;
	worker << "Total amount in this account: ";
	worker << setprecision(2) << fixed << owner.getCurBal() << endl << endl;
	worker << "Total tax due: ";
	worker << setprecision(2) << fixed << taxMan(owner.getTaxBal()) << endl << endl;
	worker.close();
}

void Filer::addToBookkeeper(Transaction addition)
{
	bookkeeper.push_back(addition);
}

void Filer::printBookkeeper()
{
	for (int i = 0; i < bookkeeper.size(); i++) bookkeeper[i].printContent();
}

Filer::~Filer()
{
}
