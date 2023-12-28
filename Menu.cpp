#include "Menu.h"
#include <iostream>

Menu::Menu()
{
	participantTable_ = new ParticipantTable();
	accountTable_ = new AccountTable();
	participantTable_->loadFile("ParticipantData.txt");
	accountTable_->loadFile("AccountData.txt");
	currentUser_ = nullptr;
}

void Menu::start()
{
	chooseMenuDialog();
}

void Menu::loginDialog()
{
	// HEADER
	std::cout << "\n\n\n\n### ����������� ###\n\n";
	// DIALOG
	std::cout << "��� ������ ��������� ����� � ������� ������.\n";

	string login, password;
	Account* user;
	while (true) {
		std::cout << "������� �����: "; std::cin >> login;
		std::cout << "������� ������: "; std::cin >> password;
	
		user = accountTable_->getByLogin(login);

		// Login Check
		if (!user) {
			cout << "��� ������������ � ����� �������!\n���������� �����.\n";
			continue;
		}
		// Password Check
		if (user->getPassword() != password) {
			cout << "�� ������ ������!\n���������� �����.\n";
			continue;
		}

		currentUser_ = user;
		break;
	}

}

void Menu::chooseMenuDialog()
{
	if (!currentUser_) loginDialog();

	if (currentUser_->isAdmin()) adminMenuDialog();
	else userMenuDialog();
}

void Menu::adminMenuDialog()
{
	

	int choice;
	while (true) {
		// HEADER
		std::cout << "\n\n\n\n### ���� �������������� ###\n\n";
		// DIALOG

		std::cout << "������� ��� ��������:\n";
		std::cout << "#-- ������ � �������� ������� ������� --#\n";
		std::cout << "1. ���������� ������� ������� �������.\n";
		std::cout << "2. �������� ������� ������.\n";
		std::cout << "3. ��������������� ������� ������; \n";
		std::cout << "4. ������� ������� ������.\n";

		std::cout << "\n#-- ������ � �������� ���������� --#\n";
		std::cout << "5. ���������� ������� ���������.\n";
		std::cout << "6. �������� ������.\n";
		std::cout << "7. ������� ������.\n";
		std::cout << "8. ������������� ������.\n";

		std::cout << "\n#-- ���������� ������������ --#\n";
		std::cout << "9. ���������� ���� ������������.\n";

		std::cout << "\n#-- ���������� �������� --#\n";
		std::cout << "10. ��������� �������.\n";
		std::cout << "11. ��������� �������.\n";
		
		std::cout << "\n0. �����\n";

		cin >> choice;

		switch (choice) {
		case(1):
			lookAccountTable();
			break;

		case(2):
			addMenuDialog(*accountTable_);
			break;

		case(3):
			editMenuDialog(*accountTable_);
			break;

		case(4):
			deleteMenuDialog(*accountTable_);
			break;
		case(5):
			lookParticipantTable();
			break;
		case(6):
			addMenuDialog(*participantTable_);
			break;
		case(7):
			deleteMenuDialog(*participantTable_);
			break;
		case(8):
			editMenuDialog(*participantTable_);
			break;
		case(9):
			userMenuDialog();
			break;
		case(10):
			saveTables();
			break;
		case(11):
			loadTables();
			break;
		case(0):
			return;
		default:
			break;
		}
	}
}

void Menu::userMenuDialog()
{
	int choice;
	while (true) {
		// HEADER
		std::cout << "\n\n\n\n### ���� ������������ ###\n\n";
		// DIALOG

		std::cout << "������� ��� ��������:\n";
		std::cout << "1. ���������� ������� ���������.\n";
		std::cout << "2. ������� �������� #16.\n";
		std::cout << "3. ����� ������.\n";
		std::cout << "4. ���������� �� �����.\n";
		std::cout << "0. �����\n";

		cin >> choice;

		switch (choice){
		case(1):
			lookParticipantTable();
			break;

		case(2):
			variantTaskDialog();
			break;

		case(3):
			searchMenuDialog(*participantTable_);
			break;

		case(4):
			sortMenuDialog(*participantTable_);
			break;
		case(0):
			return;
		default:
			break;
		}
	}
}

