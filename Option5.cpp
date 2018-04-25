#include "stdafx.h"

void option5() {
	vector<string> names;
	int counter;
	string holder;

	cout << "\n \n      How many names will be entered? ";
	cin >> counter;

	cout << "\n \n      Enter names:  ";
	for (int i = 0; i < counter; i++) {
		cin >> holder;
		names.push_back(holder);
	}

	defaultWriter(names);
}