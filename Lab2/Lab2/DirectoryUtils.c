#include "DirectoryUtils.h"

string_t getPathInDirectory(string_t dir_name, string_t file)
{

	char cwd[512];
	if (getcwd(cwd, sizeof(cwd)) != 0) {
		return SUS_format1024("%s\\%s\\%s", cwd, dir_name, file);
	}
	else {
		return panic_e("Current directory path > 512");
	}

}

string_t getDirectoryPath(string_t dir_name)
{
    char cwd[512];
    if (getcwd(cwd, sizeof(cwd)) != 0) {
        return SUS_format1024("%s\\%s", cwd, dir_name);
    }
    else {
        return panic_e("Current directory path > 512");
    }
}

string_t getFilenameFromPath(string_t path)
{
    StringV sv; InitStringV(&sv);
    sv.ptr = SUS_split(path, '\\', &sv.size);
    string_t filename = SUS_str_copy(sv.ptr[sv.size - 1]);
    sv.clear(&sv);
    return filename;
}

void getFilesInDirectory(const wchar_t* dir_name, StringV* out)
{


    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;

    wchar_t sPath[2048];

    //Specify a file mask. *.* = We want everything! 
    wsprintf(sPath, L"%s\\*.*", dir_name);

    if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
    {
        printf("{%ws}\n", dir_name);
        panic("Path not found");
        return;
    }  
    if (out->__notnull__ == 0) panic_NPE();
    do
    {
        //Find first file will always return "."
        //    and ".." as the first two directories. 
        if (wcscmp(fdFile.cFileName, L".") != 0
            && wcscmp(fdFile.cFileName, L"..") != 0)
        {
            //Build up our file path using the passed in 
            //  [sDir] and the file/foldername we just found: 
            wsprintf(sPath, L"%s\\%s", dir_name, fdFile.cFileName);

            //Is the entity a File or Folder? 
            if (fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
            }
            else {
                string_t path = SUS_format1024("%ws", sPath);
                out->put(out, path);
            }
        }
    } while (FindNextFile(hFind, &fdFile)); //Find the next file. 

    FindClose(hFind); //Always, Always, clean things up! 
}

const wchar_t* wideFromMultibyte(string_t str)
{
    wchar_t wcs[1024];
    size_t length = 0;    
    mbsrtowcs_s(&length, wcs, 1024, &str, 1024, NULL);
    wcs[length] = L'\0';
    return wcs;
}
