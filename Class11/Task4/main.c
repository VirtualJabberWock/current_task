#include "AquaCrypto.h"
#include "..\aquaUtils\pch.h"
#include "ExtendedTypes.h"
#include "AquaDBMS.h"
#include "User.h"
#include "Terminal.h"
#include "Core.h"

#define DEBUG_MODE 1
#define DEBUG_LOGIN "0157143164141154"
#define DEBUG_PASSWORD "hyperv1s0r"

/*
0157143164141154 - default (Sam Sepiol)
psw: hyperv1s0r
*/

/*
TODO:
check database sign (but maybe it already done)
*/

void requestForAuth();
void mainMenu(User* user);
int checkDebugMode();
void showHelp();
void OnExit(int exitCode);

AquaDatabase db;

int main() {

	hookExitProccess(OnExit);

	char buffer[256];
	getcwd(buffer, 256);
	InitAquaDatabase(&db, SUS_str_copy(buffer));
	db.OpenOrCreate(&db, "users.db");

	system("color f");
	if (checkDebugMode()) return 0;
	requestForAuth();

}

void mainMenu(User* user){
	system("color f");

	while (1) {

		system("cls");
		const char balance_str[20];
		_i64toa_s(user->shadow_balance, balance_str, 20, 10);
		printf("\n\n\tUser: %s %s\n\tBalance: %lld\n\tCash: %lld",
			user->name, user->surname,
			user->shadow_balance, user->cash);
		printf("\n\tId: %d", user->db_tag);
		printf("\n\n");
		printf("\n\t[0] Exit");
		printf("\n\t[1] Withdraw");
		printf("\n\t[2] Deposit");
		printf("\n\t[3] Telephony (Transfer money to your mobile operator)");
		printf("\n\n\t");
		char cmd = getch();
		handleUserRequest(user, &db ,cmd);
	}
}

int checkDebugMode()
{
	if (DEBUG_MODE) {
		User user;
		int s = auth(DEBUG_LOGIN, DEBUG_PASSWORD, &user, &db);
		if (s == 1) {
			mainMenu(&user);
		}
		return 1;
	}
	return 0;
}

void showHelp()
{
	system("cls");
	printf("\n");
	printf("=-=-=-=-=-=-=-= HELP =-=-=-=-=-=-=-=-=-=\n");
	printf("\n\thelp     - show this page");
	printf("\n\twithdraw - withdraw money");
	printf("\n\texit     - exit");
	printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
	system("pause");
}

void requestForAuth() {

Entry:

	printf("Login(Your credentials): ");
	string login = SUS_trim(
		SUS_clearDublicateSpaces(getLoginFromUser())
	);
	printf("\nPassword: ");
	string psw = getPasswordFromUser();

	User user;
	int s = auth(login, psw, &user, &db);
	if (s == 1) {
		mainMenu(&user);
	}
	else {
		system("cls");
		system("color c");
		printf("Wrong!\n");
		goto Entry;
	}
}

void OnExit(
	int exitCode
) {
	if (db.__notnull__ == 1) db._close(&db);
	TerminateProcess(GetCurrentProcess(), 1);
}



/*
TODO LIST:

HashMap correct disposing! with all string and nodes!!!

*/