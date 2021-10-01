#pragma once

#include "lib.h"
using namespace std;

int countNeedWords(string*& cur, int n, int numWords);
int countInitialWords(string& s);
void removeStopwords(wstring& s);
void unsignedDocument(wstring& s);
bool isTrash(wchar_t c);
void standardized(wstring& word);