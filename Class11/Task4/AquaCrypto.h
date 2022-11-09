#pragma once
#include "..\aquaUtils\StringUtils.h"
#include "CryptoField.h";

CryptoF field;

void ACRYPTO_DisposeInstance(); //VERY IMPORTANT

string hashPassword(string a);
string hashString(string a);

/*
@private
*/
string hashToHexString(unsigned char* in);

