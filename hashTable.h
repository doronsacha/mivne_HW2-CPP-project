#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <iostream>
#include "dynamicArray.h"


template<class T>
class hashTable {
private:
    dynamicArray<T> arr;
    int size;
    T default_null;
    T flag;
public:
    hashTable(int len,T def_null, T flag)
    {
        arr = dynamicArray<T>(len,def_null);
        size = arr.getSize();
        default_null = def_null;
        flag = flag;
    }

    int insert(int id, T &data)
    {
        int index = find(id,data);
        if (index != -1)
            return -1;
        index = hash(id);
        int k=0;
        while(arr[index] != default_null || arr[index] == flag )
        {
            index = double_hashing(id,k);
            k++;
        }
        arr[index] = data;
    }

    int find(int id, T& element)
    {
        int index = hash(id);
        int k =0;
        while(arr[index] != element)
        {
            index = double_hashing(id,k);
            k++;
            if(arr[index] == default_null)
            {
                return -1;
            }
        }
        return index;
    }

    int double_hashing(int id, int k)
    {
        return ((hash(id, size) + (k * step_func(id,size))) % size) ;
    }
    int hash(int id)
    {
        return id % size;
    }
    int step_func(int id)
    {
        return 1 + (id % (size-2));
    }

};


#endif //HASH_TABLE_H
