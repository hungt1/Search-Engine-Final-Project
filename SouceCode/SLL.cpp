#include "lib.h"
#include "SLL.h"

string magicString(string cur){
    string ans = cur;
    for (int i = 0; i < ans.length(); i++){
        if (ans[i] == '\\' || ans[i] == '/') {
            ans[i] = '_';
        }
        if (ans[i] == ' '){
            ans[i] = '@';
        }
    }
    return ans;
}

Node* createNode(const string path){
    Node* cur = new Node;
    
    string pathMeta = "Crawl\\metadata\\" + magicString(path);
    FILE* fileMeta = fopen(pathMeta.c_str(), "r");
    cur->path = path;
    fscanf(fileMeta, "%d", &cur->nWords);
    cur->listWord = new pack[cur->nWords];
    for (int i = 0; i < cur->nWords; i++){
        char buffer[101]; float w;
        fscanf(fileMeta, "%f", &w); fgets(buffer, 101, fileMeta);
        string s = string(buffer);
        s.erase(0, 1);
        if (s[s.length() - 1] == '\n') s.erase(s.length() - 1, 1);
        cur->listWord[i] = pack(s, w);
    }
    fclose(fileMeta);
    cur->nxt = NULL;

    return cur;
}

void InitList(SLL &curList){
    curList.head = NULL;
    //curList.len = 0;
}

bool isEmpty(SLL &curList){
    return (curList.head == NULL);
}

void addData(SLL& curList, Node*& add) {
    if (isEmpty(curList)) curList.head = add;
    else {
        add->nxt = curList.head;
        curList.head = add;
    }
}

void eraseNode(Node* &cur){
    delete[] cur->listWord;
    delete cur; cur = NULL;
}

void eraseList(SLL& curlist)
{
    Node* cur = curlist.head;
    while (cur != NULL)
    {
        curlist.head = cur->nxt;
        eraseNode(cur);
        cur = curlist.head;
    }
}

bool removePath(const string path, SLL& curList){
    Node* cur = curList.head;
    Node* prev = NULL;
    while (cur != NULL){
        if (cur->path == path){
            if (prev == NULL) {
                curList.head = cur->nxt;
                eraseNode(cur);
            }
            else if (cur->nxt == NULL){
                prev->nxt = NULL;
                eraseNode(cur);
            }
            else {
                prev->nxt = cur->nxt;
                eraseNode(cur);
            }
            return true;
        }
        prev = cur; cur = cur->nxt;
    }
    return false;
}

/*
void printList(SLL &curList){
    Node* cur = curList.head;
    wcout << 1234 << '\n';
    while (cur != NULL){
        wcout << cur->nWords << L'\n';
        for (int i = 0; i < cur->nWords; i++){
            wcout << cur->listWord[i].word << L' ' << cur->listWord[i].weight << L'\n';
        }
        cur = cur->nxt;
    }
}*/