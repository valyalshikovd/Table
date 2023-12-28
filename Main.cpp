#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include "Menu.h"

using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	/*
	ParticipantTable participantTable = ParticipantTable();
	participantTable.loadFile("ParticipantData.txt");	
	if (participantTable.saveToFile("ParticipantData2.txt")) cout << "Сохранил\n"; 
	participantTable.printTable();

	AccountTable accountTable = AccountTable();
	accountTable.loadFile("AccountData.txt");
	if (accountTable.saveToFile("AccountData2.txt")) cout << "Сохранил\n";
	accountTable.printTable();

	cout << *accountTable.get(1) << '\n';
	cout << *accountTable.getByLogin("admin") << '\n';
	*/

	Menu menu;
	menu.start();
	return 0;
}
