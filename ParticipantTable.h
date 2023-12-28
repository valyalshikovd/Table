#pragma once
#include <vector>
#include <string>
#include "Table.h"
#include "Participant.h"


class ParticipantTable : public Table{
public:
	ParticipantTable() : Table(std::vector<std::string>{"ФИО", "Год рождеия", "Страна", "Инструмент", "Место в конкурсе"}) {
		isInt_.resize(headers_.size(), false);
		isInt_[1] = true;
		isInt_[4] = true;
	};	

	void add(std::vector<std::string> data) override;
	bool loadFile(std::string filepath) override;
	void printTable() override;
	bool isColumnInt(int i) override { return isInt_[i]; };

	// SORT 
	void sortByColum(int col);
	void sortByFio();
	void sortByBirthyear();
	void sortByCountry();
	void sortByInstrument();
	void sortByPlaceNumber();
	// SORT BASE
	void sortLikeString(int col);
	void sortLikeInt(int col);
private:
	std::vector<bool> isInt_;
};