// laba2.cpp : Defines the entry point for the console application.
//

#include "studentStruct.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	const int maxStudentsCount = 1000;
	const string defaultFilePeth = "/studentsMarks.txt";
	int studentsCount = 0;
	Student **students = 0;// = new Student*[maxStudentsCount];
	//Student **students = new Student*[maxStudentsCount];
	/*students[0] = Create();
	students[0]->fio = "fio";
	students[0]->group = "group";
	students[0]->marks = new SubjectMark[10];
	students[0]->subjCount = 1;
	students[0]->marks[0].subject = "subject subject subject";
	students[0]->marks[0].mark = "5";
	
	students[1] = Create();
	Init(*students[1], "�������: ����� ������ ����������; ������: 19����1; ������: ���� - 5, ���������� - 4, ���-������ - �� �����;");
	//TODO ������� ������ �� �����
	//TODO ������� AddSubject
	string subject = "������� ����";
	string mark = "�����";
	AddSubj(*students[1], subject, mark);*/

	/*AddStudentsFromFile("/studentsMarks.txt", &students, maxStudentsCount, &studentsCount);
	AddSubjects(*students[0], "������� ���� - �� �����;");
	for (int i = 0; i < studentsCount; i++) {
		AddConsoleTextColor("����� �������� - " + to_string(i), 224);
		PrintStudent(*students[i]);
		//cout << StudentToString(*students[i]);
	}
	SaveStudentsToFile("newStudentsMarks.txt", students, studentsCount);*/
	int selected = 0;
	do {
		selected = mainMenu();
		string filepath;
		switch (selected)
		{
		case 1:
			filepath = readFilePath(defaultFilePeth);
			AddStudentsFromFile(filepath, &students, maxStudentsCount, &studentsCount);
			break;
		case 2:
			int selectedMode = 0;
			do {
				printAllStudents(students, studentsCount);
				selectedMode = modeSelectMenu();
				switch (selectedMode)
				{
				case 1:
					userStudentAdd(&students, maxStudentsCount, &studentsCount);
					break;
				case 2:
					userStudentEdit(&students, studentsCount);
					break;
				default:
					break;
				}
			} while (selectedMode != 3);
			break;
		case 3:
			AddConsoleTextColor("______���������� ��������� � ����______", 224);

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
	AddConsoleTextColor("1. ������� ���� �� ����������", 14);
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

void printAllStudents(Student **students, int studentsCount) {
	for (int i = 0; i < studentsCount; i++) {
		AddConsoleTextColor("����� �������� - " + to_string(i), 224);
		PrintStudent(*students[i]);
	}
}

string readFilePath(string defaultPath) {
	string filePath = "";
	AddConsoleTextColor("������� ����� ����� ��� �������� ���� ������...", 14);
	cin >> filePath;
	filePath = filePath.length() > 1 ? filePath : defaultPath;
	return defaultPath;
}

void userAddStudentsFromFile(Student ***students, const int maxStudentsCount, int *studentsCount) {
	do {

	}while()
}

bool userStudentCreate(Student &newStudent) {
	AddConsoleTextColor("______�������� ��������______", 224);
	AddConsoleTextColor("������� ���������� � �������� � ������� ""�������: ������ ���� ��������; ������: ���_������; ������: ���������� - 4, ������� ���� - �����;""", 14);
	string sNewStudent = "";
	cin >> sNewStudent;
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
	bool isCreated = false, isExit = false;

	while (userStudentCreate(*newStudent) == false && isExit == false)
	{
		AddConsoleTextColor("����������� ������� �������� �����?\n0. ��\t1. ���");
		cin >> isExit;
	}
	if (isExit == false) {
		AddStudent(students, maxStudentsCount, studentsCount, *newStudent);
	}
	else {
		Kill(newStudent);
	}
}

bool selectStudentNum(int &studentNum, const int studentCount) {
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
	AddConsoleTextColor("������� ����� ��������, �������� ������ ��������...", 14);
	int studentNum = -1;
	bool isExit = false;
	while (selectStudentNum(studentNum, studentsCount) && isExit == false)
	{
		AddConsoleTextColor("������! �������� ����� ��������\n������ �����?\n0. ��\t1. ���");
		cin >> isExit;
	}
	if (isExit == false) {
		Student *newStudent = new Student();
		while (userStudentCreate(*newStudent) == false && isExit == false)
		{
			AddConsoleTextColor("����������� ������� �������� �����?\n0. ��\t1. ���");
			cin >> isExit;
		}
		if (isExit == false) {
			Kill(*students[studentNum]);
			students[studentNum] = &newStudent;
		}
		else {
			Kill(newStudent);
		}
	}
}

