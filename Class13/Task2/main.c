#include <stdio.h>
#include "../../aquaUtils/pch.h"
#include <locale.h>
#include <Windows.h>

errno_t displayData(IntV* data);
void gotoxy(int x, int y);
IntV* generateData(int c);

int main(int argc, string_t* argv) {

	if (argc != 2) return panic("Invalid args!");
	int count = atoi(argv[1]);
	setlocale(LC_ALL, "");
	IntV* data_ptr = 0;
	while (True) {
		data_ptr = generateData(count);
		displayData(data_ptr);
		system("pause");
		system("cls");
	}
}

IntV* generateData(int count)
{
	srand((unsigned int)GetTickCount64());
	if (count == 0) panic("Can't display data");
	IntV* spreading = (IntV*)malloc(sizeof(IntV));
	if (spreading == 0) return panic("Malloc error!");
	spreading->ptr = (int*)initArray(10, sizeof(int));
	spreading->size = 10;
	for (int i = 0; i < count; i++) {
		int remainder = rand() % 10;
		spreading->ptr[remainder]++;
	}
	return spreading;
}

errno_t displayData(IntV* data)
{
	if (data == 0) return panic_NPE(displayData, "<IntV> data");
	const double display_m = 20;
	double weight = 0;
	for (int i = 0; i < data->size; i++) {
		weight = max(weight, (double)data->ptr[i]);
	}
	weight = display_m / weight;
	for (int i = 0; i < data->size; i++) {
		int g = ((double)data->ptr[i] * weight);
		for (int a = 0; a < g; a++) {
			gotoxy(i * 6, display_m - a);
			printf("[%d]", i);
		}
	}
	gotoxy(0, 22);
	return 0;
}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
