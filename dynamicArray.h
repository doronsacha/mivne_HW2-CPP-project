#ifndef HW2MIVNE_DYNAMICARRAY_H
#define HW2MIVNE_DYNAMICARRAY_H

#define POSSIBLE_SIZES 28
#include <iostream>
using namespace  std;

template<class T>
class dynamicArray
{
private:
    T* arr;
    int size;
    int possible_sizes[POSSIBLE_SIZES];
    int number_of_element;
    T null_element;// the default null element
public:
    dynamicArray(int i, T default_null)
    {
        if (i <= 0) {
            cout << "cannot create an empty or negative input";
            exit(0);
        }
        init_prime();
        int currect_size = find_upper(i);
        arr = new T[currect_size](); //initialize all the values to be the null value;
        size =currect_size;
        number_of_element = 0;
        null_element = default_null;
    }
    int find_upper(int i)
    {
        int res;
        for(auto el:possible_sizes)
        {
            if (el > i)
            {
                res =el;
                break;
            }
        }
        return res;
    }
    void init_prime()
    {
        possible_sizes[0]=13;
        possible_sizes[1]=29;
        possible_sizes[2]=53;
        possible_sizes[3]=97;
        possible_sizes[4]=193;
        possible_sizes[5]=389;
        possible_sizes[6]=769;
        possible_sizes[7]=1543;
        possible_sizes[8]=3079;
        possible_sizes[9]=6151;
        possible_sizes[10]=12289;
        possible_sizes[11]=24593;
        possible_sizes[12]=49157;
        possible_sizes[13]=98317;
        possible_sizes[14]=196613;
        possible_sizes[15]=393241;
        possible_sizes[16]=786433;
        possible_sizes[17]=1572869;
        possible_sizes[18]=3145739;
        possible_sizes[19]=6291469;
        possible_sizes[20]=12582917;
        possible_sizes[21]=25165843;
        possible_sizes[22]=50331653;
        possible_sizes[23]=100663319;
        possible_sizes[24]=201326611;
        possible_sizes[25]=402653189;
        possible_sizes[26]=805306457;
        possible_sizes[27]=1610612741;
    }
    ~dynamicArray()
    {
        delete []arr;
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
        int new_size=find_next();
        T* new_arr= new T[new_size]();
        for(int i=0; i<size; i++)
        {
            new_arr[i]=arr[i];
        }
        delete []arr;
        arr= new_arr;
        size=new_size;
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
    int find_next()
    {
        int new_size;
        for (int i=0; i<POSSIBLE_SIZES ; i++)
        {
            if(possible_sizes[i]==size)
            {
                new_size=possible_sizes[i+1];
                break;
            }
        }
        return new_size;
    }
    int getSize()
    {
        return size;
    }

};

#endif //HW2MIVNE_DYNAMICARRAY_H