#include "AquaDBMS.h"
#include <time.h>
#include <limits.h>
#include <windows.h>
#include "..\aquaUtils\FileUtils.h"
#include "ExtendedUtils.h"
#include "AquaCrypto.h"
#include <io.h>

#define fileExists(s) AQUADB_Private_FileExists(s)
#define invalid() panic("AquaDatabase :: Invalid database file");

#define CORRUPTED_DB "AquaDatabase :: Invalid!\nThrere was an attempt to overwrite the data OR was accidentally corrupted!"

void InitAquaDatabase(AquaDatabase* db, const char* db_dir) {
    db->putObject = AQUADB_Default_putObject;
    db->OpenOrCreate = AQUADB_Default_OpenOrCreate;
    db->find = AQUADB_Default_find;
    db->set = AQUADB_Default_set;
    db->_close = AQUADB_Default_Close;
    db->db_dir = db_dir;
    db->current_db = 0;
    db->handleToRead = 0;
    db->handleToWrite = 0;
    db->signFile = 0;
    db->tables_c = 0;
    db->tables = initArray(0, sizeof(Table));
    db->__notnull__ = 1;
}
  
/*
Warning: This verion only for Windows
Warning: Todo: should also check for signature file
*/
void AQUADB_Default_OpenOrCreate(__AquaDBSelf__, string name) {

    if (self->db_dir == 0) {
        panic("AquaDatabase :: [db_dir] NullPointerException");
        return;
    }
    if (fileExists(self->db_dir)) {
        printf(self->db_dir);
        int r = CreateDirectoryW(self->db_dir, NULL);
        if (r == 0) {
            perror("AquaDatabase[I/O] :: ");
            panic("AquaDatabase :: can't create db_dir");
        }
    }
    StringBuilder sb;
    InitStringBuilder(&sb, self->db_dir);
    sb.add(&sb, "\\")->add(&sb, name);
    string path = SUS_str_copy(sb.build(&sb));
    string shadow_path = sb.add(&sb,"x")->build(&sb);
    string sign_path = sb.add(&sb,"sign")->buildAndDispose(&sb);
    sb.add(&sb, "copy ")->add(&sb, path)->add(&sb, " ")->add(&sb, shadow_path);
    system(sb.buildAndDispose(&sb));
    int s = 0;
    s = fopen_s(&self->handleToWrite, path, "a");
    handleIOError(s, "AquaDatabase[O] :: ");
    string shadow_sign = "__init__";
    if (SIGN_CREATE) {
        FILE* signTemp;
        s = fopen_s(&signTemp, sign_path, "r");
        handleIOError(s, "AquaDatabase[Sign] :: ");
        char buffer[512];
        if (fgets(buffer, 512, signTemp) == 0) {
            invalid();
        }
        shadow_sign = SUS_str_copy(buffer);
        fclose(signTemp);
    }
    s = fopen_s(&self->signFile, sign_path, "a");
    handleIOError(s, "AquaDatabase[Sign] :: ");
    s = fopen_s(&self->handleToRead, shadow_path, "r");
    handleIOError(s, "AquaDatabase[I] :: ");
    self->current_db = name;
    self->shadow_path = shadow_path;
    self->current_path = path;
    AQUADB_Private_ScanForTables(self);
    if (SIGN_NEEDED & SIGN_CREATE) {
        string sign = AQUADB_Private_Sign(self, 0);
        printf("\n%s\n%s\n", sign, shadow_sign);
        if (strcmp(sign, shadow_sign) != 0) panic(CORRUPTED_DB);
    }    
    system("cls");
}

void AQUADB_Default_putObject(__AquaDBSelf__, string table, DataBox* dataBox) {

    if (self->current_db == 0 || self->handleToWrite == 0)
        panic("AquaDatabase :: [current_db] NullPointerException");
    int s = 0;
    int table_n = 0;
    for (int i = 0; i < self->tables_c; i++) {
        s = (strcmp(table, (self->tables)[i].tname) == 0);
        if (s == 1) {
            table_n = i;
            break;
        }
    }
    if (s == 0) panic("AquaDatabase :: table don't exists");
    StringBuilder sb;
    StringBuilder* sbp = &sb;
    InitStringBuilder(sbp, "obj=true");
    for (int i = 0; i < dataBox->kv.size; i++) {
        sbp //
            ->add(sbp, ";")
            ->add(sbp, dataBox->kv.ptr[i])
            ->add(sbp, "=")
            ->add(sbp, dataBox->vv.ptr[i]);
    }
    sbp->add(sbp, "\n");
    AQUADB_Private_Insert(self, sbp->buildAndDispose(sbp), &self->tables[table_n]);
}

