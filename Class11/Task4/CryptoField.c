#include "CryptoField.h"
#include "..\aquaUtils\ArrayUtils.h"

#define lvl1 7
#define lvl2 19

const char __cryto_joker[8][8] = {
	{0x9c, 0x8b, 0xec, 0x02, 0xf6, 0xbf, 0x0c, 0x49},
	{0xc1, 0x70, 0x6a, 0x94, 0xa3, 0x9a, 0xd4, 0x93},
	{0xcb, 0x95, 0x49, 0xba, 0x87, 0x80, 0xbf, 0xcd},
	{0xad, 0xbf, 0x01, 0x84, 0x17, 0xe9, 0xc4, 0x30},
	{0x39, 0x67, 0x3b, 0xa1, 0x54, 0xff, 0x09, 0x5b},
	{0xed, 0xa7, 0x80, 0x1e, 0xe3, 0x18, 0xe9, 0x69},
	{0xf7, 0x9a, 0x13, 0xc8, 0xf6, 0xba, 0x0d, 0xd6},
	{0x77, 0xe0, 0xfc, 0x3e, 0x96, 0x18, 0x46, 0x4a}
};

void InitCryptoField(CryptoFP self, int w, int h)
{
	if (h < 1) panic("Error:\n\tCrypto.CryptoField :: Nope!");
	self->w = w;
	self->h = h;
	self->matrix = initArray(h, sizeof(void*));
	self->lRot = ACRYPTO_Default_lRot;
	self->rRot = ACRYPTO_Default_rRot;
	self->organic = ACRYPTO_Default_Organic;
	self->sum = ACRYPTO_Default_Sum;
	self->set = ACRYPTO_Default_Set;
	self->Dispose = ACRYPTO_Default_Dispose;
	for (int i = 0; i < h; i++) {
		self->matrix[i] = initArray(w, sizeof(char));
		for (int j = 0; j < w; j++) {
			self->matrix[i][j] = 0;
		}
	}
	self->__init__ = 1;
}

void InitCryptoFVector(CryptoFP self, string iv)
{
	int len = SUS_getStringLength(iv);
	if (len > self->w * self->h)
		panic("Error:\n\tCrypto.CryptoField :: iv size > field size");
	ACRYPTO_Default_Initalization(self, iv, len);
	self->matrix[0][0] = '1';
	self->matrix[0][1] = '1'^iv[0];
	for (int i = 0; i < self->h; i++) {
		for (int j = 0; j < self->w; j++) {
			self->matrix[i][j] ^= iv[(i + j) % len];
		}
	}
	for (int i = 1; i < self->h; i++) {
		for (int j = 1; j < self->w; j++) {
			self->matrix[i][j] ^= self->matrix[i - 1][j - 1];
		}
	}
	ACRYPTO_Default_Organic(self, 0, 1);
}

void ACRYPTO_DataInjection(CryptoFP self, string iv)
{
	int len = SUS_getStringLength(iv);
	self->matrix[0][0] = '1';
	self->matrix[0][1] = '1' ^ iv[0];
	for (int i = 0; i < self->h; i++) {
		for (int j = 0; j < self->w; j++) {
			self->matrix[i][j] ^= iv[(i + j) % len];
		}
	}
	for (int i = 1; i < self->h; i++) {
		for (int j = 1; j < self->w; j++) {
			self->matrix[i][j] ^= self->matrix[i - 1][j - 1];
		}
	}
}

void ACRYPTO_Default_lRot(CryptoFP self, int row, int c) {
	for (int i = 0; i < self->w; i++) {
		self->matrix[row%self->h][i] 
			= self->matrix[row % self->h][abs(i + c) % self->w];
	}
}

void ACRYPTO_Default_rRot(CryptoFP self, int row, int c){
	for (int i = 0; i < self->w; i++) {
		self->matrix[row % self->h][i] 
			= self->matrix[row % self->h][abs(i - c) % self->w];
	}
}

void ACRYPTO_Default_Set(CryptoFP self, int row, char* data)
{
	for (int i = 0; i < self->w; i++) {
		self->matrix[row][i] ^= data[i % self->w];
	}
}

/*
removing data factor 
*/
void ACRYPTO_Default_Organic(CryptoFP self, int row, int c) {
	for (int i = 0; i < self->w; i++) {
		char base = self->matrix[c % self->h][i];
		int offset = __cryto_joker[abs(i + base) % 8][abs(i + c) % 8];
		self->matrix[row % self->h][i] ^=
			__cryto_joker[abs(offset+base) % 8][abs(offset + c) % 8];
	}
}

void ACRYPTO_Default_Initalization(CryptoFP self, string base, int len)
{
	for (int i = 0; i < self->w; i++) {
		for (int j = 0; j < self->h; j++) {
			self->matrix[j][i] =
				base[(i + j) % len] ^ (__cryto_joker[i % 8][(j+len) % 8]);
			if (base[(j+i+1) % len] % lvl1 == 0)
				self->matrix[j][i] ^= 
				base[(i + j + lvl1) % len] & (__cryto_joker[i % 8][j % 8]);
			if (base[(j + i + 1) % len] % lvl2 == 0)
				self->matrix[j][i] ^=
				base[(i + j + lvl2) % len] | (__cryto_joker[i % 8][j % 8]);
		}
	}
}

void ACRYPTO_Default_Sum(CryptoFP self, char** out) {
	char* buffer = initArray(self->w, sizeof(char));
	for (int i = 0; i < self->w; i++) {
		buffer[i] = 0;
	}
	for (int i = 0; i < self->w; i++) {
		for (int j = 0; j < self->h; j++) {
			buffer[i] ^= self->matrix[j][i];
		}
	}
	*out = buffer;
}

void ACRYPTO_Default_Dispose(CryptoFP self) {
	if (self->matrix == 0) return;
	for (int i = 0; i < self->h; i++) {
		free(self->matrix[i]);
	}
	free(self->matrix);
}