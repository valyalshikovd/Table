#pragma once
#include <vector>
#include <string>
#include <iostream>


class TableData {
public:	
	static int id;

	TableData(int colCount) { data_.resize(colCount); id_ = id++;}
	TableData(std::vector<std::string> data) {data_ = data; id_ = id++;}

	std::string toLine(std::vector<int>& colLengths);
	int getLenght(int i);
	std::string get(int i);
	void set(int i, std::string newValue) { data_[i] = newValue;};
	int getId();
	int size() {return data_.size();};
	
	friend bool operator==(const TableData& first, const TableData& second);
protected:
	int id_; // ”никальны номер записи
	friend std::istream& operator>>(std::istream& in, TableData& tableData);
	friend std::ostream& operator<<(std::ostream& out, TableData& tableData);
	std::vector<std::string> data_;
};
