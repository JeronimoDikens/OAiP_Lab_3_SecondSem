/*
Используя функции и режим меню, создать бинарный файл из N структур,
просмотреть файл, добавить в файл новую информацию и, применяя режим прямого
доступа, выполнить задание по своему варианту.
Структура имеет вид: номер читательского билета, автор книги, название, дата
заказа. Вывести на экран содержимое файла. Поменять местами первую и
последнюю записи в файле.

*/
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>

#define MAX_COUNT 200

struct date {
	int year;
	int month;
	int day;
};

struct order {
	int num_ticket;
	char author[20];
	char name_of_book[20];
	struct date date_of_order;
};

int menu();
void file_reader(FILE*, int*);
void file_writer(struct order*, int*, FILE*);
struct order* new__struct_record(struct order*, int*);
void transpositioner(struct order*, int*);


errno_t err;
FILE* file;

int main(void) {

	static int size = 0;
	int choice;
	struct order* readers = (struct order*)calloc(size, sizeof(struct order));

	for (;;) {
		choice = menu();

		switch (choice) {
		case 0: {remove("text.dat");  exit(0); }; break;
		case 1: {err = fopen_s(&file, "text.dat", "wb");
			if (!(file == NULL)) {
				printf("File created\n");

				readers = new__struct_record(readers, &size);
				file_writer(readers, &size, file);

				fclose(file);
			}
			else {
				printf("Can't open file\n");
				exit(0);
			}}; break;
		case 2: {err = fopen_s(&file, "text.dat", "rb");
			if (!(file == NULL)) {
				printf("File opened\n");

				fseek(file, 0, SEEK_SET);
				file_reader(file, &size);

				fclose(file);
			}
			else {
				printf("Can't open file\n");
				exit(0);
			}}; break;
		case 3: {err = fopen_s(&file, "text.dat", "ab");
			if (!(file == NULL)) {
				printf("File opened\n");

				readers = new__struct_record(readers, &size);
				file_writer(readers, &size, file);
				printf("Record added\n");

				fclose(file);
			}
			else {
				printf("Can't open file\n");
				exit(0);
			}}; break;
		case 4: {remove("text.dat");
			err = fopen_s(&file, "text.dat", "wb");
			if (!(file == NULL)) {
				printf("File opened\n");
				transpositioner(readers, &size);
				printf("Lines transpositioned\n");
				fseek(file, 0, SEEK_SET);
				int new_size = 1;
				for (int i = 0; i < size; i++, new_size++) {
					file_writer(readers, &new_size, file);
				}

				fclose(file);
			}
			else {
				printf("Can't open file\n");
				exit(0);
			}}; break;
		default: exit(0);
		}
	}
	return 0;
}

int menu() {
	int choice;
	do {
		printf("%s", "Welcome to programm. Make a choice:\n");
		printf("%s", "1. Create a file\n");
		printf("%s", "2. Review a file\n");
		printf("%s", "3. Add a record\n");
		printf("%s", "4. Transposition\n");
		printf("%s", "0. Finish program\n");
		printf("%s", "Choice: ");
		scanf_s("%d", &choice);
	} while (choice < 0 || choice>5);
	return choice;
}


struct order* new__struct_record(struct order* str_var, int* size) {
	(*size)++;
	struct order* tmp_pnt = (struct order*)realloc(str_var, (*size) * sizeof(struct order));
	printf("%s", "Number of ticket: ");
	scanf_s("%d", &tmp_pnt[((*size) - 1)].num_ticket);
	printf("%s", "Last name of author: ");
	scanf_s("%s", &tmp_pnt[((*size) - 1)].author, sizeof(char[20]));
	printf("%s", "Name of book: ");
	scanf_s("%s", &tmp_pnt[((*size) - 1)].name_of_book, sizeof(char[20]));
	printf("%s", "Date of order \nyear: ");
	scanf_s("%d", &tmp_pnt[((*size) - 1)].date_of_order.year);
	printf("%s", "month: ");
	scanf_s("%d", &tmp_pnt[((*size) - 1)].date_of_order.year);
	printf("%s", "day: ");
	scanf_s("%d", &tmp_pnt[((*size) - 1)].date_of_order.day);
	return tmp_pnt;
}


void file_writer(struct order* str_order, int* sz_str, FILE* file) {
	int sz = *sz_str;
	fwrite((str_order + (sz - 1)), sizeof(struct order), 1, file);
}

void file_reader(FILE* file, int* sz_struc) {
	struct order* temp_p = (struct order*)malloc(sizeof(struct order) * (*sz_struc));
	fread(temp_p, sizeof(struct order), *sz_struc, file);
	int i = 0;
	for (i; i < (*sz_struc); i++) {
		printf("%d %s %s %d.%d.%d\n",
			temp_p[i].num_ticket,
			temp_p[i].author,
			temp_p[i].name_of_book,
			temp_p[i].date_of_order.year,
			temp_p[i].date_of_order.year,
			temp_p[i].date_of_order.year);
	}

}



void transpositioner(struct order* str_p, int* sz_p) {
	int sz = *sz_p;
	struct order temp_struc = str_p[0];
	str_p[0] = str_p[sz - 1];
	str_p[sz - 1] = temp_struc;
}