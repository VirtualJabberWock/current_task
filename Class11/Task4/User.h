#pragma once
#include "..\aquaUtils\pch.h"
#include "ExtendedTypes.h"


typedef struct tagUser {
	string name;
	string surname;
	__int64 shadow_balance;
	string credentials;
	string shadow_pass;
	__int64 cash;
	int phone_balance;
	int db_tag;

} User;

/*
userdata:
	{
		"name",
		"surname",
		"credentials",
		"balance",
		"cash",
		"phone_b",
		"psw_hash"
	}
*/
void InitUser(User* user, HashMap* userdata, int db_tag);
void ExtractUserData(HashMap* userdata, User* user);
void UnboxUserData(DataBox* out, User* user);