/*
@return (> 0) - found, (-0x404) - not found
*/
errno_t AQUADB_Default_find(__AquaDBSelf__, string table, string key, string value, HashMap* out) {
    rewind(self->handleToRead);
    rewind(self->handleToWrite);
    StringBuilder sv; InitStringBuilder(&sv, key);
    sv.add(&sv, "=")->add(&sv, value);
    string pair = sv.buildAndDispose(&sv);
    int s = 0;
    int table_n = 0;
    for (int i = 0; i < self->tables_c; i++) {
        s = (strcmp(table, (self->tables)[i].tname) == 0);
        if (s == 1) {
            table_n = i;
            break;
        }
    }
    if (s == 0) panic("AquaDatabase :: table don't exists");

    int status = STATUS_SUCCESS;
    if (self->handleToRead == 0) return ERROR_CANT_READ;
    s = 1;
    int search = 1;
    int line_n = -1;
    while (s != 0) {
        char* buffer = initArray(2048, 1);
        s = fgets(buffer, 2048, self->handleToRead);
        if (ferror(self->handleToRead) != 0) {
            _fcloseall();
            perror("I/O");
            panic("[!panic]");
        }
        line_n++;
        if (line_n <= self->tables[table_n].start) {
            free(buffer);
            continue;
        }
        if (s == 0) break;
        string line_str = buildLine(buffer, 2048);
        if (strcmp(line_str, "end") == 0) break;
        StringV sv;
        InitStringV(&sv);
        sv.ptr = SUS_split(line_str, ';', &sv.size);
        for (int j = 0; j < sv.size; j++) {
            StringVP pair = NewStringV();
            pair->ptr = SUS_split(sv.ptr[j], '=', &pair->size);
            if (pair->size != 2) invalid();
            search *= (strcmp(pair->ptr[0], key) || strcmp(pair->ptr[1], value));
            out->put(out, pair->ptr[0], pair->ptr[1]);
        }
        if (search == 0) return line_n;
        sv.clear(&sv);
        free(line_str);
    }
    handleIOError(status, "Input file: ");
    return -0x404;
}

void AQUADB_Default_set(__AquaDBSelf__, int p, DataBox* dataBox)
{
    if (self->current_db == 0 || self->handleToWrite == 0)
        panic("AquaDatabase :: [current_db] NullPointerException");

    StringBuilder sb;
    StringBuilder* sbp = &sb;
    InitStringBuilder(sbp, "obj=true");
    for (int i = 0; i < dataBox->kv.size; i++) {
        sbp //
            ->add(sbp, ";")
            ->add(sbp, dataBox->kv.ptr[i])
            ->add(sbp, "=")
            ->add(sbp, dataBox->vv.ptr[i]);
    }
    sbp->add(sbp, "\n");
    AQUADB_Private_Replace(self, sbp->buildAndDispose(sbp), p);
}

void AQUADB_Default_Close(__AquaDBSelf__) {
    _fcloseall();
    remove(self->shadow_path);
    self->handleToWrite = 0;
    self->handleToRead = 0;
    self->current_db = 0;
}

