#include "QuickSort.h"

template<class T> void Swap(T &a, T& b){
    T tmp = a; a = b; b = tmp;
}

template<class T> int myPartition(T arr[], int lo, int hi){
    T key = arr[hi];
    int p = lo - 1;
    for (int i = lo; i < hi; i++){
        if (arr[i] < key){
            p++;
            Swap(arr[i], arr[p]);
        }
    }
    Swap(arr[p + 1], arr[hi]);
    return (p + 1);
}

void quickSort(string* arr, int lo, int hi){
    if (lo < hi){
        int pos = myPartition(arr, lo, hi);
        quickSort(arr, lo, pos - 1); 
        quickSort(arr, pos + 1, hi);
    }
}


void quickSort(pack* arr, int lo, int hi) {
    if (lo < hi) {
        int pos = myPartition(arr, lo, hi);
        quickSort(arr, lo, pos - 1);
        quickSort(arr, pos + 1, hi);
    }
}
