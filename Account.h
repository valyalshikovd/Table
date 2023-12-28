#pragma once
#include "TableData.h"

class Account : public TableData {
public:
	Account() : TableData(3) {};
	Account(std::vector<std::string> data) : TableData(data) {};

	bool isAdmin();
	std::string getLogin() { return data_[0]; };
	std::string getPassword() { return data_[1]; };
	std::string getType() { return data_[2]; };

};