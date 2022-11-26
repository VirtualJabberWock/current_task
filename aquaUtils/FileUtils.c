#include "FileUtils.h"

int openFile(FILE** hFile, string_t filename) {
    return fopen_s(hFile, filename, "r");
}

void openFile_s(FILE** hFile, string_t filename) {
    setTemp(FILENNAME_CHANNEL, filename);
    handleIOError(fopen_s(hFile, filename, "r"), "OPEN_FILE_ERROR: ");
}

void openFileText_s(FILE** hFile, string_t filename) {
    setTemp(FILENNAME_CHANNEL, filename);
    handleIOError(fopen_s(hFile, filename, "rt"), "OPEN_FILE_ERROR: ");
}

void openFileW_s(FILE** hFile, string_t filename) {
    handleIOError(fopen_s(hFile, filename, "w"), "OPEN_FILE_ERROR: ");
}

int openFileW(FILE** hFile, string_t filename) {
    return fopen_s(hFile, filename, "w");
}

void closeFile(FILE* hFile) {
    handleIOError(fclose(hFile), "CLOSING_FILE_ERROR: ");
}

void readAllLines_s(FILE* hFile, StringV* sv) {
    int status = STATUS_SUCCESS;
    if (hFile == 0) return ERROR_CANT_READ;
    int s = 1;
    while (s != 0) {
        char* buffer = initArray(2048, 1);
        s = fgets(buffer, 2048, hFile);
        if (ferror(hFile) != 0) {
            _fcloseall();
            perror("I/O");
            panic("[!panic]");
        }
        if (s == 0) break;
        sv->put(sv, buildLine(buffer, 2048));
    }
    handleIOError(status, "Input file: ");
}

void writeAllLines_s(FILE* hFile, StringV* lines)
{
    int status = STATUS_SUCCESS;
    int tmp;
    for (int i = 0; i < lines->size; i++) {
        tmp = fprintf_s(hFile, "%s\n", lines->ptr[i]);
        if (tmp == 0) 
        {
             status = ERROR_CANT_WRITE;
             break;
        }
        if (tmp < 0) {
            printf("\nstatus = %d\n", tmp);
            status = tmp;
            break;
        }
    }
    handleIOError(status, "File writer: ");
}


void handleIOError(int status, string_t msg) {
    if (status == STATUS_SUCCESS) {
        return;
    }
    printf_s(msg);
    if (status == ERROR_CANT_READ) {
        printf_s("Can't READ data from file");
        status = 0;
    }
    if (status == ERROR_CANT_WRITE) {
        printf_s("Can't WRITE data to file");
        status = 0;
    }
    if (status == ERROR_BUFFER_OVERFLOW) {
        printf_s("Buffer overflow, number or single text line in input file too big (> 2048 chars).");
        status = 0;
    }
    if (status == 2) {
        printf_s(SUS_str_f("File <%> don`t exists!", getTemp(FILENNAME_CHANNEL)));
        status = 0;
    }
    if (status != 0) {
        perror("IO Error");
    }
    panic("\n...");
}

void _handleIOError(int status) {
    handleIOError(status, "IO Error: ");
}
