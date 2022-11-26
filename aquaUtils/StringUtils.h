#pragma once
#define string_t const char*
#define CharList char*

#define F_Scan128 "%128[^\n\r]"
#define F_Scan512 "%512[^\n\r]"
#define F_Scan1024 "%1024[^\n\r]"

// UTILS

string_t SUS_clearDublicateSpaces(string_t str);
int SUS_getStringLength(string_t str);
int SUS_parseInteger32(string_t str, __int32* out);
int SUS_isStringNumber(string_t str);
string_t SUS_str_copy(string_t str1);

/*@return 1 - if [str] goes earlier [next] in (ASCII) comparison*/
char SUS_alphabetCompare(string_t str, string_t next);

// UTILS + STRING_BUILDER HELPERS

string_t SUS_trim(string_t str);
string_t* SUS_split(string_t, char delimiter, int* parts_count);
string_t SUS_str_c(string_t str1, string_t str2);
string_t SUS_str_f(string_t format, string_t str2);
string_t SUS_format1024(string_t format, ...);
void SUS_str_unlock(string_t const_str, int* out_len, CharList* out_buffer);
string_t SUS_str_lock(char* buffer, int size);
string_t SUS_str_bucket_assemble(string_t* bucket, int bucket_size, char delim);

