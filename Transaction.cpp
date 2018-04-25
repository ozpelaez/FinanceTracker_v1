// Transaction is a class that holds all the pertinent transaction info such as:
// Type of transaction, how much money, when, and other metrics.

#include "stdafx.h"
#include "Transaction.h"
#include <iostream>
#include <iomanip>

// Activity should always reflect either bank transaction or stock
// symbol. If Not Good is seen, something went wrong with how the
// Transaction was defined.
Transaction::Transaction()
{
	activity = "Not Good";
	shares = 0;
	buyDate = "          ";
	buyPrice = 0.00;
	sellDate = "          ";
	sellPrice = 0.00;
	prcntChange = 0.0;
	acctChange = 0.00;
	stockSale = false;
	shared = false;
	commission = 13.9;
}

bool Transaction::isSale()
{
	return stockSale;
}

// bankWith and bankDepo represent withdrawals and deposits from 
// account. This is important because these transactions do not
// contribute to an account's tax bill.
void Transaction::bankWith(string date, double amount)
{
	activity = "With";
	sellDate = date;
	acctChange = amount* -1.00;
	stockSale = false;
}

void Transaction::bankDepo(string date, double amount)
{
	activity = "Depo";
	sellDate = date;
	acctChange = amount;
	stockSale = false;
}

// stockTrade takes in all pertinent info from a stock transaction.
// stockTrade does contribute to a person's tax bill.
//
// *IMPORTANT*: If a stockTrade is shared with another account, then
// the Transaction MUST be set as SHARED prior to calling stockTrade.
// Otherwise, acctChange will not be correct.
//
// 04/17/18: stockTrade now overloaded to properly account for commission
// fees. First version is for when taking in info from console. Second 
// version is for reading in info through Filer.
void Transaction::stockTrade(string nme, int shrs, string bd, double bp, string sd, double sp)
{
	activity = nme;
	shares = shrs;
	buyDate = bd;
	buyPrice = bp;
	sellDate = sd;
	sellPrice = sp;
	prcntChange = (sp - bp) / bp *100.00;
	stockSale = true;
	if (shared) acctChange = ((sp - bp)*shrs - commission)/2.0;
	else acctChange = (sp - bp)*shrs - commission;
	
}

void Transaction::stockTrade(string nme, int shrs, string bd, double bp, string sd, double sp, double cm)
{
	activity = nme;
	shares = shrs;
	buyDate = bd;
	buyPrice = bp;
	sellDate = sd;
	sellPrice = sp;
	commission = cm;
	prcntChange = (sp - bp) / bp * 100.00;
	stockSale = true;
	if (shared) acctChange = ((sp - bp)*shrs - commission) / 2.0;
	else acctChange = (sp - bp)*shrs - commission;

}

// Sets a Transaction to SHARED
void Transaction::setShared()
{
	shared = true;
}

void Transaction::printContent()
{
	cout << setw(6) << left << activity << setw(7) << right << shares << " " << buyDate << " ";
	cout << setprecision(2)<< fixed << setw(7) << buyPrice << " " << sellDate << " " << setw(7) << sellPrice;
	cout << setw(7) << setprecision(2) << fixed << prcntChange << setw(11) << acctChange;
	
	if (shared) cout << " SHARED"<< endl ;
	else cout << endl ;
}

void Transaction::acctInfo()
{
	cout << setw(6) << left << activity << " $" ;
	cout << setprecision(2) << fixed << setw(11) << right << acctChange ;
}

double Transaction::howMuch() 
{
	return acctChange;
}

Transaction::~Transaction()
{
}
