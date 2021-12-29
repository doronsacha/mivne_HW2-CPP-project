#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <iostream>
#include "dynamicArray.h"


template<class T>
class hashTable
        {
private:
    dynamicArray<T>* arr; // mahzik pointer ki bli ze lo mitkampel i think tht better like that also
    int size; // do you want that it will the size of the hash table or the number of element in the hash table?
    int number_of_element;
    T flag;
public:
    hashTable(int length, T tombstone)
    {
        arr = new dynamicArray<T>(length);
        size = arr->getSize();
        number_of_element=arr->getNumber_of_element();
        flag = tombstone;
    }
    ~hashTable()
    {
        delete arr;
    }
    int insert(int id, T data)
    {
        int index_to_insert= hash(id),k=0;
        while((*arr)[index_to_insert]!= return_null<T>()|| (*arr)[index_to_insert] == flag)
        {
            if((*arr)[index_to_insert] != return_null<T>() && (*arr)[index_to_insert]==data)
            {
                return -1;
            }
            index_to_insert=double_hashing(id,k);
            k++;
        }
        arr->set(index_to_insert,data);
        size=arr->getSize();
        number_of_element=arr->getNumber_of_element();
        return 0;
    }

    /*
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
*/
    int double_hashing(int id, int k)
    {
        return ((hash(id) + (k * step_func(id))) % size) ;
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
