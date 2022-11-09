#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "ArrayUtils.h" 
#include "AquaTypes.h"
#include "StringUtils.h"

#define string const char*

#define ERROR_CANT_READ        0x133700
#define ERROR_CANT_WRITE       0x133701
#define ERROR_BUFFER_OVERFLOW  0x133702
#define ERROR_EMPTY_FILE  0x133703
#define STATUS_SUCCESS         0x0

#define FILENNAME_CHANNEL 1

#define DYNAMIC_SIZE -1

int openFile(FILE** hFile, string filename);
void openFile_s(FILE** hFile, string filename);
void openFileText_s(FILE** hFile, string filename);

void openFileW_s(FILE** hFile, string filename);
int openFileW(FILE** hFile, string filename);

void closeFile(FILE* hFile);

void readAllLines_s(FILE* hFile, StringV* bucket);
void writeAllLines_s(FILE* hFile, StringV* lines);

void handleIOError(int status, string msg);
void _handleIOError(int status);