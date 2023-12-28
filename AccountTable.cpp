#include <algorithm>
#include <fstream>
#include <iostream>
#include "AccountTable.h"

bool AccountTable::loadFile(string filepath)
{
	std::ifstream fin(filepath);
	if (!fin.is_open()) return false;

	while (!fin.eof()) {
		Account account;
		fin >> account;
		this->Table::add(account);
	}

	return true;
}

void AccountTable::printTable()
{
	cout << "Таблица учетных записей:\n";
	this->Table::printTable();
}

void AccountTable::add(std::vector<std::string> data)
{
	Account* toAdd = new Account(data);
	this->Table::add(*toAdd);
}

Account* AccountTable::getByLogin(string login)
{
	for (TableData& account : rows_) {
		if(account.get(0) == login) return &static_cast<Account&>(account);
	}
	return nullptr;
}
