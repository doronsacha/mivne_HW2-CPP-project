//
// Created by tsahiedri on 28/12/2021.
//

#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <iostream>
#include "dynamicArray.h"

template<class T>
class hashTable {
private:
    dynamicArray<T> arr;
    int size;
public:
    hashTable(int size, )
    int double_hashing(int id, int size, int k)
    {
        return ((hash(id, size) + (k * step_func(id,size))) % size) ;
    }
    int hash(int id,int size)
    {
        return id % size;
    }
    int step_func(int id, int size)
    {
        return 1+ (id % (size-2));
    }
};


#endif //HASH_TABLE_H
