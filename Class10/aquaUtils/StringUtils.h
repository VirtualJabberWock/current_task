#pragma once
#define string const char*
#define CharList char*

#define F_Scan128 "%128[^\n\r]"
#define F_Scan512 "%512[^\n\r]"
#define F_Scan1024 "%1024[^\n\r]"

// UTILS

string SUS_clearDublicateSpaces(string str);
int SUS_getStringLength(string str);
int SUS_parseInteger32(string str, __int32* out);
int SUS_parseInteger32_AnyWay(string str, __int32* out);
int SUS_isStringNumber(string str);
string SUS_str_copy(string str1);

// UTILS + STRING_BUILDER HELPERS

string SUS_trim(string str);
string* SUS_split(string, char delimiter, int* parts_count);
string* SUS_split_match(string, char delimiter, int max_parts_c, int* parts_count);
string SUS_str_c(string str1, string str2);
string SUS_str_f(string format, string str2, char special);
void SUS_str_unlock(string const_str, int* out_len, CharList* out_buffer);
string SUS_str_lock(char* buffer, int size);
string SUS_str_bucket_assemble(string* bucket, int bucket_size, char delim);

//a
