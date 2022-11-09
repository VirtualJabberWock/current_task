#include "AquaCrypto.h"
#include "..\aquaUtils\ArrayUtils.h"
#include "../aquaUtils/AquaTypes.h"

#define CRYPTO_VECTOR 32 
#define CRYPTO_DEPTH 33 // should be bigger than 2
//NOTE :: (CRYPTO_VECTOR x CRYPTO_DEPTH) should be smaller than input strings
// => (32 x 33) symbols can store

const char* PASS_SALT = "!ZN_SV@P_784c4799faE008E?GYAYI"; // 31

void ACRYPTO_DisposeInstance()
{
	if (field.__init__ == 0) return;
	field.Dispose(&field);
	field.__init__ = 0;
}

/*
@return [!panic] hash if OK, panic if error;
*/
string hashPassword(string a)
{
	if (SUS_getStringLength(a) > 256) {
		panic("Error:\n\tCrypto.AquaCrypto :: password size > 256");
	}
	StringBuilder sb;
	InitStringBuilder(&sb, a);
	string r0 = hashString(a);
	sb.add(&sb, r0)->add(&sb, PASS_SALT);
	return hashString(sb.buildAndDispose(&sb));
}


/*
@return [?panic] hash if OK, may call panic if internal error
*/
string hashString(string a) {
	
	InitCryptoField(&field, CRYPTO_VECTOR, CRYPTO_DEPTH);

	if (SUS_getStringLength(a) == 0) return hashString("<empty>");
	InitCryptoFVector(&field, a);
	char* last;
	//Round #1
	for (int i = 0; i < CRYPTO_DEPTH; i++) {
		if (i % 3 == 0) field.lRot(&field, i, i + 5);
		if (i % 3 == 1) field.rRot(&field, i, 17);
		if (i % 3 == 2) field.organic(&field, i, 19);
	}
	field.sum(&field, &last);
	ACRYPTO_DataInjection(&field, a);
	//Round #2^10
	field.set(&field, 1, last);
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < CRYPTO_DEPTH; i++) {
			if (i % 4 == 0) field.rRot(&field, i, abs(i ^ j));
			if (i % 4 == 1) field.lRot(&field, i, abs(7 ^ i));
		}
	}
	field.sum(&field, &last);	
	string z = hashToHexString(last);
	field.Dispose(&field);
	return z;
}


string hashToHexString(unsigned char* in)
{
	char* result = initArray(CRYPTO_VECTOR * 2 + 1, sizeof(char));
	int size = 0;
	const char* hex = "0123456789abcdef";
	int j = 0;
	for (int i = 0; i < CRYPTO_VECTOR*2; i += 2) {
		pushToCharArray(&result, &size, hex[(in[j] >> 4) & 0xF]);
		pushToCharArray(&result, &size, hex[(in[j]) & 0xF]);
		j++;
	}
	free(in);
	return buildString(result, size);
}