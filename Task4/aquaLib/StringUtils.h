#pragma once
#define string const char*
#define CharList char*

#define F_Scan128 "%128[^\n\r]"
#define F_Scan512 "%512[^\n\r]"
#define F_Scan1024 "%1024[^\n\r]"

string clearDublicateSpaces(string str);
int getStringLength(string str);
int parseInteger32(string str, __int32* out);
int isStringNumber(string str);

string trim(string str);
string* split(string, char delimiter, int* parts_count);

string str_copy(string str1);

string str_c(string str1, string str2);

/* replace every '%' to str2 in format string */
string str_f(string format, string str2);
void str_unlock(string const_str, int* out_len, CharList* out_buffer);
string str_bucket_assemble(string* bucket, int bucket_size, char delim);

//a
