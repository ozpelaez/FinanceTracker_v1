// Option 2 allows a new account to be made. It takes a name and how many transactions will
// be added. It then goes through each transaction, asking if it's a stock trade (followed
// by the appropriate information) or if it's a bank move. After it collects all the info
// from each trade, it creates all three output files (rawinfo, transacinfo, acctinfo).

#include "stdafx.h"

using namespace std;

void option2() {

	string name;
	int trans_size;
	int choice;
	string yes_no;

	// Stock trade variables
	string symbol, buy_date, sell_date;
	int shares;
	double buy_price, sell_price;

	// Bank trade variables
	string bank_date;
	double money;

	bool loop;
	

	cout << "\n \n      Name of account owner: ";
	cin >> name;
	MoneyAcct acct(name);
	cout << "\n      How many transactions will you enter? ";
	cin >> trans_size;

	while (cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "\n      Incorrect input! Please try again.";
		cout << "\n      How many transactions will you enter? ";
		cin >> trans_size;
	}
	
	vector<Transaction> deals(trans_size, Transaction());

	for (int i = 0; i < trans_size; i++) {
		
		do {
			loop = false;

			cout << "\n      Transaction " << i + 1;
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
				if (yes_no == "yes" || yes_no == "y") deals[i].setShared();
				deals[i].stockTrade(symbol, shares, buy_date, buy_price, sell_date, sell_price);
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
					deals[i].bankDepo(bank_date, money);
					break;

				case 2:
					cout << "\n      Type in the date of transaction (MM/DD/YYYY): ";
					cin >> bank_date;
					cout << "\n      Type in amount withdrawing: ";
					cin >> money;
					deals[i].bankWith(bank_date, money);
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
	}

	Filer go(acct, deals);
	go.makeRawTransac();
	go.makeFormTransac();
	go.makeFormAcct(acct);

	cout << "\n      The following transactions were entered: \n";

	for (int i = 0; i < trans_size; i++) deals[i].printContent();

}