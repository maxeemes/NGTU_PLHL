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
			AddConsoleTextColor("______Сохранение студентов в файл______", 224);

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
	AddConsoleTextColor("2. Просмотр/редактирование информации о студентах", 14);
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

void userAddStudentsFromFile(Student ***students, const int maxStudentsCount, int *studentsCount) {
	do {

	}while()
}

bool userStudentCreate(Student &newStudent) {
	AddConsoleTextColor("______Создание студента______", 224);
	AddConsoleTextColor("Введите информацию о студенте в формате ""Студент: Иванов Иван Иванович; Группа: имя_группы; Оценки: Математика - 4, Русский язык - зачет;""", 14);
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
	AddConsoleTextColor("______Добавление студента______", 224);
	bool isCreated = false, isExit = false;

	while (userStudentCreate(*newStudent) == false && isExit == false)
	{
		AddConsoleTextColor("Попробовать создать студента снова?\n0. Да\t1. Нет");
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
	AddConsoleTextColor("______Изменение студента______", 224);
	AddConsoleTextColor("Введите номер студента, которого хотите изменить...", 14);
	int studentNum = -1;
	bool isExit = false;
	while (selectStudentNum(studentNum, studentsCount) && isExit == false)
	{
		AddConsoleTextColor("Ошибка! Неверный номер студента\nВвести снова?\n0. Да\t1. Нет");
		cin >> isExit;
	}
	if (isExit == false) {
		Student *newStudent = new Student();
		while (userStudentCreate(*newStudent) == false && isExit == false)
		{
			AddConsoleTextColor("Попробовать создать студента снова?\n0. Да\t1. Нет");
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

