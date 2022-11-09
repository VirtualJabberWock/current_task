#include "AquaCrypto.h"
#include "..\aquaUtils\pch.h"
#include "ExtendedTypes.h"
#include "AquaDBMS.h"
#include "User.h"
#include "Terminal.h"

/*
0157143164141154 - default (Sam Sepiol)
psw: hyperv1s0r
*/

void requestForAuth();
void mainMenu(User* user);

AquaDatabase db;

int main() {
	requestForAuth();
}

void mainMenu(User* user){
	while (1) {
		system("cls");
		StringBuilder sb; InitStringBuilder(&sb, "\nWelcome, ");
		sb.add(&sb, user->name)->add(&sb, " ")->add(&sb, user->surname);
		printf(sb.buildAndDispose(&sb));
		printf("\n> ");
		int s = scanf("");
	}
}

void requestForAuth() {
	char buffer[256];
	getcwd(buffer, 256);
	InitAquaDatabase(&db, SUS_str_copy(buffer));
	db.OpenOrCreate(&db, "users.db");
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
		printf("Wrong!\n");
		goto Entry;
	}
}



/*
TODO LIST:

HashMap correct disposing! with all string and nodes!!!

*/