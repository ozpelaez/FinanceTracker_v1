// taxMan receives the amount of Earned Income made and estimates the amount of tax
// needed to pay for all gains. taxMan is currently written for 2018 tax brackets
// for a single filer. Changes in tax rates and cutoffs need only adjust the
// double arrays (taxrate & cutoff). Changes in the amount of brackets 
// (currently 7 brackets) will require changes to the code.
#include "stdafx.h"


double taxMan(double x)
{
	double const taxrate[7] = { 0.1, 0.12, 0.22, 0.24, 0.32, 0.35, 0.37 };
	double const cutoff[6] = { 9525, 38700, 82500, 157500, 200000, 500000};
	double taxpayment;
	double lowerBracket=cutoff[0]*taxrate[0];					// Used to keep tab on taxes from lower brackets

	
	if (x <= cutoff[0]) {
		taxpayment = x * taxrate[0];
	}
	
	for (int i = 1; i < 6; i++) {								// Set exit condition to i less than size of cutoff array
		
		if (x > cutoff[i-1] && x <= cutoff[i]) {
			taxpayment = (x - cutoff[i-1]) * taxrate[i] + lowerBracket;
		
			lowerBracket += (cutoff[i] - cutoff[i-1])*taxrate[i];
		}

		else lowerBracket += (cutoff[i] - cutoff[i-1])*taxrate[i];
	}

	if (x > cutoff[5]) {
		taxpayment = (x - cutoff[5]) * taxrate[6] + lowerBracket;
	}

	return taxpayment;
}