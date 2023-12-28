#pragma once
#pragma once
#include <vector>
#include <string>
#include "Table.h"
#include "Account.h"

using namespace std;

class AccountTable : public Table {
public:
	AccountTable() : Table(vector<string>{"Логин", "Пароль", "Тип аккаунта"}) {};
	bool loadFile(string filepath) override;
	void printTable() override;
	void add(std::vector<std::string> data) override;
	// unique
	Account* getByLogin(string login);
};