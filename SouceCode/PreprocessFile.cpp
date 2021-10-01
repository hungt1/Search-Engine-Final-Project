#include "preprocessFile.h"
using namespace std;

const int _a[] = {97, 224, 225, 7843, 227, 7841, 259, 7857, 7855, 7859, 7861, 7863, 226, 7847, 7845, 7849, 7851, 7853, 192, 193, 7842, 195, 7840, 258, 7856, 7854, 7858, 7860, 7862, 194, 7846, 7844, 7848, 7850, 7852};
const int _d[] = {100, 273, 272};
const int _e[] = {101, 232, 233, 7867, 7869, 7865, 234, 7873, 7871, 7875, 7877, 7879, 200, 201, 7866, 7868, 7864, 202, 7872, 7870, 7874, 7876, 7878};
const int _i[] = {105, 236, 237, 7881, 297, 7883, 204, 205, 7880, 296, 7882};
const int _o[] = {111, 242, 243, 7887, 245, 7885, 244, 7891, 7889, 7893, 7895, 7897, 417, 7901, 7899, 7903, 7905, 7907, 210, 211, 7886, 213, 7884, 212, 7890, 7888, 7892, 7894, 7896, 416, 7900, 7898, 7902, 7904, 7906};
const int _u[] = {117, 249, 250, 7911, 361, 7909, 432, 7915, 7913, 7917, 7919, 7921, 217, 218, 7910, 360, 7908, 431, 7914, 7912, 7916, 7918, 7920};
const int _y[] = {121, 7923, 253, 7927, 7929, 7925, 7922, 221, 7926, 7928, 7924};
extern int convert[1 << 16];
extern wstring discards[1942];
extern int nStopwords;

void prepare(){
    FILE* f = _wfopen(L"stopwords.txt", L"r,ccs=UTF-8");
    wchar_t buffer[40];
    for (int i = 0; i < nStopwords; i++){
        fgetws(buffer, 40, f);
        discards[i] = wstring(buffer);
        int len = discards[i].length();
        if (discards[i][len - 1] == L'\n'){
            discards[i].erase(len - 1, 1);
        }
    }
    for (int i = 0; i < (1 << 16); i++) convert[i] = -1;
    for (int i = 1; i < 35; i++) convert[_a[i]] = _a[0];
    for (int i = 1; i < 3; i++) convert[_d[i]] = _d[0];
    for (int i = 1; i < 23; i++) convert[_e[i]] = _e[0];
    for (int i = 1; i < 11; i++) convert[_i[i]] = _i[0];
    for (int i = 1; i < 35; i++) convert[_o[i]] = _o[0];
    for (int i = 1; i < 23; i++) convert[_u[i]] = _u[0];
    for (int i = 1; i < 11; i++) convert[_y[i]] = _y[0];
    fclose(f);  
}

bool checkExtension(const wstring cur, const wstring chk){
    if (cur.find(chk) != -1) return true;
    return false;
}