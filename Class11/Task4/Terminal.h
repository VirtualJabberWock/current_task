#pragma once
#include "..\aquaUtils\pch.h"
#include "User.h"
#include "AquaDBMS.h"

string getPasswordFromUser();

/*
@return 1 - if success, 0 - if error
*/
int auth(string login, string password, User* user, AquaDatabase* db);

