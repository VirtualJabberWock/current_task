#pragma once
#include "..\aquaUtils\AquaTypes.h"
#include "..\aquaUtils\ArrayUtils.h"
#include "ExtendedTypes.h"
#include <Windows.h>

#define __AquaDBSelf__ struct tagAquaDatabase* self
#define DB_UUID unsigned long long

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
	FILE* handleToWrite;
	FILE* handleToRead;
	Table* tables;
	int tables_c;
	unsigned int lines;
	void (*OpenOrCreate) (__AquaDBSelf__, string name);
	void (*putObject) (__AquaDBSelf__, string table, HashMap* obj);
	errno_t (*find)
		(__AquaDBSelf__, string table, string key, string value, HashMap *out);
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
errno_t AQUADB_Default_find(__AquaDBSelf__, string table, string key, string value, HashMap* out);
void AQUADB_Default_Close(__AquaDBSelf__);

int AQUADB_Private_FileExists(LPCWSTR file);
int AQUADB_Private_ScanForTables(__AquaDBSelf__);
void AQUADB_Private_Insert(__AquaDBSelf__, string line, Table* table);