void Menu::task2()
{
	const int currentYear = 2023;
	ParticipantTable* resultTable = new ParticipantTable();

	for (size_t rowIndex = 0; rowIndex < participantTable_->getRowCount(); rowIndex++)
	{
		TableData& data = *participantTable_->get(rowIndex);
		int age = currentYear - std::stoi(data.get(1));
		int placeNumber = std::stoi(data.get(4));

		if (age <= 12 && placeNumber == 1) {
			resultTable->Table::add(*participantTable_->get(rowIndex));
		}
	}
	if (resultTable->getRowCount() == 0) std::cout << "����������� �� 12 ��� �� �������\n";
	else {
		std::cout << "���������� �� 12 ���:\n";
		resultTable->printTable();
	}
}

void Menu::searchMenuDialog(Table& table)
{
	// HEADER
	std::cout << "\n\n\n\n### ���� ������ � ������� ###\n\n";
	// DIALOG

	int col = askChooseColumn(table);
	// ������� � ����
	if (col == 0) return;

	std::string keyWord;
	cout << "������� �������� ����� ��� ������: ";
	cin >> keyWord;

	
	ParticipantTable* resultTable = getFiltredTable(table, col - 1, keyWord);

	if (resultTable->getRowCount() != 0) resultTable->printTable();
	else std::cout << "�� �������� ������ �� �������\n";

}

void Menu::sortMenuDialog(Table& table)
{
	// HEADER
	std::cout << "\n\n\n\n### ���� ���������� �� �������� ###\n\n";
	// DIALOG

	int col = askChooseColumn(table);
	// ������� � ����
	if (col == 0) return;

	participantTable_->sortByColum(col - 1);
	lookParticipantTable();
}

void Menu::variantTaskDialog()
{
	// HEADER
	std::cout << "\n\n\n\n### ���� ������� �������� �16 ###\n\n";
	// DIALOG
	// 1
	std::cout << "\n\n\n������� 1:\n\n";
	task1();
	// 2
	std::cout << "\n\n\n������� 2:\n\n";
	task2();

}

void Menu::task1()
{
	ParticipantTable* resultTable = new ParticipantTable();

	for (size_t rowIndex = 0; rowIndex < participantTable_->getRowCount(); rowIndex++)
	{
		TableData& data = *participantTable_->get(rowIndex);
		int placeNumber = std::stoi(data.get(4));

		if ( placeNumber <= 3) {
			resultTable->Table::add(*participantTable_->get(rowIndex));
		}
	}
	resultTable->sortByPlaceNumber();
	resultTable->sortByInstrument();
	resultTable->printTable();
	
}


bool is_number(const std::string& s)
{
	return !s.empty() && (s.find_first_not_of("0123456789") == s.npos);
}

void Menu::editMenuDialog(Table& table)
{
	// HEADER
	std::cout << "\n\n\n\n### ���� �������������� ������� ###\n\n";
	// DIALOG

	int row = askChooseRow(table);
	if (row == 0) return;
	TableData* data = table.get(row - 1);

	while (true) {
		std::cout << "\n\n ������� ������:\n";
		for (size_t i = 0; i < data->size(); i++) {
			std::cout << i + 1 << ". " << table.getHeader(i) << ":\t" << data->get(i) << '\n';
		}

		int col = askChooseColumn(table);
		if (col == 0) return;

		std::string newValue;
		std::cout << "\n������� ����� ��������: ";
		std::cin >> newValue;

		if (table.isColumnInt(col - 1) && is_number(newValue)) {
			cout << "������������ ��������\n";
			cout << "���� ������� ������ ��������� ������ �����!\n";
			continue;
		}

		cout << "�������� ��������\n";
		data->set(col - 1, newValue);
	}
	
}

void Menu::deleteMenuDialog(Table& table)
{
	// HEADER
	std::cout << "\n\n\n\n### ���� �������� ������� ###\n\n";
	// DIALOG

	std::cout << "\n�������� ������, ������� ����� �������\n";
	int row = askChooseRow(table);
	if (row == 0) return;

	TableData* data = table.get(row - 1);

	std::cout << "\n\n ������� ������:\n";
	for (size_t i = 0; i < data->size(); i++) {
		std::cout << i + 1 << ". " << table.getHeader(i) << ":\t" << data->get(i) << '\n';
	}

	std::string answer;
	std::cout << "������� ������� (��/���): ";
	cin >> answer;
	while (answer != "��" && answer != "���") {
		std::cout << "������������ �����! ���������� �����\n";
		std::cout << "������� ������� (��/���): ";
		cin >> answer;
	}
	if (answer == "���") return;
	int id = data->getId();
	table.deleteById(id);
}

