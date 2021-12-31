#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H
#define POSSIBLE_SIZES 28
#include <iostream>
#define NOT_FOUND -1

template<class T>
class HashTable
{
private:
    int size;
    int number_of_elements;
    int number_of_tombstones;
    T tombstone;
    int prime_possible_sizes[POSSIBLE_SIZES];
    T* arr;
public:
    HashTable(T tomb)
    {
        init_prime();
        size = prime_possible_sizes[0];
        arr = new T[size]();
        number_of_elements=0;
        number_of_tombstones=0;
        tombstone=tomb;
    }

    HashTable(int length, T tomb): size(length), number_of_elements(0), number_of_tombstones(0), tombstone(tomb)
    {
        init_prime();
        size = find_upper(length);
        arr = new T[size];
    }
    ~HashTable()
    {
        delete []arr;
    }
    T& operator [](int idx)
    {
        return arr[idx];
    }

//***********************************************************************************************************************
//----------------------------------------------Operations---------------------------------------------------------------
//***********************************************************************************************************************

    void insert(int id, T data)
    {
        int index = find_index_to_insert(id);
        if(arr[index] == tombstone)
        {
            number_of_tombstones--;
        }
        arr[index] = data;
        number_of_elements++;
        fixing_sizes();
    }

    int find(int id)
    {
        int index = hash(id), k=1;
        while(arr[index] != nullptr && arr[index]->getID() != id )
        {
            index = double_hashing(id,k);
            k++;
        }
        if(arr[index] == nullptr)
            return NOT_FOUND;
        else
            return index;
    }

    void remove(int id)
    {
        int index = find(id);
        if (index == -1)
            return;
        else
        {
            arr[index] = tombstone;
            number_of_tombstones++;
            number_of_elements--;
        }
        fixing_sizes();
    }



//**********************************************************************************************************************
//----------------------------------------------Hashing-----------------------------------------------------------------
//**********************************************************************************************************************

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

    int find_index_to_insert(int id)
    {
        int index = hash(id);
        int k=1;
        while(arr[index] != nullptr && arr[index] != tombstone)
        {
            index = double_hashing(id,k);
            k++;
        }
        return index;
    }

//**********************************************************************************************************************
//----------------------------------------------Size Management---------------------------------------------------------
//**********************************************************************************************************************

    void fixing_sizes()
    {
        if(number_of_elements > size/2)
            resize_up();
        if(number_of_elements < size/4 && size > prime_possible_sizes[0])
            resize_down();
    }

    void resize_up()
    {
        T temp_array[number_of_elements];
        for(int i=0,j=0; i<size; ++i)
        {
            if(arr[i] != tombstone && arr[i] != nullptr)
            {
                temp_array[j] = arr[i];
                j++;
            }
        }
        delete []arr;
        size = find_upper(size);
        arr = new T[size]();
        int correct_num_of_elements = number_of_elements;
        for(int i=0; i< correct_num_of_elements; i++)
        {
            int index = find_index_to_insert(temp_array[i]->getID());
            if(arr[index] == tombstone)
                number_of_tombstones--;
            arr[index] = temp_array[i];
        }
        number_of_tombstones = 0;
    }

    void resize_down()
    {
        T temp_array[number_of_elements];
        for(int i=0,j=0; i<size; ++i)
        {
            if(arr[i] != tombstone && arr[i] != nullptr)
            {
                temp_array[j] = arr[i];
                j++;
            }
        }
        delete []arr;
        size = find_lower(size);
        arr = new T[size]();
        int correct_num_of_elements = number_of_elements;
        for(int i=0; i< correct_num_of_elements; i++)
        {
            int index = find_index_to_insert(temp_array[i]->getID());
            if(arr[index] == tombstone)
                number_of_tombstones--;
            arr[index] = temp_array[i];
        }
        number_of_tombstones =0;
    }

//**********************************************************************************************************************
//----------------------------------------------Prime numbers-----------------------------------------------------------
//**********************************************************************************************************************

    void init_prime()
    {
        int prime[POSSIBLE_SIZES]={13,29,53,97,193,389,769,1543,
                                   3079,6151,12289,24593,49157,98317,
                                   196613,393241,786433,1572869,3145739,6291469,
                                   12582917,25165843,50331653,100663319,
                                   201326611,402653189,805306457,1610612741};
        for(int i=0;i<POSSIBLE_SIZES;i++)
        {
            prime_possible_sizes[i]=prime[i];
        }
    }

    int find_upper(int current)
    {
        int result=0;
        for(auto element:prime_possible_sizes)
        {
            if (element > current)
            {
                result = element;
                break;
            }
        }
        return result;
    }

    int find_lower(int current)
    {
        int result=0;
        for(int i=POSSIBLE_SIZES-1; i>0; --i)
        {
            if (prime_possible_sizes[i] < current)
            {
                return prime_possible_sizes[i];
            }
        }
        return 13;
    }

};

#endif //WET2_HASHTABLE_H
