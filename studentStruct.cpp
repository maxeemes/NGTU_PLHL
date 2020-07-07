#include "studentStruct.h"
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;
//�����: 10 - �������, 12 - �������, 7 - �����, 14 - ������, 224 - ������ �� ������ ����
bool AddConsoleTextColor(const string error,const int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	cout << error << endl;
	SetConsoleTextAttribute(hConsole, 7);
	return true;
}

Student *Create()
{
	Student *sNew = new Student();
	sNew->valid = false;
	sNew->fio = "";
	sNew->group = "";
	sNew->subjCount = 0;
	sNew->marks = 0;
	return sNew;
}

bool Clear(Student &student)
{
	student.valid = false;
	student.fio = "";
	student.group = "";
	student.subjCount = 0;
	delete[] student.marks;
	return true;
}


bool Kill(Student *student)
{
	delete[] student->marks;
	delete student;
	return true;
}

bool AddStudents(Student ***students, const int maxStudentsCount, int *studentsCount, Student ***newStudents, int newStudentsCount) {
	cout << "���������� " << newStudentsCount << " ���������..." << endl;
	int studentsCnt = *studentsCount + newStudentsCount;
	if (studentsCnt <= maxStudentsCount) {
		Student **resStudents = new Student*[studentsCnt];
		Student **localNewStudents = *newStudents;
		Student **localStudents = *students;
		for (int i = 0; i < *studentsCount; i++) {
			resStudents[i] = localStudents[i];
		}
		for (int i = *studentsCount, j = 0; i < studentsCnt; i++, j++) {
			resStudents[i] = localNewStudents[j];
		}
		*studentsCount = studentsCnt;
		delete *students;
		*students = resStudents;
		return true;
	}
	else
	{
		AddConsoleTextColor("������ ���������� ���������! ��������� ������������ ���������� ���������!");
		return false;
	}
}

bool AddStudent(Student ***students, const int maxStudentsCount, int *studentsCount, Student &newStudent) {
	Student **newStudents = new Student*[1];
	newStudents[0] = &newStudent;
	AddStudents(students, maxStudentsCount, studentsCount, &newStudents, 1);
	delete newStudents;
	return false;
}

//������ ������: "���� - 5, ���������� - 4, ���-������ - �����;"
bool AddSubjects(Student &student, const string subjectMarks) {
	int endPos = subjectMarks.find(";");
	if (endPos > 0)
	{
		int nextPos = -2, newSubjectsCount = student.subjCount;
		do
		{
			newSubjectsCount++;
			nextPos = subjectMarks.find(", ", nextPos + 2);
		} while (nextPos > 0);
		
		SubjectMark *newSubjects = new SubjectMark[newSubjectsCount];

		for (int i = 0; i < student.subjCount; i++) {
			newSubjects[i].mark = student.marks[i].mark;
			newSubjects[i].subject = student.marks[i].subject;
		}

		string strSubj = "";
		int prevPos = 0, partPos;
		nextPos = 0;
		for (int i = student.subjCount; i < newSubjectsCount; i++)
		{
			nextPos = subjectMarks.find(", ", prevPos);
			nextPos = nextPos > 0 ? nextPos : endPos;
			strSubj = subjectMarks.substr(prevPos, nextPos - prevPos);
			prevPos = nextPos + 2;
			partPos = strSubj.find(" - ");
			if (partPos > 0)
			{
				newSubjects[i].subject = strSubj.substr(0, partPos);
				newSubjects[i].mark = strSubj.substr(partPos + 3);
			}
			else
			{
				newSubjects[i].subject = strSubj;
				newSubjects[i].mark = "-";
			}
		}
		delete[] student.marks;
		student.subjCount = newSubjectsCount;
		student.marks = newSubjects;

		return true;
	}
	else {
		AddConsoleTextColor("������ ������������� ������!");
		return false;
	}
}

//������ ������: "�������: ����� ������ ����������; ������: 19����1; ������: ���� - 5, ���������� - 4, ���-������ - �����;"
bool Init(Student &student, string str)
{
	int fioPos = -1, groupPos = -1, marksPos = -1, endPos = -1;
	fioPos = str.find("�������: ") + 9;
	groupPos = str.find("; ������: ", fioPos) + 10;
	marksPos = str.find("; ������: ", groupPos) + 10;
	endPos = str.find(';', marksPos);
	if (fioPos >= 9 && groupPos >= 10 && marksPos >= 10 && endPos >= 1)
	{
		student.valid = true;
		student.fio = str.substr(fioPos, groupPos - 10 - fioPos);
		student.group = str.substr(groupPos, marksPos - 10 - groupPos);
		student.subjCount = 0;
		if (marksPos != endPos)
		{
			//string strSubjs = str.substr(marksPos, endPos - marksPos);
			AddSubjects(student, str.substr(marksPos, endPos - marksPos + 1));
		}
		return true;
	}
	else
	{
		AddConsoleTextColor("������ ������������� ������!");
		if(fioPos < 9) AddConsoleTextColor("�� ������� ��� ��������!");
		if(groupPos < 10) AddConsoleTextColor("�� ������� ������ ��������!");
		if(marksPos < 10) AddConsoleTextColor("�� ������� ������ ��������!");
		if(endPos < 1) AddConsoleTextColor("�� ������� ��������� ������!");

		AddConsoleTextColor("������: \"" + str + "\"");
		return false;
	}
}

