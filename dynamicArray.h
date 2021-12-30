#ifndef HW2MIVNE_DYNAMICARRAY_H
#define HW2MIVNE_DYNAMICARRAY_H

#define POSSIBLE_SIZES 28
#include <iostream>

using namespace  std;
template <class S>
/*
     * this function help to find the default null of the type T
     */
S return_null()
{
    S* nu= new S[1](); // create an array using the default constructor
    S absolut_null=nu[0]; // get the default value of T
    delete []nu;
    return absolut_null;
}

//this dynamic array can have only size of prime numbers
template<class T>
class dynamicArray
{
private:
    T* array;
    int size;
    int prime_possible_sizes[POSSIBLE_SIZES];
    int number_of_element;
public:
    dynamicArray(int length)
    {
        init_prime();
        int current_size = find_upper(length);
        array = new T[current_size](); //initialize all the values to be the null value;
        size =current_size;
        number_of_element = 0;
    }
    //this function find the nearest prime from length in the array of prime numbers
    int find_upper(int i)
    {
        int result=0;
        for(auto element:prime_possible_sizes)
        {
            if (element > i)
            {
                result = element;
                break;
            }
        }
        return result;
    }
    // this function help for initialize the array of prime number of the class
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
    ~dynamicArray()
    {
        delete array;
    };

    /*
     * this function help to find the default null of the type T

    T return_null()
    {
        T* nu= new T[1](); // create an array using the default constructor
        T absolut_null=nu[0]; // get the default value of T
        delete []nu;
        return absolut_null;
    }
    */

    T operator[](int index)
    {
        if(array[index].data == return_null<T>().data)
        {
            return return_null<T>();
        }
        return (*(array+index));
    }

    /*
    dynamicArray(dynamicArray& other)
    {
        delete []arr;
        arr = new T(other.size);
        for(int i=0; i< other.size ; i++)
        {
            arr[i]=other[i];
        }
        size = other.size;
        number_of_element= other.number_of_element;
    };
    */

    void resize()
    {
        int new_size= find_next();
        T* new_arr= new T[new_size]();
        int j=0;
        for(  j ; j<size; j++)
        {
            new_arr[j]=array[j];
        }
        delete []array;
        array= new_arr;
        size=new_size;
    }

    void set(int index, T value , int key)
    {
        if(array[index].data != return_null<T>().data)
        {
            return ; //error to throw
        }
        if((size/2)<number_of_element)
        {
            resize();
        }
        number_of_element++;
        array[index].data = value.data;
        array[index].key= key;
    }

    void remove(int index, T value , int key)
    {
        number_of_element--;
        array[index].data = value.data;
        array[index].key= key;
    }


    int find_next()
    {
        int new_size;
        for (int i=0; i<POSSIBLE_SIZES ; i++)
        {
            if(prime_possible_sizes[i]==size)
            {
                new_size= prime_possible_sizes[i+1];
                break;
            }
        }
        return new_size;
    }
    int getSize()
    {
        return size;
    }
    int getNumber_of_element()
    {
        return number_of_element;
    }
    void remove_element()
    {
        number_of_element--;
    }
    T* get_the_array()
    {
        return array;
    }
};

#endif //HW2MIVNE_DYNAMICARRAY_H