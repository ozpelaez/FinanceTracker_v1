#pragma once
#include "stdafx.h"

using namespace std;

class Transaction
{
	friend class Filer;

public:
	Transaction();
	~Transaction();
	void bankWith(string date, double amount);
	void bankDepo(string date, double amount);
	void stockTrade(string nme, int shrs, string bd, double bp , string sd, double sp);
	void printContent();
	void acctInfo();
	bool isSale();
	void setShared();
	double howMuch();

private:
	string activity;
	int shares;
	string buyDate;
	double buyPrice;
	string sellDate;
	double sellPrice;
	double prcntChange;
	double acctChange;
	bool stockSale;
	bool shared;
};

