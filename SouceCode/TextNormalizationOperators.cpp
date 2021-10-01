#include "textNormalizationOperators.h"
using namespace std;

extern int nStopwords;
extern wstring discards[1942];
extern int convert[1 << 16];
extern wstring stupidChar;

const float eps[] = { 0.01, 0.0075, 0.005 };

int countNeedWords(string*& cur, int n, int total) {
    if (n == 0) return 0;
    int cnt = 1, ans = 0;
    for (int i = 1; i < n; i++) {
        if (cur[i] == cur[i - 1]) cnt++;
        else {
            int len = countInitialWords(cur[i - 1]);
            float weight = 1.00 * cnt / total;
            if (weight >= eps[len - 1]) ans++;
            cnt = 1;
        }
    }
    int len = countInitialWords(cur[n - 1]);
    float weight = 1.00 * cnt / total;
    if (weight >= eps[len - 1]) ans++;
    return ans;
}

int countInitialWords(string& s) {
    int ans = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ' || s[i] == '\n') ans++;
    }
    return ans + 1;
}

void removeStopwords(wstring& s) {
    for (int i = 0; i < nStopwords; i++) {
        while (true) {
            int pos = s.find(L" " + discards[i] + L" ");
            if (pos != -1) {
                s.erase(pos, discards[i].length() + 1);
            }
            else break;
        }
    }
}

void unsignedDocument(wstring& s) {
    for (int i = 0; i < s.length(); i++) {
        if (convert[s[i]] != -1) {
            s[i] = convert[s[i]];
        }
        if (L'A' <= s[i] && s[i] <= L'Z') {
            s[i] = (s[i] - L'A' + L'a');
        }
    }
}

bool isTrash(wchar_t c) {
    for (int i = 0; i < stupidChar.length(); i++) {
        if (c == stupidChar[i]) return true;
    }
    return false;
}

void standardized(wstring& word) {
    while (word.length() && isTrash(word[0])) {
        word.erase(0, 1);
    }
    while (word.length() && isTrash(word[word.length() - 1])) {
        word.erase(word.length() - 1, 1);
    }
}

