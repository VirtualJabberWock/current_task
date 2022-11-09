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

AquaDatabase db;

int main() {
	char buffer[256];
	getcwd(buffer, 256);
	InitAquaDatabase(&db, SUS_str_copy(buffer));
	db.OpenOrCreate(&db, "users.db");
Entry:
	printf("Login(Your credentials): ");
	string login = "0157143164141154";
	printf("\nPassword: ");
	string psw = getPasswordFromUser();
	User user;
	int s = auth(login, psw, &user, &db);
	if (s == 1) {
		printf("Yes!");
	}
	else {
		goto Entry;
	}
}



/*
TODO LIST:

HashMap correct disposing! with all string and nodes!!!

*/