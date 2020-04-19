#include "studentStruct.h"
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>   // WinApi header

using namespace std;
//Цвета: 10 - зеленый, 12 - красный
bool AddConsoleTextColor(const string error,const int color = 12) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
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
	student.fio = "";
	student.group = "";
	student.subjCount = 0;
	delete[] student.marks;
	return true;
}


bool Kill(Student *student)
{
	delete student->marks;
	delete student;
	return true;
}

bool PrintStudent(const Student &student)
{
	if (student.valid) {
		cout.width(62);
		cout.fill('_');
		cout << "" << endl;
		cout.fill(' ');
		cout << left << "Студент: " + student.fio << endl;
		cout << left << "Группа: " + student.group << endl;
		cout << left << "ОЦЕНКИ" << endl;
		cout.fill('_');
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 10);
		cout.width(62);
		cout << "" << endl;
		cout.width(50);
		cout << left << "|ПРЕДМЕТ" << right << "|";
		cout.width(10);
		cout << left << "ОЦЕНКА" << right << "|";
		cout << endl;
		SetConsoleTextAttribute(hConsole, 7);
		for (int i = 0; i < student.subjCount; i++)
		{
			cout.width(50);
			cout << left << "|" + student.marks[i].subject << right << "|";
			cout.width(10);
			if (student.marks[i].mark == "не зачет") SetConsoleTextAttribute(hConsole, 12);
			cout << left << student.marks[i].mark;
			SetConsoleTextAttribute(hConsole, 7);
			cout << right << "|" << endl;
		}
		cout.width(62);
		cout << "" << endl;
		return true;
	}
	else {
		AddConsoleTextColor("Ошибка! Данные о студенте не валидны!");
		return false;
	}

}


//Пример строки: "ПЯВУ - 5, Математика - 4, Веб-дизайн - зачет;"
bool AddSubjects(Student &student, const string subjectMarks) {
	int endPos = subjectMarks.find(";");
	if (endPos)
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
		AddConsoleTextColor("Ошибка распознавания оценок!");
		return false;
	}
}

//Пример строки: "Студент: Савва Максим Русланович; Группа: 19ИСТВ1; Оценки: ПЯВУ - 5, Математика - 4, Веб-дизайн - зачет;"
bool Init(Student &student, string str)
{
	int fioPos = -1, groupPos = -1, marksPos = -1, endPos = -1;
	fioPos = str.find("Студент: ") + 9;
	groupPos = str.find("; Группа: ", fioPos) + 10;
	marksPos = str.find("; Оценки: ", groupPos) + 10;
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
			AddSubjects(student, str.substr(marksPos, endPos - marksPos));
		}
		return true;
	}
	else
	{
		AddConsoleTextColor("Ошибка распознавания строки!");
		if(fioPos < 9) AddConsoleTextColor("Не найдено имя студента!");
		if(groupPos < 10) AddConsoleTextColor("Не найдена группа студента!");
		if(marksPos < 10) AddConsoleTextColor("На найдены оценки студента!");
		if(endPos < 1) AddConsoleTextColor("Не найдено окончание строки!");

		AddConsoleTextColor("Строка: \"" + str + "\"");
		return false;
	}
}


/*bool AddSubjects(Student &student,const string _subject,const string _mark)
{
	SubjectMark *tmpMarks = new SubjectMark[student.subjCount + 1];
	for (int i = 0; i < student.subjCount; i++) 
	{
		tmpMarks[i] = student.marks[i];
	}
	tmpMarks[student.subjCount].subject = _subject;
	tmpMarks[student.subjCount].mark = _mark;
	delete[] student.marks;
	student.subjCount++;
	student.marks = tmpMarks;
	return true;
}*/

bool ReadFileStudents(string filePath, Student ***students, const int maxStudentsCount, int *studentsCount)
{
	Student **resStudents = new Student*[maxStudentsCount];
	for (int i = 0; i < *studentsCount; i++) {
		resStudents[i] = *students[i];
	}
	ifstream fileStudents (filePath);
	if (fileStudents.is_open()) {
		const int maxLen = 1024;
		Student *newStudent;
		int studentsCnt = *studentsCount;
		char line[maxLen];
		while (fileStudents.getline(line, streamsize(maxLen))) {
			if (studentsCnt< maxStudentsCount) newStudent = Create();
			if (studentsCnt< maxStudentsCount && Init(*newStudent, line)) {
				resStudents[studentsCnt] = newStudent;
				studentsCnt++;
			}
		}
		fileStudents.close();
		*studentsCount = studentsCnt;
		delete *students;
		*students = new Student*[*studentsCount];
		*students = resStudents;
		return true;
	}
	else {
		AddConsoleTextColor("Ошибка! Файл не найден!");
		fileStudents.close();
		getchar();
		return false;
	}

}