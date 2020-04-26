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
	Init(*students[1], "Студент: Савва Максим Русланович; Группа: 19ИСТВ1; Оценки: ПЯВУ - 5, Математика - 4, Веб-дизайн - не зачет;");
	//TODO сделать чтение из файла
	//TODO сделать AddSubject
	string subject = "Русский язык";
	string mark = "зачет";
	AddSubj(*students[1], subject, mark);*/

	/*AddStudentsFromFile("/studentsMarks.txt", &students, maxStudentsCount, &studentsCount);
	AddSubjects(*students[0], "Русский язык - не зачет;");
	for (int i = 0; i < studentsCount; i++) {
		AddConsoleTextColor("Номер студента - " + to_string(i), 224);
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

			} while (selectedMode != 3);
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
	AddConsoleTextColor("1. Открыть файл со студентами", 14);
	AddConsoleTextColor("2. Просмотр/редактирование оценок студентов", 14);
	AddConsoleTextColor("3. Сохранить студентов в файл", 14);
	AddConsoleTextColor("4. ВЫХОД");
	AddConsoleTextColor("Введите номер действия...", 7);
	int selected = 0;
	cin >> selected;
	return selected;
}

int modeSelectMenu() {
	AddConsoleTextColor("______Выберите действие______", 224);
	AddConsoleTextColor("1. Добавить студента", 14);
	AddConsoleTextColor("2. Изменить информацию о студенте", 14);
	AddConsoleTextColor("3. Вернуться в главное меню", 14);
	int selected = 0;
	cin >> selected;
	return selected;
}

void printAllStudents(Student **students, int studentsCount) {
	for (int i = 0; i < studentsCount; i++) {
		AddConsoleTextColor("Номер студента - " + to_string(i), 224);
		PrintStudent(*students[i]);
	}
}

string readFilePath(string defaultPath) {
	string filePath = "";
	AddConsoleTextColor("Введите адрес файла или оставьте поле пустым...", 14);
	cin >> filePath;
	filePath = filePath.length() > 1 ? filePath : defaultPath;
	return defaultPath;
}

