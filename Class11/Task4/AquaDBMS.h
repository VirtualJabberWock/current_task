#pragma once
#include "..\aquaUtils\AquaTypes.h"
#include "..\aquaUtils\ArrayUtils.h"
#include "ExtendedTypes.h"
#include <Windows.h>

#define __AquaDBSelf__ struct tagAquaDatabase* self
#define DB_UUID unsigned long long

#define SIGN_NEEDED 1
#define SIGN_CREATE 0

typedef struct tagTableRect {

	string tname;
	unsigned int start;
	unsigned int end;

} Table;

typedef struct tagAquaDatabase {

	int __notnull__;
	const char* db_dir;
	string current_db;
	string shadow_path;
	string current_path;
	FILE* handleToWrite;
	FILE* handleToRead;
	FILE* signFile;
	Table* tables;
	int tables_c;
	unsigned int lines;
	void (*OpenOrCreate) (__AquaDBSelf__, string name);
	void (*putObject) (__AquaDBSelf__, string table, HashMap* obj);
	int (*find)
		(__AquaDBSelf__, string table, string key, string value, HashMap *out);
	void (*set)(__AquaDBSelf__, int pointer, DataBox* obj);
	void (*_close) (__AquaDBSelf__);

} AquaDatabase;

/*

TODO:

create table...
drop table...

*/

/* 
*  WARNING: Current version only for Windows OS
*/
void InitAquaDatabase(AquaDatabase* db, const char* db_dir);

void AQUADB_Default_OpenOrCreate(__AquaDBSelf__, string name);
void AQUADB_Default_putObject(__AquaDBSelf__, string table, DataBox * obj);
int AQUADB_Default_find(__AquaDBSelf__, string table, string key, string value, HashMap* out);
void AQUADB_Default_set(__AquaDBSelf__, int line, DataBox* out);
void AQUADB_Default_Close(__AquaDBSelf__);


int AQUADB_Private_FileExists(LPCWSTR file);
int AQUADB_Private_ScanForTables(__AquaDBSelf__);
void AQUADB_Private_Insert(__AquaDBSelf__, string line, Table* table);
void AQUADB_Private_Replace(__AquaDBSelf__, string line, int pointer);
string AQUADB_Private_Sign(__AquaDBSelf__, BOOL replace_mode);
void AQUADB_Private_Rewind(__AquaDBSelf__);