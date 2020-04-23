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

	AddStudentsFromFile("/studentsMarks.txt", &students, maxStudentsCount, &studentsCount);
	AddSubjects(*students[0], "������� ���� - �� �����;");
	for (int i = 0; i < studentsCount; i++) {
		AddConsoleTextColor("����� �������� - " + to_string(i), 224);
		PrintStudent(*students[i]);
		//cout << StudentToString(*students[i]);
	}
	SaveStudentsToFile("newStudentsMarks.txt", students, studentsCount);
	getchar();
	return 0;
}

bool mainMenu() {
	AddConsoleTextColor("______����______", 224);
	AddConsoleTextColor("1. ������� ���� �� ����������", 14);
	AddConsoleTextColor("2. ������� ���� ���������", 14);
	AddConsoleTextColor("3. ��������� ��������� � ����", 14);
	AddConsoleTextColor("4. �����");
	AddConsoleTextColor("������� ����� ��������...", 7);
	int selected = 0;
	string filepath;
	cin >> selected;
	switch (selected)
	{
	case 1:
		AddConsoleTextColor("������� ����� �����",7);
		cin >> filepath;

		break;
	default:
		break;
	}
	return true;
}
