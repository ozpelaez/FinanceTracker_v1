// Option 3 adds a transaction to an existing account. It asks for the account
// name, transaction info, and adds the transaction to the existing files.

#include "stdafx.h"

using namespace std;

void option3() {
	
	string name, yes_no;
	int choice;
	bool loop;

	// Stock trade 
	string symbol, buy_date, sell_date;
	int shares;
	double buy_price, sell_price;

	string bank_date;
	double money;

	cout << "\n \n      Name of account owner: ";
	cin >> name;
	
	MoneyAcct acct(name);
	Transaction deal;

	do {

		loop = false;

		cout << "\n      Transaction ";
		cout << "\n \n      1) Stock trade";
		cout << "\n      2) Bank move";
		cout << "\n \n      Select type of transaction: ";
		cin >> choice;

		while (cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "\n      Incorrect input! Please try again.";
			cout << "\n      Select type of transaction: ";
			cin >> choice;
		}

		switch (choice) {
		case 1:
			cout << "\n      Type in the stock symbol: ";
			cin >> symbol;
			cout << "\n      Type in the number of shares: ";
			cin >> shares;
			cout << "\n      Type in the buy date (MM/DD/YYYY): ";
			cin >> buy_date;
			cout << "\n      Type in the buy price: ";
			cin >> buy_price;
			cout << "\n      Type in the sell date (MM/DD/YYYY): ";
			cin >> sell_date;
			cout << "\n      Type in the sell price: ";
			cin >> sell_price;
			cout << "\n      Is this trade shared? ";
			cin >> yes_no;
			if (yes_no == "yes" || yes_no == "y") deal.setShared();
			deal.stockTrade(symbol, shares, buy_date, buy_price, sell_date, sell_price);
			break;

		case 2:
			cout << "\n      Bank Transaction ";
			cout << "\n \n      1) Deposit";
			cout << "\n      2) Withdrawal";
			cout << "\n \n      Select type of transaction: ";
			cin >> choice;

			while (cin.fail()) {
				cin.clear();
				cin.ignore(256, '\n');
				cout << "\n      Incorrect input! Please try again.";
				cout << "\n      Select type of transaction: ";
				cin >> choice;
			}

			switch (choice) {
			case 1:
				cout << "\n      Type in the date of transaction (MM/DD/YYYY): ";
				cin >> bank_date;
				cout << "\n      Type in amount depositing: ";
				cin >> money;
				deal.bankDepo(bank_date, money);
				break;

			case 2:
				cout << "\n      Type in the date of transaction (MM/DD/YYYY): ";
				cin >> bank_date;
				cout << "\n      Type in amount withdrawing: ";
				cin >> money;
				deal.bankWith(bank_date, money);
				break;

			default:
				loop = true;
				cout << "\n     You entered this wrong. Try again. \n";
			}
			break;

		default:
			loop = true;
			cout << "\n     You entered this wrong. Try again. \n";

		}
						
	} while (loop);


	Filer go(acct);
	go.readRawTransac();
	go.addToBookkeeper(deal);
	go.makeRawTransac();
	go.makeFormTransac();
	go.makeFormAcct(acct);

	cout << "\n \n      The following transactions are in " << acct.getOwner() << "'s account: \n \n";
	go.printBookkeeper();

}