#include "Terminal.h"
#include "AquaDBMS.h"
#include "AquaCrypto.h"
#include "..\aquaUtils\pch.h"

string getPasswordFromUser() {
    char c;
    char* password = (char*)initArray(100, sizeof(char));
    int i = 0;
    do {
        c = getch();
        if (c == '\n' || c == '\r') break;
        password[i] = c;
        printf("*");
        i++;
        if (i > 99) break;
    } while ((c != '\n') && (c != '\r'));
    return buildString(password, 100);
}

string getLoginFromUser() {
    char c;
    char* password = (char*)initArray(256, sizeof(char));
    int i = 0;
    do { 
        c = getch();
        if (c == '\n' || c == '\r') break;
        if (c == '\b') {
            printf("\b");
            i = min(i-1, 0);
            continue;
        }
        password[i] = c;
        printf("%c", c);
        if ((i+1) % 4 == 0) {
            printf(" ");
        }
        i++;
        if (i > 255) break;
    } while ((c != '\n') && (c != '\r'));
    return buildString(password, 256);
}


int auth(string login, string password, User* user, AquaDatabase* db)
{
    HashMap data;
    InitHashMap(&data);
    int s = db->find(db, "users", "credentials", login, &data);
    if (s == 0x404) return 0;
    InitUser(user, &data);
    string a = hashPassword(password);
    if (strcmp(a, user->shadow_pass) == 0) {
        return 1;
    }
    return 0;
}