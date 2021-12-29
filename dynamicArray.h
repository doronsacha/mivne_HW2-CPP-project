#ifndef HW2MIVNE_DYNAMICARRAY_H
#define HW2MIVNE_DYNAMICARRAY_H

#include <iostream>
using namespace  std;

template<class T>
class dynamicArray
{
private:
    T* arr;
    int size;
    int number_of_element;
    T null_element;// the default null element
public:
    dynamicArray(int i, T default_null)
    {
        if(i<=0)
        {
            cout << "cannot create an empty or negative input";
            exit(0);
        }
        arr = new T[i](); //initialize all the values to be the null value;
        size = i ;
        number_of_element=0;
        null_element = default_null;
    };

    ~dynamicArray()
    {
        delete []arr;
        size = 0;
        number_of_element=0;
    };


    T& operator[](int index)
    {
        if(index > size)
        {
            cout << " Array index out of bound !!!";
            exit(0);
        }
        if(arr[index] == null_element)
        {
            return null_element;
        }
        return *(arr+index);
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
    void push(T insert)
    {
        if((size/2)<number_of_element)
        {
            resize();
        }
        arr[number_of_element] = insert;
        number_of_element++;
    }
    void resize()
    {
        T* new_arr= new T[size*2]();
        for(int i=0; i<size; i++)
        {
            new_arr[i]=arr[i];
        }
        delete []arr;
        arr= new_arr;
        size=size*2;
    }

    void set(int index, T value)
    {
        if(arr[index] != null_element)
        {
            return ;
        }
        if((size/2)<number_of_element)
        {
            resize();
        }
        number_of_element++;
        arr[index] = value;
    }
};

#endif //HW2MIVNE_DYNAMICARRAY_H