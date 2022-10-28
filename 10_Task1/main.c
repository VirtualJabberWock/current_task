#include <stdio.h>

void handleScanError(int);

int main() {
}

void handleScanError(int errorCode) {
    if (errorCode != 0) return;
    printf("Error: scanf can't read any field\nTerminate process...");
    exit(1);
}




