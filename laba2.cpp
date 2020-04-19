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
	//Student **students = new Student*[maxStudentsCount];
	/*students[0] = Create();
	students[0]->fio = "fio";
	students[0]->group = "group";
	students[0]->marks = new SubjectMark[10];
	students[0]->subjCount = 1;
	students[0]->marks[0].subject = "subject subject subject";
	students[0]->marks[0].mark = "5";
	
	students[1] = Create();
	Init(*students[1], "Студент: Савва Максим Русланович; Группа: 19ИСТВ1; Оценки: ПЯВУ - 5, Математика - 4, Веб-дизайн - не зачет;");
	//TODO сделать чтение из файла
	//TODO сделать AddSubject
	string subject = "Русский язык";
	string mark = "зачет";
	AddSubj(*students[1], subject, mark);*/

	Student **students = 0;// = new Student*[maxStudentsCount];
	ReadFileStudents("/studentsMarks.txt", &students, maxStudentsCount, &studentsCount);
	AddSubjects(*students[0], "Русский язык - не зачет;");
	for (int i = 0; i < studentsCount; i++) {
		PrintStudent(*students[i]);
	}
	
	//Clear(*students[1]);

	//cout << "OK!";
	getchar();
	return 0;
}