void Menu::addMenuDialog(Table& table)
{
	// HEADER
	std::cout << "\n\n\n\n### ���� ���������� ������� ###\n\n";
	// DIALOG
	std::vector<std::string> data(table.getColumnCount());
	for (int i = 0; i < table.getColumnCount(); i++) {
		std::cout << i + 1 << ". ������� ���� -" << table.getHeader(i) << ":\n";
		std::string newValue = askColumnValue(table, i);
		
		data[i] = newValue;
	}
	std::cout << "��� ������ �������.\n";
	table.add(data);
	std::cout << "������ ���������\n";

}

int Menu::askChooseColumn(Table& table)
{
	// ���������� ����� �� 1
	int col;
	cout << "������� ���������� ����� ������ (�� 1, �� ������ ������� ���������). (0 - ����� � ����): ";
	cin >> col;
	while (col < 0 || col > table.getColumnCount()) {
		cout << "������������ ����:\n";
		cout << "������� ���������� ����� ������ (�� 1, �� ������ ������� ���������). (0 - ����� � ����): ";
		cin >> col;
	}
	return col;
}

int Menu::askChooseRow(Table& table)
{
	// ���������� ����� �� 1
	int row;
	cout << "������� ���������� ����� ������ (��������� � ���������). (0 - ����� � ����): ";
	cin >> row;
	while (row < 0 || row > table.getRowCount()) {
		cout << "������������ ����:\n";
		cout << "������� ���������� ����� ������ (��������� � ���������). (0 - ����� � ����): ";
		cin >> row;
	}
	return row;
}

std::string Menu::askColumnValue(Table& table, int i)
{
	std::cout << "������� ��������: ";
	std::string answer;
	cin >> answer;
	while (table.isColumnInt(i) && !is_number(answer)) {
		std::cout << "\n�������� ������ ���� �������������! ���������� �����.\n";
		std::cout << "������� ��������: ";
		cin >> answer;
	}
	return answer;
}

void Menu::lookParticipantTable()
{
	participantTable_->printTable();
}

void Menu::lookAccountTable()
{
	accountTable_->printTable();
}

void Menu::loadTables()
{
	ParticipantTable* candidatParticipantTable = new ParticipantTable();
	cout << "�������� ������� ����������.\n";
	if (loadTable(*candidatParticipantTable)) {
		delete participantTable_;
		participantTable_ = candidatParticipantTable;
	}

	AccountTable* candidatAccountTable = new AccountTable();
	cout << "�������� ������� ������� �������.\n";
	if (loadTable(*candidatAccountTable)) {
		delete accountTable_;
		accountTable_ = candidatAccountTable;
	}



}

bool Menu::loadTable(Table& table)
{
	std::string filepath;
	while (true) {
		std::cout << "������� ���� � ����� ������ ������� (\"-\" ����� �������� �������):\n-> ";
		std::cin >> filepath;
		if (filepath == "-") {
			return false;
		}
		if (table.loadFile(filepath)) {
			std::cout << "������� ���������!\n";
			return true;
		}
		std::cout << "�� ������� ������� ����!\n���������� ��� ���.";
	}
}

void Menu::saveTables()
{
	saveTable(*participantTable_);
	saveTable(*accountTable_);
}

void Menu::saveTable(Table& table)
{
	std::string filepath;
	while (true) {
		std::cout << "������� ���� � ����� ������ ������� (\"-\" �����):\n-> ";
		std::cin >> filepath;
		if (filepath == "-") {
			return;
		}
		if (table.saveToFile(filepath)) {
			std::cout << "������� ���������!\n";
			return;
		}
		std::cout << "�� ������� ������� ����!\n���������� ��� ���.";
	}
}

ParticipantTable* Menu::getFiltredTable(Table& table, int colIndex, std::string keyWord) {
	ParticipantTable* resultTable = new ParticipantTable();
	for (size_t rowIndex = 0; rowIndex < participantTable_->getRowCount(); rowIndex++)
	{
		if (table.get(rowIndex)->get(colIndex) == keyWord)
			resultTable->Table::add(*participantTable_->get(rowIndex));
	}
	return resultTable;
}