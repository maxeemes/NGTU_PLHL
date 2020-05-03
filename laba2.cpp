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
void userSaveStudentsToFile(Student **students, const int studentsCount);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	const int maxStudentsCount = 1000;
	const string defaultFilePeth = "/studentsMarks.txt";
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
			userSaveStudentsToFile(students, studentsCount);
			break;
		default:
			break;
		}
	} while (selected != 4);

	getchar();
	return 0;
}

int mainMenu() {
	AddConsoleTextColor("______����______", 224);
	AddConsoleTextColor("1. �������� ��������� �� �����", 14);
	AddConsoleTextColor("2. ��������/�������������� ���������� � ���������", 14);
	AddConsoleTextColor("3. ��������� ��������� � ����", 14);
	AddConsoleTextColor("4. �����");
	AddConsoleTextColor("������� ����� ��������...", 7);
	int selected = 0;
	cin >> selected;
	return selected;
}

int modeSelectMenu() {
	AddConsoleTextColor("______�������� ��������______", 224);
	AddConsoleTextColor("1. �������� ��������", 14);
	AddConsoleTextColor("2. �������� ���������� � ��������", 14);
	AddConsoleTextColor("3. ��������� � ������� ����", 14);
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
		default:
			break;
		}
	} while (selectedMode != 3);
}

void printAllStudents(Student **students, const int studentsCount) {
	for (int i = 0; i < studentsCount; i++) {
		AddConsoleTextColor("����� �������� - " + to_string(i), 224);
		PrintStudent(*students[i]);
	}
}

string readFilePath(string defaultPath) {
	string filePath = "";
	AddConsoleTextColor("������� ����� �����...", 14);
	cin >> filePath;
	filePath = filePath.length() > 1 ? filePath : defaultPath;
	return filePath;
}

void userAddStudentsFromFile(Student ***students, const int maxStudentsCount, int *studentsCount, const string defaultPath) {
	AddConsoleTextColor("______���������� ��������� �� �����______", 224);
	bool isExit = false;
	bool isSuccess = false;
	do {
		string filePath = readFilePath(defaultPath);
		isSuccess = AddStudentsFromFile(filePath, students, maxStudentsCount, studentsCount);
		if (isSuccess == false) {
			AddConsoleTextColor("������! �������� ���� � �����\n������ �����?\n0. ��\t1. ���");
			cin >> isExit;
		}
	} while (isSuccess == false && isExit == false);
}

bool userStudentCreate(Student &newStudent, string oldStudent = "�������: ������ ���� ��������; ������: ���_������; ������: ���������� - 4, ������� ���� - �����;") {
	AddConsoleTextColor("______�������� ��������______", 224);
	AddConsoleTextColor("������� ���������� � �������� � �������\"" + oldStudent + "\"", 14);
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
	AddConsoleTextColor("______���������� ��������______", 224);
	bool isSuccess = false, isExit = false;
	do
	{
		isSuccess = userStudentCreate(*newStudent);
		if (isSuccess == false) {
			AddConsoleTextColor("����������� ������� �������� �����?\n0. ��\t1. ���");
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
	AddConsoleTextColor("������� ����� ��������, �������� ������ ��������...", 14);
	cin >> studentNum;
	if (studentNum >= 0 && studentNum < studentCount) {
		return true;
	}
	else {
		return false;
	}
}

void userStudentEdit(Student ***students,const int studentsCount) {
	AddConsoleTextColor("______��������� ��������______", 224);
	int studentNum = -1;
	bool isExit = false, isSuccess = false;
	do
	{
		isSuccess = selectStudentNum(studentNum, studentsCount);
		if (isSuccess == false) {
			AddConsoleTextColor("������! �������� ����� ��������\n������ �����?\n0. ��\t1. ���");
			cin >> isExit;
		}
	} while (isSuccess == false && isExit == false);
	if (isExit == false) {
		Student *newStudent = new Student();
		isSuccess = false;
		do
		{
			isSuccess = userStudentCreate(*newStudent, StudentToString(**students[studentNum]));
			if (isSuccess == false) {
				AddConsoleTextColor("����������� ������� �������� �����?\n0. ��\t1. ���");
				cin >> isExit;
			}
		} while (isSuccess == false && isExit == false);
		if (isExit == false) {
			Kill(*students[studentNum]);
			*students[studentNum] = newStudent;
		}
		else {
			Kill(newStudent);
		}
	}
}

void userSaveStudentsToFile(Student **students, const int studentsCount) {
	AddConsoleTextColor("______���������� ��������� � ����______", 224);
	bool isExit = false, isSuccess = false;
	do {
		string filePath = readFilePath("C:/");
		isSuccess = SaveStudentsToFile(filePath, students, studentsCount);
		if (isSuccess == false) {
			AddConsoleTextColor("������! �������� ���� � �����\n������ �����?\n0. ��\t1. ���");
			cin >> isExit;
		}
	} while (isSuccess == false && isExit == false);
}
