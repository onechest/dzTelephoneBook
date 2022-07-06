#pragma once
#include"menu.h"

ifstream fileIn;
ofstream fileOut;

class Abonent
{
	char* FIO = nullptr;
	char* phone = nullptr;
	char* info = nullptr;
public:

	void setFIO(const char* n);
	void setPhone(const char* n);
	void setInfo(const char* n);
	inline char* getFIO();
	inline char* getPhone();
	inline char* getInfo();
	string toString();
};

void Abonent::setFIO(const char* n)
{
	int len = strlen(n) + 1;
	FIO = new char[len];
	strcpy_s(FIO, len, n);
}
void Abonent::setPhone(const char* n)
{
	int len = strlen(n) + 1;
	phone = new char[len];
	strcpy_s(phone, len, n);
}
void Abonent::setInfo(const char* n)
{
	int len = strlen(n) + 1;
	info = new char[len];
	strcpy_s(info, len, n);
}

inline char* Abonent::getFIO()
{
	return FIO;
}
inline char* Abonent::getPhone()
{
	return phone;
}
inline char* Abonent::getInfo()
{
	return info;
}

string Abonent::toString()
{
	return  (string)FIO + " " + (string)phone + " " + (string)info;
}

class PhoneBook
{
	Abonent* abonents;
	int size;

public:
	PhoneBook()
	{
		size = 0;
	}
	~PhoneBook()
	{
		delete[] abonents;
	}

	void AddAbonent();
	void DeleteAbonent();
	void SearchAbonent();
	void print();
	void SaveInFile();
	int LoadFromFile();

	void menu()
	{
		system("cls");
		cout << " Меню" << endl;
		int choice = Menu::select_vertical({ "Додати", "Видалити", "Знайти", "Друк", "Зберегти у файлі", "Загрузити з файлу", "Вихід" }, HorizontalAlignment::Left, 1);;

		switch (choice)
		{
		case 0:
		{
			AddAbonent();
			break;
		}
		case 1:
		{
			DeleteAbonent();
			break;
		}
		case 2:
		{
			SearchAbonent();
			break;
		}
		case 3:
		{
			print();
			break;
		}
		case 4:
		{
			SaveInFile();
			break;
		}
		case 5:
		{
			LoadFromFile();
			break;
		}
		case 6:
		{
			break;
		}
		}
	}
};

void PhoneBook::AddAbonent()
{
	system("cls");
	Abonent* newArray = new Abonent[size + 1];
	for (int i = 0; i < size; i++)
	{
		newArray[i] = abonents[i];
	}
	cout << "ФИО: ";
	char n[100];
	cin.getline(n, 100);
	newArray[size].setFIO(n);
	cout << "Телефон: ";
	cin.getline(n, 100);
	newArray[size].setPhone(n);
	cout << "Инфо: ";
	cin.getline(n, 100);
	newArray[size].setInfo(n);
	size++;
	delete[] abonents;
	abonents = newArray;
	menu();
}

void PhoneBook::DeleteAbonent()
{
	system("cls");
	vector<string> delList;

	if (size == 0)
	{
		cout << "У вас пустая телефонная книга!" << endl;
		system("pause");
		menu();
	}

	for (size_t i = 0; i < size; i++)
	{
		delList.push_back(to_string(i + 1) + abonents[i].toString());
	}
	cout << " Выбрите, кого хотите удалить: " << endl;

	int ind = Menu::select_vertical(delList, HorizontalAlignment::Left, 1);
	Abonent* newArr = new Abonent[size];
	for (size_t i = 0; i < ind; i++)
	{
		newArr[i] = abonents[i];
	}
	for (size_t i = ind + 1; i < size; i++)
	{
		newArr[i - 1] = abonents[i];
	}
	size--;
	delete[] abonents;
	abonents = newArr;
	menu();
}

void PhoneBook::SearchAbonent()
{
	int similarity = 0;
	int numName = 0;
	char name[255];
	system("cls");
	cout << "Введите ФИО абонента, которую хотите найти: ";
	cin.ignore();
	cin.getline(name, 255);
	for (int i = 0; i < size; i++)
	{
		bool check = false;
		char* fio = abonents[i].getFIO();
		for (int j = 0; j < strlen(fio); j++)
		{
			if (name[numName] == fio[j])
			{
				if (numName + 1 == strlen(name))
				{
					check = true;
					break;
				}
				numName++;
			}
			else
			{
				numName = 0;
			}
		}
		if (check == true)
		{
			similarity++;
			cout << similarity << ") ФИО: " << abonents[i].getFIO() << endl;
			cout << "Телефон: " << abonents[i].getPhone() << endl;
			cout << "Описание: " << abonents[i].getInfo() << endl;
			cout << "=====================================" << endl;
		}
	}
	if (similarity == 0)
	{
		cout << "По вашему запросу ничего не найдено." << endl;
	}
	system("pause");
	menu();
}

void PhoneBook::print()
{
	system("cls");
	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << ") ФИО: " << abonents[i].getFIO() << endl;
		cout << "Телефон: " << abonents[i].getPhone() << endl;
		cout << "Описание: " << abonents[i].getInfo() << endl;
		cout << "=====================================" << endl;
	}
	system("pause");
	menu();
}

void PhoneBook::SaveInFile()
{
	fileOut.open("Abonents.txt");
	for (int i = 0; i < size; i++)
	{
		fileOut << i + 1 << ") ФИО: " << abonents[i].getFIO() << endl;
		fileOut << "Телефон: " << abonents[i].getPhone() << endl;
		fileOut << "Описание: " << abonents[i].getInfo() << endl;
		fileOut << "=====================================" << endl;
	}
	cout << "Файл успешно сохранен" << endl;
	fileOut.close();
	menu();
}

int PhoneBook::LoadFromFile()
{
	size = 0;
	char str[255]{};
	fileIn.open("Abonents.txt");
	if (fileIn.fail())
	{
		cout << "ERROR" << endl;
		return 404;
	}
	while (!fileIn.eof())
	{
		size++;
		for (int i = 0; i < 4; i++)
		{
			fileIn.getline(str, 255);
		}
	}
	size--;
	fileIn.close();

	fileIn.open("Abonents.txt");
	Abonent* newArray = new Abonent[size];
	for (int i = 0; i < size; i++)
	{
		fileIn >> str;
		fileIn >> str;
		fileIn.getline(str, 255);
		newArray[i].setFIO(str);
		fileIn >> str;
		fileIn.getline(str, 255);
		newArray[i].setPhone(str);
		fileIn >> str;
		fileIn.getline(str, 255);
		newArray[i].setInfo(str);
		fileIn >> str;
	}
	delete[] abonents;
	abonents = newArray;
	menu();
}