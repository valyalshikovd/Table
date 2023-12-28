#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "TableData.h"


class Participant : public TableData {
public:
	Participant() : TableData(5) {};
	Participant(std::vector<std::string> data) : TableData(data) {};

	std::string getFio() { return data_[0]; };
	int getBirthyear() { return stoi(data_[1]); };
	std::string getCountry() { return data_[2]; };
	std::string getInstrument() { return data_[2]; };
	int getPlaceNumber() { return stoi(data_[3]); };


};


