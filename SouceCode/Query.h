#ifndef Query_h
#define Query_h

#include "SLL.h"

void loadFileMeta(SLL& cur);
void searchData(SLL& curList, wstring s);
int binSearch(pack* a, int lo, int hi, string& key);
void removeFile(const string path);
bool addFile(const wstring path, SLL& curList);
void updateMetadata(SLL& curList);

#endif