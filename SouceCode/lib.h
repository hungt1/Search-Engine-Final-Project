#include <fcntl.h> 
#include <io.h>    
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <ctime>
using namespace std;
#ifndef _LIB_H_
#define _LIB_H_

struct pack {
    string word;
    double weight;
    pack() {};
    pack(string word, double weight) : word(word), weight(weight) {};
    bool operator < (const pack& other) const {
        return weight > other.weight;
    }
};

#endif