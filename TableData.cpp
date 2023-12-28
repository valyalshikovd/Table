#include "Table.h"
#include "TableData.h"

int TableData::getLenght(int i)
{
    return data_[i].length();
}

std::string TableData::get(int i)
{
    return data_[i];
}

int TableData::getId()
{
    return id_;
}

std::string TableData::toLine(std::vector<int>& colLengths)
{
    std::string line = ":";
    for (size_t i = 0; i < colLengths.size(); i++){
        line += fillToLenAddingChar(data_[i], colLengths[i], ' ');
        line += ":";
    }
    return line;
}

bool operator== (const TableData& first, const TableData& second)
{
    return first.id_ == second.id_;
}

std::istream& operator>>(std::istream& in, TableData& tableData)
{
    for (size_t i = 0; i < tableData.data_.size(); i++)
        in >> tableData.data_[i];
    return in;
}

std::ostream& operator<<(std::ostream& out, TableData& tableData)
{
    for (size_t i = 0; i < tableData.data_.size(); i++)
        out << tableData.data_[i] << ' ';
    return out;
}


int TableData::id = 0;  