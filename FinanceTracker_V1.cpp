// FinanceTracker_V1 is a tool to track your finances. It is currently limited in scope to bank transactions (withdrawals
// and deposits) and stock trades. It stores data through the rawinfo.txt file. It generates formatted files that are
// easier to read. rawinfo.txt files may be modified but at your own risk.
//

#include "stdafx.h"
using namespace std;

int main()
{
	int choice;
	bool stay = true;
	string name1, name2;

// name1 and name2 allow you to have your own default functionality
	name1 = "Blaine";
	name2 = "Lance";

	do {

		cout << "\n \n         Welcome to FinanceTracker version 1.0 \n \n";
		cout << "      Select from the following choices: \n \n";
		cout << "          1) Load in default ("<< name1 <<" & "<< name2 <<") "<< endl;
		cout << "          2) Create new account" << endl;
		cout << "          3) Add transaction to existing account" << endl;
		cout << "          4) Read in raw transaction info" << endl;
		cout << "          5) Exit program \n \n" << endl;
		cout << "      Make your selection: ";
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
			option1(name1, name2);
			break;
		case 2:
			option2();
			break;
		case 3:
			option3();
			break;
		case 4:
			option4();
			break;
		case 5:
			stay = false;
			break;
		default:
			cout << "\n      Incorrect input! Please try again.";
		}

	} while (stay);

    return 0;
}

