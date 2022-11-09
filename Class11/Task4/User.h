#pragma once
#include "..\aquaUtils\pch.h"
#include "ExtendedTypes.h"


typedef struct tagUser {
	string name;
	string surname;
	__int64 shadow_balance;
	string credentials;
	string shadow_pass;
} User;

/*
userdata:
	{
		"name",
		"surname",
		"credentials",
		"balance",
		"psw_hash"
	}
*/
void InitUser(User* user, HashMap* userdata);
void ExtractUserData(HashMap* userdata, User* user);
