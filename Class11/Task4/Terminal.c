#include "Terminal.h"
#include "AquaDBMS.h"
#include "AquaCrypto.h"
#include "..\aquaUtils\pch.h"

void handleUserRequest(User *user, AquaDatabase* db, char command) {
    if (command == '1') {
        withdraw(user, db);
        return;
    }
    if (command == '0') {
        if (db->__notnull__) db->_close(&db);
        panic("eXit");
    }
    if (command == '2') {
        deposit(user, db);
        return;
    }
    if (command == '3') {
        telephony(user, db);
        return;
    }
    printf("\nCommand '%s' doesn't exists\n\n", command);
    system("pause");
}

string getPasswordFromUser() {
    char c;
    char* password = (char*)initArray(100, sizeof(char));
    int i = 0;
    do {
        c = getch();
        if (c == '\n' || c == '\r') break;
        if (c == '\b') {
            if (i > 0) {
                printf("\b");
                i--;
            }
            continue;
        }
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
            if (i > 0) {
                printf("\b");
                i--;
            }
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
    InitUser(user, &data, s);
    string a = hashPassword(password);
    if (strcmp(a, user->shadow_pass) == 0) {
        return 1;
    }
    return 0;
}

int withdraw(User* user, AquaDatabase* db)
{
    system("cls");
    printf("\n\tYour current balance: %lld", user->shadow_balance);
    printf("\n\n\tPlease enter the amount to withdraw");
    printf("\n\tAmount: ");
    __int64 amount = 0;
    int s = scanf_s("%lld", &amount);
    if ((s == 0) || (amount < 0)) {
        printf("\nInvalid Input!!!\n");
        system("pause"); return 0;
    }
    if (user->shadow_balance - amount < 0) {
        printf("\nInsufficient funds (Not enough money)!\n");
        system("pause"); return 0;
    }
    user->shadow_balance = user->shadow_balance - amount;
    user->cash = user->cash + amount;
    DataBox box; InitDataBox(&box);
    UnboxUserData(&box, user);
    db->set(db, user->db_tag, &box);
    printf("\nSuccess! Now you have %lld$ as cash\n", user->cash);
    system("pause"); return 0;
}

void deposit(User* user, AquaDatabase* db)
{
    system("cls");
    printf("\n\tYou have %lld$ as a cash.", user->cash);
    printf("\n\n\tPlease enter the amount to deposit");
    printf("\n\tAmount: ");
    __int64 amount = 0;
    int s = scanf_s("%lld", &amount);
    if ((s == 0) || (amount < 0)) {
        printf("\nInvalid Input!!!\n");
        system("pause"); return 0;
    }
    if (user->cash - amount < 0) {
        printf("\nInsufficient funds (Not enough money)!\n");
        system("pause"); return 0;
    }
    user->cash = user->cash - amount;
    user->shadow_balance = user->shadow_balance + amount;
    DataBox box; InitDataBox(&box);
    UnboxUserData(&box, user);
    db->set(db, user->db_tag, &box);
    printf("\nSuccess! Now you have %lld$ in your account\n", user->shadow_balance);
    system("pause"); return 0;
}

void telephony(User* user, AquaDatabase* db)
{
    system("cls");
    printf("\n\tYour current balance: %lld", user->shadow_balance);
    printf("\n\tYour current mobile operator: Girth5");
    printf("\n\tConnecting with Girth5 servers...");
    Sleep(1000); // for visual
    printf("\n\n\tNote: minimum sum to transfer is 25$");
    printf("\n\tAmount:");
    __int64 amount = 0;
    int s = scanf_s("%lld", &amount);
    if (s == 0) {
        printf("\nInvalid Input!!!\n");
        system("pause"); return 0;
    }
    if (amount < 25) {
        printf("\nValue smaller than minimum!\n");
        system("pause"); return 0;
    }
    if (user->shadow_balance - amount < 0) {
        printf("\nInsufficient funds (Not enough money)!\n");
        system("pause"); return 0;
    }
    user->shadow_balance = user->shadow_balance - amount;
    user->cash = user->cash + amount;
    DataBox box; InitDataBox(&box);
    UnboxUserData(&box, user);
    db->set(db, user->db_tag, &box);
    printf("\nSuccess! Now you have %lld$ as cash\n", user->cash);
    system("pause"); return 0;
}
