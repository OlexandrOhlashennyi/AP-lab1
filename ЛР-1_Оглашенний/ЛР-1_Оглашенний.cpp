#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXname 30
#define MAXmark 10
#define MAXstd 50

char alphabetB[] = { "АБВҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ" };

int n = 0, markn;

typedef struct student {
	char name[MAXname];
	double mark[MAXmark];
} stud;

stud students[MAXstd];

void inputStudents(stud[]);
void printsheets();
void printStudent(stud*, int);
void sortStudents(stud[]);
double mark(stud);

int main() {
	system("chcp 1251"); system("cls");
	
	printf("Введіть кількість оцінок: ");
	scanf_s("%d", &markn);
	printf("Вводьте дані про студентів(кінець -- порожній рядок):\n");
	inputStudents(students);

	printf("\n\n\tВведені дані:\n");
	printsheets();
	sortStudents(students);
	printf("\n\n\tСписок, відсортований за абеткою:\n");
	printsheets();

	int firstID = 0, secondID = 0, i;
	double firstMark = 0, secondMark = 0, temp;
	for (i = 0; i < n; i++) {
		temp = mark(students[i]);
		if (temp > firstMark) {
			secondID = firstID;
			secondMark = firstMark;
			firstID = i;
			firstMark = temp;

		}
		else if (temp > secondMark) {
			secondID = i;
			secondMark = temp;
		}
	}

	printf("\n\n\tДвоє кращих:\n");
	printStudent(&students[firstID], 0);
	printStudent(&students[secondID], 1);
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

void inputStudents(stud[]) {
	char input_name[MAXname] = "";
	int i;
	do {
		rewind(stdin);
		printf("Введіть ім'я студента: ");
		gets_s(input_name);
		if (strcmp(input_name, "") == 0)
			break;
		strcpy(students[n].name, input_name);
		printf("Введіть оіцнки: ");
		for (i = 0; i < markn; i++) {
			scanf_s("%lf", &students[n].mark[i]);
		}
	} while (++n < MAXstd);
}

void printsheets() {
	stud* ptrstudend;
	int i;
	for (i = 0; i < 4 + MAXname + 10 * markn; i++) printf("_");
	for (ptrstudend = students, i = 0; i < n; i++, ptrstudend++) {
		printStudent(ptrstudend, i);
	}
	printf("\n");
	for (i = 0; i < 4 + MAXname + 10 * markn; i++) printf("_");
}

void printStudent(stud *st, int i) {
	int j;
	printf("\n%2d|%-30s|", i + 1, st->name);
	for (j = 0; j < markn; j++) printf("%9.2lf|", st->mark[j]);
}

void sortStudents(stud st[]) {
	stud *ptrstudend, temp;
	int i;
	for (i = 0; i < n; i++) {
		for (ptrstudend = st; ptrstudend + 1 < st + n - i; ptrstudend++) {
			if (strchr(alphabetB, ptrstudend->name[0]) > strchr(alphabetB, (ptrstudend + 1)->name[0])) {
				temp = *ptrstudend;
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