int AQUADB_Private_FileExists(LPCWSTR dir)
{
    DWORD dwAttrib = GetFileAttributes(dir);

    return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
        (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

int AQUADB_Private_ScanForTables(__AquaDBSelf__) {
    int status = STATUS_SUCCESS;
    if (self->handleToRead == 0) return ERROR_CANT_READ;
    int s = 1;
    int line_n = 0;
    int table = 0;
    while (s != 0) {
        char* buffer = initArray(2048, 1);
        s = fgets(buffer, 2048, self->handleToRead);
        if (ferror(self->handleToRead) != 0) {
            _fcloseall();
            perror("I/O");
            panic("[!panic]");
        }
        if (s == 0) break;
        string line_str = buildLine(buffer, 2048);
        if (strstr(line_str, "table") != 0) {
            StringV sv; InitStringV(&sv);
            sv.ptr = SUS_split(line_str, ':', &sv.size);
            if (sv.size != 2) invalid();
            string tmp0 = sv.ptr[1];
            self->tables_c++;
            Table* tmp = (Table*)realloc(self->tables, sizeof(Table) * self->tables_c);
            if (tmp == NULL) { panic("Memory allocation error!"); return; }
            self->tables = (Table*)tmp;
            (self->tables)[table].tname = tmp0;
            self->tables->start = line_n;
        }
        else {
            if (line_n == 0) invalid();
        }
        if (strstr(line_str, "end") != 0) {
            self->tables[table].end = line_n;
            table++;
        }
        free(line_str);
        line_n++;
    }
    handleIOError(status, "Input file: ");
    return 0;
}

void AQUADB_Private_Insert(__AquaDBSelf__, string line, Table* table) {
    int status = STATUS_SUCCESS;
    int eax = _chsize(_fileno(self->handleToWrite), 0);
    fseek(self->handleToRead, 0, 0);
    fseek(self->handleToWrite, 0, 0);
    if (self->handleToRead == 0) return ERROR_CANT_READ;
    if (self->handleToWrite == 0) return ERROR_CANT_WRITE;
    int s = 1;
    int line_n = 0;
    int table_n = 0;
    while (s != 0) {
        char* buffer = initArray(2048, 1);
        s = fgets(buffer, 2048, self->handleToRead);
        if (ferror(self->handleToRead) != 0) {
            _fcloseall();
            perror("I/O");
            panic("[!panic]");
        }
        if (line_n == table->end) {
            fputs(line, self->handleToWrite);
            fputs("end\n", self->handleToWrite);
        }
        else {
            fputs(buffer, self->handleToWrite);
        }
        free(buffer);
        line_n++;
    }
    handleIOError(status, "Input file: ");
    if (SIGN_NEEDED) AQUADB_Private_Sign(self, 1);
    AQUADB_Private_Rewind(self);
    return 0;
}

void AQUADB_Private_Replace(__AquaDBSelf__, string line, int pointer)
{
    int status = STATUS_SUCCESS;
    int eax = _chsize(_fileno(self->handleToWrite), 0);
    fseek(self->handleToRead, 0, 0);
    fseek(self->handleToWrite, 0, 0);
    if (self->handleToRead == 0) return ERROR_CANT_READ;
    if (self->handleToWrite == 0) return ERROR_CANT_WRITE;
    int s = 1;
    int line_n = 0;
    int table_n = 0;
    while (s != 0) {
        char* buffer = initArray(2048, 1);
        s = fgets(buffer, 2048, self->handleToRead);
        if (ferror(self->handleToRead) != 0) {
            _fcloseall();
            perror("I/O");
            panic("[!panic]");
        }
        if (line_n == pointer) {
            fputs(line, self->handleToWrite);
        }
        else {
            fputs(buffer, self->handleToWrite);
        }
        free(buffer);
        line_n++;
    }
    handleIOError(status, "Input file: ");
    if(SIGN_NEEDED) AQUADB_Private_Sign(self, 1);
    AQUADB_Private_Rewind(self);
    return 0;
}

string AQUADB_Private_Sign(__AquaDBSelf__, BOOL replace_mode) {

    if (self->handleToRead == 0) panic("AquaDBMS.Sign() :: handleToRead == 0!");
    if (self->signFile == 0) panic("AquaDBMS.Sign() :: signFile == 0!");
    fseek(self->handleToRead, 0, 0);
    int eax;
    if (replace_mode) {
        eax = _chsize(_fileno(self->signFile), 0);
    }
    int s = 1;
    LongV lv; InitLongV(&lv);
    while (s != 0) {
        char* buffer = initArray(2048, 1);
        s = fgets(buffer, 2048, self->handleToRead);
        int i = 0;
        __int64 h0 = 0x8888888888888888;
        string line = buildLine(buffer, 2048);
        while ((line[i] != '\0')&&(i < 2048)) {
            h0 = h0 ^ ((__int64) line[i] << (i % 64));
            i++;
        }
        lv.put(&lv, h0 ^ i);
    }
    __int64 lasthope = 0x12341234;
    for (int i = 0; i < lv.size; i++) {
        lasthope ^= lv.ptr[i];
    }
    char i1[20];
    for (int i = 0; i < 20; i++) i1[i] = '*';
    _i64toa_s(lasthope, i1, 20, 16);
    string sign = hashString(i1);
    if (replace_mode) {
        fputs(sign, self->signFile);
        fputs("\n", self->signFile);
    }
    return sign;
}

void AQUADB_Private_Rewind(__AquaDBSelf__) {
    _fcloseall();
    StringBuilder sb;
    InitStringBuilder(&sb, "copy ");
    sb.add(&sb, self->current_path)->add(&sb, " ")->add(&sb, self->shadow_path);
    system(sb.buildAndDispose(&sb));
    int s = 0;
    s = fopen_s(&self->handleToWrite, self->current_path, "a");
    handleIOError(s, "AquaDatabase[O] :: ");
    s = fopen_s(&self->handleToRead, self->shadow_path, "r");
    handleIOError(s, "AquaDatabase[I] :: ");
    system("cls");
}