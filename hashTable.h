#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <iostream>
#include "dynamicArray.h"

template<class T>
class hashTable
        {
private:
    struct M
    {
        T data;
        int key;
    };
    dynamicArray<M>* arr; // mahzik pointer ki bli ze lo mitkampel i think tht better like that also
    int size; // do you want that it will the size of the hash table or the number of element in the hash table?
    int number_of_element;
    T tombstone;
    int number_of_tombstone;
public:
    hashTable(int length, T tomb)
    {
        arr = new dynamicArray<M>(length);
        size = arr->getSize();
        number_of_element=0;
        tombstone = tomb;
        number_of_tombstone=0;
    }
    ~hashTable()
    {
        delete arr;
    }
    int insert_position(int id, M data,dynamicArray<M>* array )
    {
        int index_to_insert= hash(id),k=0;
        while((*array)[index_to_insert].data!= return_null<T>()|| (*array)[index_to_insert].data == tombstone)
        {
            if((*array)[index_to_insert].data != return_null<T>() && (*array)[index_to_insert].data==data.data)
            {
                return -1;
            }
            index_to_insert=double_hashing(id,k);
            k++;
        }
        return index_to_insert;
    }
    int insert(int id, M data)
    {
        int index_to_insert= insert_position(id,data,arr);
        arr->set(index_to_insert,data,id);
        size=arr->getSize();
        number_of_element++;
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
    void clean_tombstone()
    {
        dynamicArray<M>* new_arr=new dynamicArray<M>(number_of_element);
        for (int i=0; i<size; i++)
        {
            if((*arr)[i].data == return_null<M>().data)
            {
                continue;
            }
            if((*arr)[i].data != tombstone || (*arr)[i].data != return_null<M>().data)
            {
                int index_to_insert= insert_position((*arr)[i].key, (*arr)[i],new_arr);
                new_arr->set(index_to_insert,(*arr)[i],(*arr)[i].key);
                //delete (*arr)[i];
            }
        }
        delete arr;
        arr=new_arr;
        size=arr->getSize();
        number_of_element=arr->getNumber_of_element();
    }

    void remove(int id)
    {
        int index_to_remove= hash(id),k=1;
        while((*arr)[index_to_remove].key != id)
        {
            index_to_remove=double_hashing(id,k);
            k++;
        }
        arr->remove(index_to_remove,{tombstone, id},-1);
        number_of_tombstone++;
        number_of_element--;
        if(number_of_tombstone > size/10)//TODO: check what is the number
        {
            clean_tombstone();
        }
    }
};

#endif //HASH_TABLE_H
