#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXname 30
#define MAXmark 10
#define MAXstd 50

char alphabetB[] = { "АБВҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ" };  //масив українських символів, для сортування

typedef struct student {		//оголошення структури
	char name[MAXname];			//ім'я студента
	double mark[MAXmark];		//масив оцінок студента
} stud;

void inputStudents();			//ф-ія для вводу даних про студентів
void printSheets();				//ф-ія виведення таблиці
void printStudent(stud*, int);	//ф-ія виведення одного студента
void sortStudents();			//ф-ія сортування масиву сутдентів
double mark(stud);				//ф-ія обчислення середнього балу

stud students[MAXstd];			//масив студентів
int stn, markn;					//кількість студентів та оцінок

int main() {
	system("chcp 1251"); system("cls");
	
	/*Введення*/
	printf("Введіть кількість оцінок: ");
	scanf_s("%d", &markn);
	printf("Вводьте дані про студентів(кінець -- порожній рядок):\n");
	inputStudents();

	/*Виведення таблиць*/
	printf("\n\n\tВведені дані:\n");
	printSheets();
	sortStudents();
	printf("\n\n\tСписок, відсортований за абеткою:\n");
	printSheets();

	/*Пошук двох кращих*/
	int firstID = 0, secondID = 0, i;			//індекси кращих студентів
	double firstMark = 0, secondMark = 0, temp;	
	for (i = 0; i < stn; i++) {					
		temp = mark(students[i]);
		if (temp > firstMark) {					
			secondID = firstID;					
			secondMark = firstMark;				
			firstID = i;						
			firstMark = temp;					
												
		} else if (temp > secondMark) {			
			secondID = i;						
			secondMark = temp;					
		}
	}

	/*Виведення двох кращих*/
	printf("\n\n\tДвоє кращих:\n");
	printStudent(&students[firstID], 0);
	printf("\tСередній бал -- %lf", mark(students[firstID]));
	printStudent(&students[secondID], 1);
	printf("\tСередній бал -- %lf", mark(students[secondID]));
	printf("\n\n");
	system("pause");
	return 0;
}

double mark(stud st) {
	int i;
	double sum = 0;
	for (i = 0; i < markn; i++) sum += st.mark[i];
	return sum / markn;
}

void inputStudents() {
	char input_name[MAXname] = "";
	int i;
	do {
		rewind(stdin);
		printf("Введіть ім'я студента: ");
		gets_s(input_name);						//записуємо у буферний рядок
		if (strcmp(input_name, "") == 0)		//Перевіряємо чи це не порожній рядок
			break;
		strcpy(students[stn].name, input_name);	//копіюємо у ім'я студента
		printf("Введіть оіцнки: ");
		for (i = 0; i < markn; i++) {
			scanf_s("%lf", &students[stn].mark[i]);	//записуємо оцінки студента
		}
	} while (++stn < MAXstd);
}

void printSheets() {
	stud* ptrstudend;
	int i;
	for (i = 0; i < 6 + MAXname + 10 * markn; i++) printf("_");		//рамка таблиці
	for (ptrstudend = students, i = 0; i < stn; i++, ptrstudend++) {
		printStudent(ptrstudend, i);	//виводимо дані заданого студента
	}
	printf("\n");
	for (i = 0; i < 6 + MAXname + 10 * markn; i++) printf("_");
}

void printStudent(stud *st, int i) {
	int j;
	printf("\n|%3d|%-30s|", i + 1, st->name);						//виводимо ім'я
	for (j = 0; j < markn; j++) printf("%9.2lf|", *st->mark+j);		//виводимо список оцінок
}

void sortStudents() {
	stud *ptrstudend, temp;
	int i;
	/*Бульбашкове сортування*/
	for (i = 0; i < stn-1; i++) {
		for (ptrstudend = students; ptrstudend + 1 < students + stn - i; ptrstudend++) {
			if (strchr(alphabetB, ptrstudend->name[0]) > strchr(alphabetB, (ptrstudend + 1)->name[0])) { //порівнюємо 				
				temp = *ptrstudend;													//порядкові номери перших символів імені
				*ptrstudend = *(ptrstudend + 1);
				*(ptrstudend + 1) = temp;
			}
		}
	}
}

/*4
Войчак Катерина
78 88 96 84
Мірза Дарина
81 56 49 36
Федак Данило
94 51 88 54
Яремчук Антон
88 69 97 96
Ґрибов Артем
51 51 50 21
Руппа Кирило
76 80 61 64
Анна Герилова
81 51 67 75
*/