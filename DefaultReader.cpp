// This reads DefaultInfo.txt. Built to accommodate more than two names and
// possibly other type of info that will be contained in DefaultInfo.txt
// (e.g. commission fees)
#include "stdafx.h"

vector<string> defaultReader(){

	string dummy;
	ifstream reader("DefaultInfo.txt");
	vector<string> names;
	

	getline(reader, dummy);

	while (reader.good()) {
		getline(reader, dummy);
		names.push_back(dummy);
	}

	if (names.size() == 0) {
		cout << "Could not read DefaultInfo.txt. Please use Option 5 to make DefaultInfo.txt. \n";
		names.push_back("Blaine");
		names.push_back("Lance");
	}

	return names;
}