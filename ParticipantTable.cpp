#include <algorithm>
#include <fstream>
#include "ParticipantTable.h"

void ParticipantTable::add(std::vector<std::string> data)
{
	Participant* toAdd = new Participant(data);
	this->Table::add(*toAdd);
}

bool ParticipantTable::loadFile(std::string filepath)
{
	std::ifstream fin(filepath);
	if (!fin.is_open()) return false;
	
	while (!fin.eof()) {
		Participant part;
		fin >> part;
		this->Table::add(part);
	}

	fin.close();
	return true;

}

void ParticipantTable::printTable()
{
	std::cout << "Таблица участников:\n";
	this->Table::printTable();
}


void ParticipantTable::sortByColum(int col)
{
	if (col < 0 || col > headers_.size()) return;

	if (col == 1 || col == 4) sortLikeInt(col);
	else sortLikeString(col);
}

void ParticipantTable::sortByFio()
{
	sortLikeString(0);
}

void ParticipantTable::sortByBirthyear()
{
	sortLikeInt(1);
}

void ParticipantTable::sortByCountry()
{
	sortLikeString(2);
}

void ParticipantTable::sortByInstrument()
{
	sortLikeString(3);
}

void ParticipantTable::sortByPlaceNumber()
{
	sortLikeInt(4);
}

void ParticipantTable::sortLikeString(int col)
{
	auto comp = [&col](TableData& a, TableData& b)
	{
		return a.get(col) < b.get(col);
	};
	std::sort(rows_.begin(), rows_.end(), comp);
}

void ParticipantTable::sortLikeInt(int col)
{
	auto comp = [&col](TableData& a, TableData& b)
	{
		return std::stoi(a.get(col)) > std::stoi(b.get(col));
	};
	std::sort(rows_.begin(), rows_.end(), comp);
}


