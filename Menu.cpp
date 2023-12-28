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
	std::cout << "\n\n\n\n### Авторизация ###\n\n";
	// DIALOG
	std::cout << "Для работы требуется войти в учетную запись.\n";

	string login, password;
	Account* user;
	while (true) {
		std::cout << "Введите логин: "; std::cin >> login;
		std::cout << "Введите пароль: "; std::cin >> password;
	
		user = accountTable_->getByLogin(login);

		// Login Check
		if (!user) {
			cout << "Нет пользователя с таким логином!\nПопробуйте снова.\n";
			continue;
		}
		// Password Check
		if (user->getPassword() != password) {
			cout << "Не верный пароль!\nПопробуйте снова.\n";
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
		std::cout << "\n\n\n\n### Меню администратора ###\n\n";
		// DIALOG

		std::cout << "Введите код операции:\n";
		std::cout << "#-- Работа с таблицей учетных записей --#\n";
		std::cout << "1. Посмотреть таблицу учетных записей.\n";
		std::cout << "2. Добавить учетную запись.\n";
		std::cout << "3. Отредактировать учетную запись; \n";
		std::cout << "4. Удалить учетную запись.\n";

		std::cout << "\n#-- Работа у таблицей участников --#\n";
		std::cout << "5. Посмотреть таблицу учасников.\n";
		std::cout << "6. Добавить запись.\n";
		std::cout << "7. Удалить запись.\n";
		std::cout << "8. Редактировать запись.\n";

		std::cout << "\n#-- Функционал пользователя --#\n";
		std::cout << "9. Отобразить меню пользователя.\n";

		std::cout << "\n#-- Функционал хранения --#\n";
		std::cout << "10. Сохранить таблицы.\n";
		std::cout << "11. Загрузить таблицы.\n";
		
		std::cout << "\n0. Выход\n";

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
		std::cout << "\n\n\n\n### Меню пользователя ###\n\n";
		// DIALOG

		std::cout << "Введите код операции:\n";
		std::cout << "1. Посмотреть таблицу учасников.\n";
		std::cout << "2. Задание варианта #16.\n";
		std::cout << "3. Поиск данных.\n";
		std::cout << "4. Сортировка по полям.\n";
		std::cout << "0. Выход\n";

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
	if (resultTable->getRowCount() == 0) std::cout << "Победителей до 12 лет не найдено\n";
	else {
		std::cout << "Победители до 12 лет:\n";
		resultTable->printTable();
	}
}

void Menu::searchMenuDialog(Table& table)
{
	// HEADER
	std::cout << "\n\n\n\n### Меню поиска в таблице ###\n\n";
	// DIALOG

	int col = askChooseColumn(table);
	// Возврат в меню
	if (col == 0) return;

	std::string keyWord;
	cout << "Введите ключевое слово для поиска: ";
	cin >> keyWord;

	
	ParticipantTable* resultTable = getFiltredTable(table, col - 1, keyWord);

	if (resultTable->getRowCount() != 0) resultTable->printTable();
	else std::cout << "Не найденно данных по запросу\n";

}

void Menu::sortMenuDialog(Table& table)
{
	// HEADER
	std::cout << "\n\n\n\n### Меню сортировки по столбцам ###\n\n";
	// DIALOG

	int col = askChooseColumn(table);
	// Возврат в меню
	if (col == 0) return;

	participantTable_->sortByColum(col - 1);
	lookParticipantTable();
}

void Menu::variantTaskDialog()
{
	// HEADER
	std::cout << "\n\n\n\n### Меню задания варианта №16 ###\n\n";
	// DIALOG
	// 1
	std::cout << "\n\n\nЗадание 1:\n\n";
	task1();
	// 2
	std::cout << "\n\n\nЗадание 2:\n\n";
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
	std::cout << "\n\n\n\n### Меню редактирования записей ###\n\n";
	// DIALOG

	int row = askChooseRow(table);
	if (row == 0) return;
	TableData* data = table.get(row - 1);

	while (true) {
		std::cout << "\n\n Текущая запись:\n";
		for (size_t i = 0; i < data->size(); i++) {
			std::cout << i + 1 << ". " << table.getHeader(i) << ":\t" << data->get(i) << '\n';
		}

		int col = askChooseColumn(table);
		if (col == 0) return;

		std::string newValue;
		std::cout << "\nВведите новое значение: ";
		std::cin >> newValue;

		if (table.isColumnInt(col - 1) && is_number(newValue)) {
			cout << "Некорректное значение\n";
			cout << "Этот столбел должен содержать целове число!\n";
			continue;
		}

		cout << "Заменяем значение\n";
		data->set(col - 1, newValue);
	}
	
}

void Menu::deleteMenuDialog(Table& table)
{
	// HEADER
	std::cout << "\n\n\n\n### Меню удаления записей ###\n\n";
	// DIALOG

	std::cout << "\nВыберите запись, которую нужно удалить\n";
	int row = askChooseRow(table);
	if (row == 0) return;

	TableData* data = table.get(row - 1);

	std::cout << "\n\n Текущая запись:\n";
	for (size_t i = 0; i < data->size(); i++) {
		std::cout << i + 1 << ". " << table.getHeader(i) << ":\t" << data->get(i) << '\n';
	}

	std::string answer;
	std::cout << "Введите уверены (да/нет): ";
	cin >> answer;
	while (answer != "да" && answer != "нет") {
		std::cout << "Некорректный ответ! Попробуйте снова\n";
		std::cout << "Введите уверены (да/нет): ";
		cin >> answer;
	}
	if (answer == "нет") return;
	int id = data->getId();
	table.deleteById(id);
}

void Menu::addMenuDialog(Table& table)
{
	// HEADER
	std::cout << "\n\n\n\n### Меню добавления записей ###\n\n";
	// DIALOG
	std::vector<std::string> data(table.getColumnCount());
	for (int i = 0; i < table.getColumnCount(); i++) {
		std::cout << i + 1 << ". Текущее поле -" << table.getHeader(i) << ":\n";
		std::string newValue = askColumnValue(table, i);
		
		data[i] = newValue;
	}
	std::cout << "Все данные введены.\n";
	table.add(data);
	std::cout << "Запись добавлена\n";

}

int Menu::askChooseColumn(Table& table)
{
	// Возвращает номер от 1
	int col;
	cout << "Введите порядковый номер стобца (от 1, не считая столбца нумерации). (0 - назад в меню): ";
	cin >> col;
	while (col < 0 || col > table.getColumnCount()) {
		cout << "Некорректный ввод:\n";
		cout << "Введите порядковый номер стобца (от 1, не считая столбца нумерации). (0 - назад в меню): ";
		cin >> col;
	}
	return col;
}

int Menu::askChooseRow(Table& table)
{
	// Возвращает номер от 1
	int row;
	cout << "Введите порядковый номер строки (совпадает с табличным). (0 - назад в меню): ";
	cin >> row;
	while (row < 0 || row > table.getRowCount()) {
		cout << "Некорректный ввод:\n";
		cout << "Введите порядковый номер строки (совпадает с табличным). (0 - назад в меню): ";
		cin >> row;
	}
	return row;
}

std::string Menu::askColumnValue(Table& table, int i)
{
	std::cout << "Введите значение: ";
	std::string answer;
	cin >> answer;
	while (table.isColumnInt(i) && !is_number(answer)) {
		std::cout << "\nЗначение должно быть целочисленное! Попробуйте снова.\n";
		std::cout << "Введите значение: ";
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
	cout << "Загрузка таблицы участников.\n";
	if (loadTable(*candidatParticipantTable)) {
		delete participantTable_;
		participantTable_ = candidatParticipantTable;
	}

	AccountTable* candidatAccountTable = new AccountTable();
	cout << "Загрузка таблицы учетных записей.\n";
	if (loadTable(*candidatAccountTable)) {
		delete accountTable_;
		accountTable_ = candidatAccountTable;
	}



}

bool Menu::loadTable(Table& table)
{
	std::string filepath;
	while (true) {
		std::cout << "Введите путь к файлу данных таблицы (\"-\" чтобы оставить текущую):\n-> ";
		std::cin >> filepath;
		if (filepath == "-") {
			return false;
		}
		if (table.loadFile(filepath)) {
			std::cout << "Таблица загружена!\n";
			return true;
		}
		std::cout << "Не удалось открыть файл!\nПопробуйте еще раз.";
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
		std::cout << "Введите путь к файлу данных таблицы (\"-\" выход):\n-> ";
		std::cin >> filepath;
		if (filepath == "-") {
			return;
		}
		if (table.saveToFile(filepath)) {
			std::cout << "Таблица сохранена!\n";
			return;
		}
		std::cout << "Не удалось открыть файл!\nПопробуйте еще раз.";
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