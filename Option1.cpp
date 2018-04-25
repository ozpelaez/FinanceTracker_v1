// Option 1 is the option mostly used by me. It takes in my transaction info and adds it
// to one of 2 accounts I own. The Joint account tracks the total  change of all accounts. 
// Option 1 has me select which account to add to, asks for transaction info, and adds it to
// my account. It reads in the rawinfo.txt file, adds the entered transaction info, and makes
// a new rawinfo.txt file with the added transaction, along with formatted transaction &
// account files.
//
// Only stock trades can be entered through Joint. Bank moves must be entered through either 
// name1 or name2 accounts, not joint. Stock trades entered through Joint are considered
// SHARED for name1 and name2 and are populated in all three accounts.
//
// name1 and name2 can be set in the main function.

#include "stdafx.h"

using namespace std;

void option1(string name1, string name2) {

	MoneyAcct ozzie(name1), notOzzie(name2), joint("Joint"), acct;
	Transaction forOzzie, forJoint, deal;
	bool loop;
	int choice;

	// These variables are for stock trades
	string symbol, buy_date, sell_date;
	int shares;
	double buy_price, sell_price;

	//These are for bank deposits
	string bank_date;
	double money;

	
	do {
		loop = false;
		cout << "\n \n      Welcome "<< name1 <<"! \n      For which account will you be entering?";
		cout << "\n      1) "<< name1;
		cout << "\n      2) "<< name2;
		cout << "\n      3) Joint";
		cout << "\n \n      Select which account: ";
		cin >> choice;

		while (cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "\n      Incorrect input! Please try again.";
			cout << "\n      Make your selection: ";
			cin >> choice;

		}

		switch (choice) {
		case 1:
			acct.setOwner(name1);
			break;
		case 2:
			acct.setOwner(name2);
			break;
		case 3:
			acct.setOwner("Joint");
			break;
		default:
			loop = true;
			cout << "\n     You entered this wrong. Try again.";
		}
						
	} while (loop);

	do {
		loop = false;

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

		// All bank moves need to go through either name1 or name2
		if (choice == 2 && acct.getOwner() == "Joint") {
			cout << " \n \n      " << acct.getOwner() <<" can't make a bank move! ";
			loop = true;
		}
		else {
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
				if (acct.getOwner() == "Joint") {
					forOzzie.setShared();
					forOzzie.stockTrade(symbol, shares, buy_date, buy_price, sell_date, sell_price);
				}
				deal.stockTrade(symbol, shares, buy_date, buy_price, sell_date, sell_price);
				forJoint.stockTrade(symbol, shares, buy_date, buy_price, sell_date, sell_price);
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
					forJoint.bankDepo(bank_date, money);
					break;
				case 2:
					cout << "\n      Type in the date of transaction (MM/DD/YYYY): ";
					cin >> bank_date;
					cout << "\n      Type in amount withdrawing: ";
					cin >> money;
					deal.bankWith(bank_date, money);
					forJoint.bankWith(bank_date, money);
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
		}

	} while (loop);
	
	Filer goJoe(acct);

	goJoe.readRawTransac();
	goJoe.addToBookkeeper(deal);
	goJoe.makeRawTransac();
	goJoe.makeFormTransac();
	goJoe.makeFormAcct(acct);

	if (acct.getOwner() == "Joint") {
		Filer goOzzie(ozzie), goNotOzzie(notOzzie);

		goOzzie.readRawTransac();
		goOzzie.addToBookkeeper(forOzzie);
		goOzzie.makeRawTransac();
		goOzzie.makeFormTransac();
		goOzzie.makeFormAcct(ozzie);

		goNotOzzie.readRawTransac();
		goNotOzzie.addToBookkeeper(forOzzie);
		goNotOzzie.makeRawTransac();
		goNotOzzie.makeFormTransac();
		goNotOzzie.makeFormAcct(notOzzie);
	
	}

	else {
		Filer goJoint(joint);

		goJoint.readRawTransac();
		goJoint.addToBookkeeper(forJoint);
		goJoint.makeRawTransac();
		goJoint.makeFormTransac();
		goJoint.makeFormAcct(joint);

	}

	cout << "\n \n      The following transactions are in " << acct.getOwner() << "'s account: \n \n";
	goJoe.printBookkeeper();
}

void option1(string name1) {

	MoneyAcct acct(name1);
	Transaction deal;
	bool loop;
	int choice;

	// These variables are for stock trades
	string symbol, buy_date, sell_date;
	int shares;
	double buy_price, sell_price;

	//These are for bank deposits
	string bank_date;
	double money;

		
	cout << "\n \n      Welcome " << name1 << "! ";

	do {
		loop = false;

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

	Filer goJoe(acct);

	goJoe.readRawTransac();
	goJoe.addToBookkeeper(deal);
	goJoe.makeRawTransac();
	goJoe.makeFormTransac();
	goJoe.makeFormAcct(acct);
		
	cout << "\n \n      The following transactions are in " << acct.getOwner() << "'s account: \n \n";
	goJoe.printBookkeeper();
}