#pragma once
#include "..\aquaUtils\pch.h"


#define MAP_BLOCK_SIZE 64
#define MAX_MAP_KEY_SIZE 20

#define __HMSelf__ struct tagHashMap* self
#define lc_string const char* // lower case string

#define ERR_KEY_DONT_EXIST -1
#define ERR_NO 0
#define DEBUG_MODE 1

typedef struct tagHashNode {

	int hash;
	lc_string key;
	string_t value;
	struct tagHashNode* next;
	int __notnull__;

} HashNode;

#define HASHMAP_CLASSNAME "ExtendedTypes.HashMap"
typedef struct tagHashMap {

	HashNode* _nodes;
	int size;
	void (*put) (__HMSelf__, lc_string key, string_t value);
	string_t (*get) (__HMSelf__, lc_string key, errno_t* status);
	void (*dispose) (__HMSelf__);
	int __notnull__;

} HashMap;

typedef struct tagDataBox {

	StringV kv;
	StringV vv;

} DataBox;

void __InitHashNode(HashNode* node, int hash, lc_string key, string_t value);
void InitHashMap(HashMap *map);
void InitDataBox(DataBox* dB);

void HASHMAP_Default_put(__HMSelf__, lc_string key, string_t value);
string_t HASHMAP_Default_get(__HMSelf__, lc_string key, errno_t* status);
void HASHMAP_Default_dispose(__HMSelf__);
int HASHMAP_Private_hash(string_t s);
void HASHMAP_Private_checkKey(string_t key);