bool AddStudentsFromFile(string filePath, Student ***students, const int maxStudentsCount, int *studentsCount)
{
	AddConsoleTextColor("������ ��������� �� ����� " + filePath + "...", 7);
	int maxStudentsCnt = maxStudentsCount - *studentsCount;
	Student **newStudents = new Student*[maxStudentsCnt];
	ifstream fileStudents (filePath);
	if (fileStudents.is_open()) {
		const int maxLen = 1024;
		Student *newStudent;
		int newStudentsCnt = 0;
		/*char line[maxLen];
		while (fileStudents.getline(line, streamsize(maxLen))) {
			if (newStudentsCnt < maxStudentsCnt) newStudent = Create();
			if (newStudentsCnt < maxStudentsCnt && Init(*newStudent, line)) {
				newStudents[newStudentsCnt] = newStudent;
				newStudentsCnt++;
			}
		}*/
		for (string line; getline(fileStudents, line);) {
			if (newStudentsCnt < maxStudentsCnt)
			{
				newStudent = Create();
				if (Init(*newStudent, line)) {
					newStudents[newStudentsCnt] = newStudent;
					newStudentsCnt++;
				}
			}
		}
		fileStudents.close();

		AddStudents(students, maxStudentsCount, studentsCount, &newStudents, newStudentsCnt);
		delete newStudents;
		return true;
	}
	else {
		AddConsoleTextColor("������! ���� �� ������!");
		fileStudents.close();
		getchar();
		return false;
	}

}

bool PrintStudent(const Student &student)
{
	if (student.valid) {
		cout.width(62);
		cout.fill('_');
		cout << "" << endl;
		cout.fill(' ');
		cout << left << "�������: " + student.fio << endl;
		cout << left << "������: " + student.group << endl;
		cout << left << "������" << endl;
		cout.fill('_');
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 10);
		cout.width(62);
		cout << "" << endl;
		cout.width(50);
		cout << left << "|�������" << right << "|";
		cout.width(10);
		cout << left << "������" << right << "|";
		cout << endl;
		SetConsoleTextAttribute(hConsole, 7);
		for (int i = 0; i < student.subjCount; i++)
		{
			cout.width(50);
			cout << left << "|" + student.marks[i].subject << right << "|";
			cout.width(10);
			if (student.marks[i].mark == "�� �����") SetConsoleTextAttribute(hConsole, 12);
			cout << left << student.marks[i].mark;
			SetConsoleTextAttribute(hConsole, 7);
			cout << right << "|" << endl;
		}
		cout.width(62);
		cout << "" << endl;
		return true;
	}
	else {
		AddConsoleTextColor("������! ������ � �������� �� �������!\n������: """ + StudentToString(student) + """");

		return false;
	}
}
//������ �������� ������: "�������: ����� ������ ����������; ������: 19����1; ������: ���� - 5, ���������� - 4, ���-������ - �����;"
string StudentToString(const Student &student) {
	string res = "";
	res += "�������: " + (student.fio.empty() ? "��� �����������" : student.fio) + "; ";
	res += "������: " + (student.group.empty() ? "������ �����������" : student.group) + "; ";
	res += "������: ";
	if (student.subjCount) {
		for (int i = 0; i < student.subjCount; i++) {
			res += i > 0 ? ", " : "";
			res += (student.marks[i].subject.empty() ? "��� �������� �����������" : student.marks[i].subject) + " - ";
			res += (student.marks[i].mark.empty() ? "������ �����������" : student.marks[i].mark);
		}
	}
	res += ";";
	return res;
}

bool SaveStudentsToFile(const string filePath, Student **students, const int studentsCount) {
	cout << "���������� " << studentsCount << " ��������� � ���� " + filePath + "..." << endl;
	ofstream outFile;
	outFile.open(filePath);
	for (int i = 0; i < studentsCount; i++) {
		outFile << StudentToString(*students[i]) << endl;
	}
	outFile.close();
	AddConsoleTextColor("�������� ��������� � ����", 10);
	return true;
}