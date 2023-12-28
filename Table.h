#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "TableData.h"

class Table{
public:
	Table(std::vector<std::string> headers);
	void add(TableData& toAdd);
	virtual void add(std::vector<std::string> data) = 0;
	virtual void printTable();
	int getColumnCount();
	int getRowCount();

	TableData* get(int i);
	TableData* getById(int id);
	int getIndexById(int id);

	void deleteById(int id) {
		int i = getIndexById(id);
		if (i == -1) return;
		rows_.erase(rows_.begin() + i);
	};

	std::string getHeader(int i);

	virtual bool isColumnInt(int i) { return false; };

	virtual bool loadFile(std::string filepath) = 0;
	bool saveToFile(std::string filepath);

	void sortByColumn(int colIndex);
protected:
	void recountColLengths(TableData& toAdd);
	std::vector<std::string> headers_;
	std::vector<TableData> rows_;
	std::vector<int> colLengths_;

	static const int padding = 6;
	static const int numberColLength = 6;
	static const std::string numberColName;
};

static std::string fillToLenAddingChar(std::string str, int len, char c) {
	int delta = len - str.length();
	return std::string(delta / 2 + delta % 2, c) + str + std::string(delta / 2 , c);
}