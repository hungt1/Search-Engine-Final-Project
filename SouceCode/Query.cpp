#include "lib.h"
#include "SLL.h"
#include "TextNormalizationOperators.h"
#include "PreprocessFIle.h"
#include "QuickSort.h"
using namespace std;

const float eps[] = { 0.01, 0.0075, 0.005 };

extern SLL curList;

bool isAdded(string& path) {
    FILE* index = fopen("Crawl\\index.txt", "r");
    char buffer[1000];
    while (fgets(buffer, 1000, index)) {
        string s = string(buffer);
        if (s[s.length() - 1] == '\n') s.erase(s.length() - 1, 1);
        if (s == path) {
            fclose(index);
            return true;
        }
    }
    fclose(index);
    return false;
}

bool addFile(const wstring path, SLL& curList) {
    FILE* curFile = _wfopen(path.c_str(), L"r,ccs=UTF-8");
    string p = string(path.begin(), path.end());

    if (isAdded(p))
    {
        fclose(curFile);
        return false;
    }

    FILE* index = fopen("Crawl\\index.txt", "a");
    fprintf(index, "%s\n", p.c_str()); fclose(index);
    wstring s = L"";
    while (true) {
        if (feof(curFile)) {
            break;
        }
        s += fgetwc(curFile);
    }
    s.erase(s.size() - 1, 1);
    removeStopwords(s); unsignedDocument(s);
    string t = string(s.begin(), s.end());
    int total = countInitialWords(t);
    string* tmp = new string[total];
    string* words = new string[total * 3];
    wstring x = L""; s += L' ';
    int cur = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == L' ' || s[i] == L'\n') {
            standardized(x);
            if (x.length() != 0 && x.length() < 50) {
                tmp[cur++] = string(x.begin(), x.end());
            }
            x = L"";
        }
        else x += s[i];
    }
    int numWords = 0;
    for (int i = 0; i < cur; i++) {
        words[numWords++] = tmp[i];
        if (i + 1 < cur) {
            words[numWords++] = tmp[i] + " " + tmp[i + 1];
        }
        if (i + 2 < cur) {
            words[numWords++] = tmp[i] + " " + tmp[i + 1] + " " + tmp[i + 2];
        }
    }
    quickSort(words, 0, numWords - 1);
    Node* add = new Node;
    int distincs = countNeedWords(words, numWords, total);
    int cnt = 1; add->nWords = 0; add->path = p;
    add->listWord = new pack[distincs];
    for (int i = 1; i < numWords; i++) {
        if (words[i] == words[i - 1]) cnt++;
        else {
            int len = countInitialWords(words[i - 1]);
            float weight = 1.00 * cnt / total;
            if (weight >= eps[len - 1]) {
                add->listWord[add->nWords++] = pack(words[i - 1], weight);
            }
            cnt = 1;
        }
    }
    int len = countInitialWords(words[numWords - 1]);
    float weight = 1.00 * cnt / total;
    if (weight >= eps[len - 1]) {
        add->listWord[add->nWords++] = pack(words[numWords - 1], weight);
    }
    add->nxt = NULL;
    delete[] tmp, words;
    addData(curList, add);
    fclose(curFile);

    return true;
}


void removeFile(const string path) {
    if (removePath(path, curList)) {

        FILE* index = fopen("Crawl\\index.txt", "w");
        
        Node* cur = curList.head;
        while (cur != NULL) {
            if (cur->path.length() > 4) {
                string prefix = "";
                for (int i = 0; i < min(6,cur->path.size()); i++) prefix += cur->path[i];
                if (prefix != "train\\") {
                    fprintf(index, "%s\n", cur->path.c_str());
                }
            }
            cur = cur->nxt;
        }
        fclose(index);
    }
}

int binSearch(pack* a, int lo, int hi, string &key){
    int pos = -1;
    while (lo <= hi){
        int mi = (lo + hi) / 2;
        if (a[mi].word <= key){
            pos = mi;
            lo = mi + 1;
        }
        else hi = mi - 1;
    }
    if (pos == -1) return pos;
    if (a[pos].word != key) return -1;
    else return pos;
}

void searchData(SLL &curList, wstring s){
    unsignedDocument(s);
    string t = string(s.begin(), s.end());
    int numWords = countInitialWords(t);
    string* words = new string[numWords]; 
    int cntWords = 0;
    wstring curWord = L""; s += L' ';
    for (int i = 0; i < s.length(); i++){
        if (s[i] == L' ' || s[i] == L'\n'){
            standardized(curWord);
            if (curWord.length() != 0 && curWord.length() <= 50){
                words[cntWords++] = string(curWord.begin(), curWord.end());
            }
            curWord = L"";
        }
        else curWord += s[i];
    }

    FILE* ans = fopen("out.txt", "w");
    Node* cur = curList.head;
    while (cur != NULL){
        float totalWeight = 0.00;
        for (int i = 0; i < cntWords; i++){
            string key = words[i];
            int id = binSearch(cur->listWord, 0, cur->nWords - 1, key);
            if (id != -1){
                totalWeight += cur->listWord[id].weight;
            }
        }
        for (int i = 0; i + 1 < cntWords; i++) {
            string key = words[i] + " " + words[i + 1];
            int id = binSearch(cur->listWord, 0, cur->nWords - 1, key);
            if (id != -1) {
                totalWeight += cur->listWord[id].weight * 5;
            }
        }
        for (int i = 0; i + 2 < cntWords; i++) {
            string key = words[i] + " " + words[i + 1] + " " + words[i + 2];
            int id = binSearch(cur->listWord, 0, cur->nWords - 1, key);
            if (id != -1) {
                totalWeight += cur->listWord[id].weight * 10;
            }
        }
        if (totalWeight != 0.0) fprintf(ans, "%s*%f\n", cur->path.c_str(), totalWeight);
        cur = cur->nxt;
    }
    fclose(ans);

}

void loadFileMeta(SLL& cur) {
    FILE* meta = fopen("Crawl\\metadata.txt", "r");
    int n; float weight; char buf[101];
    while (fscanf(meta, "%d", &n)) {
        if (n == -1) break;
        Node* add = new Node;
        char buffer[1000]; // path
        fgetc(meta);  fgets(buffer, 1000, meta);
        string path = string(buffer);
        if (path[path.length() - 1] == '\n') path.erase(path.length() - 1, 1);
        add->nWords = n; add->path = path;
        add->listWord = new pack[n];
        for (int i = 0; i < n; i++) {
            fscanf(meta, "%f", &weight);  fgets(buf, 101, meta);
            string word = string(buf);
            if (word[word.length() - 1] == '\n') word.erase(word.length() - 1, 1);
            word.erase(0, 1);
            add->listWord[i] = pack(word, weight);
        }
        add->nxt = NULL;
        addData(curList, add);
    }

    fclose(meta);
}

void updateMetadata(SLL& curList) {
    FILE* meta = fopen("Crawl\\metadata.txt", "w");
    Node* cur = curList.head;
    while (cur != NULL) {
        fprintf(meta, "%d\n%s\n", cur->nWords, cur->path.c_str());
        for (int i = 0; i < cur->nWords; i++) {
            fprintf(meta, "%f %s\n", cur->listWord[i].weight, cur->listWord[i].word.c_str());
        }
        cur = cur->nxt;
    }
    fprintf(meta, "-1");
    fclose(meta);
}

/*int main()
{
    _setmode(_fileno(stdout), _O_WTEXT);
    InitList(curList);
    loadFileMeta(curList);
    prepare();
    wcout << L"Done !!!";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;    
}*/