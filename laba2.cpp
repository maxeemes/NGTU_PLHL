// laba2.cpp : Defines the entry point for the console application.
//

#include "studentStruct.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <Windows.h>

using namespace std;

int mainMenu();
void studentsEditSubMenu(Student ***students, const int maxStudentsCount, int *studentsCount);
void userAddStudentsFromFile(Student ***students, const int maxStudentsCount, int *studentsCount, const string defaultPath);
void printAllStudents(Student **students, int studentsCount);
int modeSelectMenu();
void userStudentAdd(Student ***students, const int maxStudentsCount, int *studentsCount);
void userStudentEdit(Student ***students, const int studentsCount);
void userStudentDelete(Student ***students, int *studentsCount);
void userStudentDeleteAll(Student ***students, int *studentsCount);
void userSaveStudentsToFile(Student **students, const int studentsCount, const string defaultPath);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	const int maxStudentsCount = 1000;
	const string defaultFilePeth = "studentsMarks.txt";
	int studentsCount = 0;
	Student **students = 0;
	int selected = 0;
	do {
		selected = mainMenu();
		switch (selected)
		{
		case 1:
			userAddStudentsFromFile(&students, maxStudentsCount, &studentsCount, defaultFilePeth);
			break;
		case 2:
			studentsEditSubMenu(&students, maxStudentsCount, &studentsCount);
			break;
		case 3:
			userSaveStudentsToFile(students, studentsCount, defaultFilePeth);
			break;
		default:
			break;
		}
	} while (selected != 4);

	getchar();
	return 0;
}

int mainMenu() {
	AddConsoleTextColor("______МЕНЮ______", 224);
	AddConsoleTextColor("1. Добавить студентов из файла", 14);
	AddConsoleTextColor("2. Просмотр/редактирование информации о студентах", 14);
	AddConsoleTextColor("3. Сохранить студентов в файл", 14);
	AddConsoleTextColor("4. ВЫХОД");
	AddConsoleTextColor("Введите номер действия...", 7);
	int selected = 0;
	cin >> selected;
	return selected;
}

int modeSelectMenu() {
	AddConsoleTextColor("______Просмотр/редактирование информации о студентах______", 224);
	AddConsoleTextColor("1. Добавить студента", 14);
	AddConsoleTextColor("2. Изменить информацию о студенте", 14);
	AddConsoleTextColor("3. Удалить студента", 14);
	AddConsoleTextColor("4. Удалить всех студентов");
	AddConsoleTextColor("5. Вернуться в главное меню", 14);
	AddConsoleTextColor("Введите номер действия...", 7);
	int selected = 0;
	cin >> selected;
	return selected;
}

void studentsEditSubMenu(Student ***students, const int maxStudentsCount, int *studentsCount) {
	int selectedMode = 0;
	do {
		printAllStudents(*students, *studentsCount);
		selectedMode = modeSelectMenu();
		switch (selectedMode)
		{
		case 1:
			userStudentAdd(students, maxStudentsCount, studentsCount);
			break;
		case 2:
			userStudentEdit(students, *studentsCount);
			break;
		case 3:
			userStudentDelete(students, studentsCount);
			break;
		case 4:
			userStudentDeleteAll(students, studentsCount);
			break;
		default:
			break;
		}
	} while (selectedMode != 5);
}

void printAllStudents(Student **students, const int studentsCount) {
	if (studentsCount > 0) {
		for (int i = 0; i < studentsCount; i++) {
			AddConsoleTextColor("Номер студента - " + to_string(i), 224);
			PrintStudent(*students[i]);
		}
	}
	else {
		AddConsoleTextColor("Список студентов пуст!");
	}
}

string readFilePath(string defaultPath) {
	string filePath = "";
	AddConsoleTextColor("Введите адрес файла или любой сивол, чтобы выбрать стандартный путь...", 14);
	cin >> filePath;
	filePath = filePath.length() > 1 ? filePath : defaultPath;
	return filePath;
}

void userAddStudentsFromFile(Student ***students, const int maxStudentsCount, int *studentsCount, const string defaultPath) {
	AddConsoleTextColor("______Добавление студентов из файла______", 224);
	bool isExit = false;
	bool isSuccess = false;
	do {
		string filePath = readFilePath(defaultPath);
		isSuccess = AddStudentsFromFile(filePath, students, maxStudentsCount, studentsCount);
		if (isSuccess == false) {
			AddConsoleTextColor("Ошибка! Неверный путь к файлу\nВвести снова?\n0. Да\t1. Нет");
			cin >> isExit;
		}
	} while (isSuccess == false && isExit == false);
}

bool userStudentCreate(Student &newStudent, string oldStudent = "Студент: Иванов Иван Иванович; Группа: имя_группы; Оценки: Математика - 4, Русский язык - зачет;") {
	AddConsoleTextColor("______Создание студента______", 224);
	AddConsoleTextColor("Введите информацию о студенте в формате\"" + oldStudent + "\"", 14);
	string sNewStudent = "";
	getline(cin, sNewStudent);
	getline(cin, sNewStudent);
	if (Init(newStudent, sNewStudent)) {
		return true;
	}
	else
	{
		return false;
	}
}

