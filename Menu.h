#pragma once
#include <string>
#include "ParticipantTable.h"
#include "AccountTable.h"
#include "Account.h"

class Menu {
public:
	Menu();
	// start
	void start();
private:
	// Dialogs
	void loginDialog();
	void chooseMenuDialog();
	void adminMenuDialog();
	void userMenuDialog();
	void variantTaskDialog();
	void task1();
	void task2();
	void searchMenuDialog(Table& table);
	void sortMenuDialog(Table& table);
	void editMenuDialog(Table& table);
	void deleteMenuDialog(Table& table);
	void addMenuDialog(Table& table);
	// ASK
	int askChooseColumn(Table& table);
	int askChooseRow(Table& table);
	std::string askColumnValue(Table& table, int i);
	// Func
	void lookParticipantTable();
	void lookAccountTable();
	void loadTables();
	bool loadTable(Table& table);
	void saveTables();
	void saveTable(Table& table);

	ParticipantTable* getFiltredTable(Table& table, int colIndex, std::string keyWord);

private:
	ParticipantTable* participantTable_;
	AccountTable* accountTable_;
	Account* currentUser_;
};
