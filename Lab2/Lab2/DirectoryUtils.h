#pragma once
#include "../../aquaUtils/StringUtils.h"
#include "../../aquaUtils/DebugUtils.h"
#include "../../aquaUtils/AquaTypes.h"
#include <stdio.h>
#include <Windows.h>
#include <wchar.h>

string_t getPathInDirectory(string_t dir_name, string_t file);
string_t getDirectoryPath(string_t dir_name);
string_t getFilenameFromPath(string_t path);

void getFilesInDirectory(const wchar_t* dir_name, StringV* out);
const wchar_t* wideFromMultibyte(string_t str);