void userStudentAdd(Student ***students, const int maxStudentsCount, int *studentsCount) {
	Student *newStudent = new Student();
	AddConsoleTextColor("______Добавление студента______", 224);
	bool isSuccess = false, isExit = false;
	do
	{
		isSuccess = userStudentCreate(*newStudent);
		if (isSuccess == false) {
			AddConsoleTextColor("Попробовать создать студента снова?\n0. Да\t1. Нет");
			cin >> isExit;
		}
	} while (isSuccess == false && isExit == false);
	if (isExit == false) {
		
		AddStudent(students, maxStudentsCount, studentsCount, *newStudent);
	}
	else {
		Kill(newStudent);
	}
}

bool selectStudentNum(int &studentNum, const int studentCount) {
	AddConsoleTextColor("Введите номер студента...", 14);
	cin >> studentNum;
	if (studentNum >= 0 && studentNum < studentCount) {
		return true;
	}
	else {
		return false;
	}
}

void userStudentEdit(Student ***students,const int studentsCount) {
	AddConsoleTextColor("______Изменение студента______", 224);
	int studentNum = -1;
	bool isExit = false, isSuccess = false;
	do
	{
		isSuccess = selectStudentNum(studentNum, studentsCount);
		if (isSuccess == false) {
			AddConsoleTextColor("Ошибка! Неверный номер студента\nВвести снова?\n0. Да\t1. Нет");
			cin >> isExit;
		}
	} while (isSuccess == false && isExit == false);
	if (isExit == false) {
		Student **localStudents = *students;
		Student *newStudent = new Student();
		isSuccess = false;
		do
		{
			isSuccess = userStudentCreate(*newStudent, StudentToString(*localStudents[studentNum]));
			if (isSuccess == false) {
				AddConsoleTextColor("Попробовать создать студента снова?\n0. Да\t1. Нет");
				cin >> isExit;
			}
		} while (isSuccess == false && isExit == false);
		if (isExit == false) {
			Kill(localStudents[studentNum]);
			localStudents[studentNum] = newStudent;
		}
		else {
			Kill(newStudent);
		}
	}
}

void userStudentDelete(Student ***students, int *studentsCount) {
	AddConsoleTextColor("______Удаление студента______", 224);
	int studentNum = -1;
	bool isExit = false, isSuccess = false;
	do
	{
		isSuccess = selectStudentNum(studentNum, *studentsCount);
		if (isSuccess == false) {
			AddConsoleTextColor("Ошибка! Неверный номер студента\nВвести снова?\n0. Да\t1. Нет");
			cin >> isExit;
		}
	} while (isSuccess == false && isExit == false);
	if (isExit == false) {
		Student **localStudents = *students;
		int newStudentsCount = *studentsCount - 1, tmpStudentNum = 0, tmpNewStudentNum = 0;
		Student **newStudents = new Student*[newStudentsCount];
		isSuccess = true;
		do
		{
			if (tmpStudentNum != studentNum) {
				newStudents[tmpNewStudentNum] = localStudents[tmpStudentNum];
				tmpNewStudentNum++;
			}
			tmpStudentNum++;
			isExit = tmpStudentNum < *studentsCount ? false : true;
		} while (isExit == false);
		*studentsCount = newStudentsCount;
		*students = newStudents;
		string deletedStudent = localStudents[studentNum]->fio;
		Kill(localStudents[studentNum]);
		delete localStudents;
		AddConsoleTextColor("Студент " + deletedStudent + " успешно удален!", 10);
	}
}

void userStudentDeleteAll(Student ***students, int *studentsCount) {
	AddConsoleTextColor("______Удаление всех студентов______", 224);
	AddConsoleTextColor("Вы уверены что хотите удалить всех студентов?\n0. Да\t1. Нет");
	bool isExit = true;
	cin >> isExit;
	if (isExit == false) {
		Student **localStudents = *students;
		for (int i = 0; i < *studentsCount; i++) {
			Kill(localStudents[i]);
		}
		*studentsCount = 0;
		//delete localStudents;
		//localStudents = 0;
		AddConsoleTextColor("Все студенты успешно удаленты!", 10);
	}
	else {
		AddConsoleTextColor("Удаление студентов отменено!", 10);
	}
}

void userSaveStudentsToFile(Student **students, const int studentsCount, const string defaultPath) {
	AddConsoleTextColor("______Сохранение студентов в файл______", 224);
	bool isExit = false, isSuccess = false;
	do {
		string filePath = readFilePath(defaultPath);
		isSuccess = SaveStudentsToFile(filePath, students, studentsCount);
		if (isSuccess == false) {
			AddConsoleTextColor("Ошибка! Неверный путь к файлу\nВвести снова?\n0. Да\t1. Нет");
			cin >> isExit;
		}
	} while (isSuccess == false && isExit == false);
}
