#include "stdafx.h"

void defaultWriter(vector<string> names) {

	ofstream writer;

	writer.open("DefaultInfo.txt", ios::trunc);

	writer << "Account Holder Names *WARNING: DO NOT MODIFY TEXT FILE* ";
	for (int i = 0; i < names.size(); i++) writer <<endl << names[i] ;

	writer.close();

}