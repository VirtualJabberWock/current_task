#pragma once
#include "..\aquaUtils\StringUtils.h"

#define ACRYPTO_SELF struct tagCryptoF *self

const char __cryto_joker[8][8];

typedef struct tagCryptoF {
	char** matrix;
	int w;
	int h;
	void (*lRot)(ACRYPTO_SELF, int row, int shift);
	void (*rRot)(ACRYPTO_SELF, int row, int shift);
	void (*organic)(ACRYPTO_SELF, int row, int shift);
	void (*set)(ACRYPTO_SELF, int row, char* data);
	void (*sum)(ACRYPTO_SELF, char** out);
	void (*Dispose) (ACRYPTO_SELF);
	
	int __init__;
} CryptoF, *CryptoFP;

void InitCryptoField(CryptoFP self, int width, int height);
void InitCryptoFVector(CryptoFP self, string iv);

void ACRYPTO_Default_lRot(CryptoFP self, int row, int s);
void ACRYPTO_Default_rRot(CryptoFP self, int row, int s);
void ACRYPTO_Default_Set(CryptoFP self, int row, char* data);
void ACRYPTO_Default_Organic(CryptoFP self, int row, int s);
void ACRYPTO_Default_Initalization(CryptoFP self, string base, int len);
void ACRYPTO_Default_Sum(CryptoFP self, char** out);
void ACRYPTO_Default_Dispose(CryptoFP self);

void ACRYPTO_DataInjection(CryptoFP self, string iv);