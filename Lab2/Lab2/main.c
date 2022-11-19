#include <stdio.h>
#include "ExtendedTypes.h"
#include "Matrices.h"
#include <stdlib.h>
#include "MatrixCalculator.h"
#include "DirectoryUtils.h"
#include <conio.h>

#define EXIT_CHAR 'E'
#define INIT_CHAR 'I'

string_t left_info = "NULL";
string_t right_info = "NULL";

Matrix left;
Matrix right;
Matrix out;

char getUserAction();
void displayMenu();
int showLoadMatrixMenu();
int loadMatrixFromFile(Matrix* ptr, const char** info_ptr);

void gotoxy(int x, int y);

int main() {

    left.__notnull__ = 0; right.__notnull__ = 0;

    while (True) {
        system("cls");
        displayMenu();
        char c = getUserAction();
        if (c == '?') continue;
        if (c == EXIT_CHAR) return 0;
        if (c == INIT_CHAR) showLoadMatrixMenu();
        if (right.__notnull__ != 0) InitMatrix(&out, right.w, left.h);
        else InitMatrix(&out, left.w, left.h);
        if (handleMatrixOperation(&left, &right, &out, c)) {
            printf("\n");
            system("pause");
        }
    }
}

char getUserAction()
{
    char c = _getch();
    if (c < '0' || c > '6') return '?';
    if (c == '0') return INIT_CHAR;
    if (c == '6') return EXIT_CHAR;
    return __map_k[(c - '1')];
}

void displayMenu()
{
    printf("\n\tMatrices:\n\t[\n\t\tLEFT = {%s},\n\t\tRIGHT = {%s}\n\t];",
        left_info,
        right_info
    );
    printf("\n\n");
    printf("\n\t[0] Load matrix from file");
    printf("\n\t[1] Add         (LEFT + RIGHT)");
    printf("\n\t[2] Substract   (LEFT - RIGHT)");
    printf("\n\t[3] Multiply    (LEFT x RIGHT)");
    printf("\n\t[4] Transpose   (LEFT^t)");
    printf("\n\t[5] Determinate (det[LEFT])");
    printf("\n\t[6] Exit");
    printf("\n\t...\n\t");
}

int showLoadMatrixMenu()
{
    system("cls");
    printf("\n\tWhich of matrices you wan't to load?\n");
    printf("\n\t[0] LEFT matrix {%s}", left_info);
    printf("\n\t[1] RIGHT matrix {%s}", right_info);
    printf("\n\n\t... ");
    char c = _getch();
    if (c == '0') return loadMatrixFromFile(&left, &left_info);
    if (c == '1') return loadMatrixFromFile(&right, &right_info);
    printf("\n\tInvalid command!");
    return 0;
}

int loadMatrixFromFile(Matrix* ptr, const char** info)
{
    system("cls");
    string_t path = getDirectoryPath("matrices");
    StringV files; InitStringV(&files);
    getFilesInDirectory(wideFromMultibyte(path), &files);
    printf("\n\n\tSelect a file to scan:\n{\n");
    for (int i = 0; i < files.size; i++) {
        printf("\n    ----  %d. %s", 
            i, 
            getFilenameFromPath(files.ptr[i])
        );
    }
    printf("\n}\n\t* Use arrows to up or down selector\n\t* Enter to confirm");
    int select = 0;
    gotoxy(4, 5 + select);
    printf("===> ");
    gotoxy(3, 5 + select);
    while (True) {
        char c = _getch();
        gotoxy(4, 5 + select);
        printf("---- ");
        if ((int)c == 72) select = abs((select - 1) % files.size);
        if ((int)c == 80) select = (select + 1) % files.size;
        if ((int)c == 13) break;
        gotoxy(4, 5 + select);
        printf("===> ");
        gotoxy(3, 5 + select);
    }
    ScanMatrixFromFile(ptr, files.ptr[select]);
    if (ptr->__notnull__ != 0) {
        *info = getFilenameFromPath(files.ptr[select]);
    }
    else {
        system("cls");
        printf("\n\n\tError: Invalid Matrix! Now matrix is NULL\n\n");
        *info = "NULL";
        system("pause");
    }
    files.clear(&files);
    return 1;
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
