#include "Table.h"
#include <iostream>
#include <fstream>


Table::Table(std::vector<std::string> headers)
{
	this->headers_ = headers;
	this->colLengths_.resize(headers_.size());
	for (size_t i = 0; i < headers_.size(); i++) {
		colLengths_[i] = headers_[i].length() + padding;
	}
}

void Table::add(TableData& toAdd)
{
	recountColLengths(toAdd);
	rows_.push_back(toAdd);
}


void Table::printTable()
{

	int sumLength = numberColLength + 2;
	for (int& l : colLengths_) sumLength += l + 1; // +1 для разделтелей

	std::string rowSpliter = std::string(sumLength, '-') + '\n';

	// Верхняя граница
	std::cout << rowSpliter;
	// Колонка нумерации
	std::cout << ':' << fillToLenAddingChar(numberColName, numberColLength, ' ');
	for (size_t i = 0; i < headers_.size(); i++) {
		std::cout << ':' << fillToLenAddingChar(headers_[i], colLengths_[i], ' ');
	}
	std::cout << ":\n\n" << rowSpliter;
	
	for (size_t i = 0; i < rows_.size(); i++) {
		std::cout << ':' << fillToLenAddingChar(std::to_string(i + 1), numberColLength, ' ') << rows_[i].toLine(colLengths_) << '\n' << rowSpliter;
	}
	
}

int Table::getColumnCount()
{
	return headers_.size();
}

int Table::getRowCount()
{
	return rows_.size();
}

TableData* Table::get(int i)
{
	if (i < 0 || i >= rows_.size()) return nullptr;
	return &rows_[i];
}

std::string Table::getHeader(int i)
{
	return headers_[i];
}

TableData* Table::getById(int id) {
	for (TableData& data : rows_) {
		if (data.getId() == id) return &data;
	}
	return nullptr;
}

int Table::getIndexById(int id) {
	int i = 0;
	for (TableData& data : rows_) {
		if (data.getId() == id) return i;
		i++;
	}
	return -1;
}

void Table::recountColLengths(TableData& toAdd)
{
	for (size_t i = 0; i < colLengths_.size(); i++) {
		colLengths_[i] = std::max(colLengths_[i] - padding, toAdd.getLenght(i)) + padding;
	}
}

const std::string Table::numberColName = "№";

bool Table::saveToFile(std::string filepath) {
	std::ofstream fout(filepath);
	if (!fout.is_open()) return false;


	for (size_t i = 0; i < rows_.size(); i++) {
		fout << rows_[i];
		if (i + 1 < rows_.size()) fout << '\n';
	}
	fout.close();
	return true;
}
