#include "lib.h"
using namespace std;

#ifndef _SLL_H_
#define _SLL_H_

struct Node {
    string path;
    int nWords;
    pack* listWord;  
    Node* nxt;
};

struct SLL {
    Node* head;
}; 

string magicString(string cur);
Node* createNode(const string path);
void InitList(SLL &curList);
bool isEmpty(SLL &curList);
void addData(SLL& curList, Node*& add);
void eraseNode(Node* &cur);
void eraseList(SLL& curlist);
bool removePath(const string path, SLL &curList);


#endif