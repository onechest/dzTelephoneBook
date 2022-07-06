#include "Header.h"

int main()
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	PhoneBook phonebook;
	phonebook.menu();
}