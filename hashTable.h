#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <iostream>
#define POSSIBLE_SIZES 28
#define TOMBSTONE -1

template <class S>
S return_null()
{
    S* nu= new S[1](); // create an array using the default constructor
    S absolut_null=nu[0]; // get the default value of T
    delete []nu;
    return absolut_null;
}

template<class T>
class hashTable
        {
private:
    class M
    {
    private:
        int key;
        T data;
    public:
        M(int k, T d)
        {
            key=k;
            data=d;
        }
        M()=default;
        bool operator !=(M a)
        {
            if(a.data==data && a.key==key)
            {
                return false;
            }
            return true;
        }
        bool operator ==(M a)
        {
            if(a.key== key && a.data==data)
            {
                return true;
            }
            return false;
        }
        M& operator=(M& other)
        {
            key=other.key;
            data=other.data;
        }
        int get_key()
        {
            return key;
        }
        T get_data()
        {
            return data;
        }
    };
    M* arr; //the dynamic array
    int size;
    int number_of_element;
    int number_of_tombstone;
    int prime_possible_sizes[POSSIBLE_SIZES];
public:
    hashTable(int length )
    {
        init_prime();
        int upper_prime=find_upper(length);
        arr = new M[upper_prime]();
        size = upper_prime;
        number_of_element=0;
        number_of_tombstone=0;
    }
    ~hashTable()
    {
        delete []arr;
    }
    int insert_position(int id, T data,M* array)
    {
        int index_to_insert= hash(id);
        int k=1; //hash with k =0 upper line
        M element=array[index_to_insert];
        while(element != return_null<M>() || element.get_key() == TOMBSTONE)
        {
            if(element != return_null<M>() && element.get_data() == data )
            {
                return -1;
            }
            index_to_insert = double_hashing(id,k);
            element=array[index_to_insert];
            k++;
        }
        return index_to_insert;
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

    int insert(int id, T data)
    {
        int index_to_insert= insert_position(id,data,arr);
        M new_element = M(id,data);
        set(index_to_insert,new_element,arr);
        number_of_element++;
        return 0;
    }

    void set(int index, M value, M* array)
    {
        if( array[index] != return_null<M>())
        {
            return ; //error to throw :: there is a problem in
        }
        array[index]=value;
        if(number_of_element>(size/2))
        {
            resize();
        }
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

    void resize()
    {
        int new_size= find_next();
        M* new_arr= new M[new_size]();
        for( int j=0; j<size; j++)
        {
            new_arr[j]=arr[j];
        }
        delete []arr;
        arr= new_arr;
        size=new_size;
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

    void set_tomb(int index, M value, M* array)
    {
        array[index]=value;
    }

    /*
    void clean_tombstone()
    {
        int new_size=find_upper(number_of_element);
        M* new_arr=new M[new_size]();
        for (int i=0; i<size; i++)
        {
            if(arr[i] == return_null<M>())
            {
                continue;
            }
            M element=arr[i];
            if( element.get_data() != return_null<M>().get_data())
            {
                int index_to_insert = insert_position(element.get_key(),element.get_data(),new_arr);
                set(index_to_insert,element,new_arr);
            }
        }
        delete []arr;
        arr = new_arr;
        size=new_size;
        number_of_tombstone=0;
    }
*/
    void clean_tombstone()
    {
        M* new_arr=new M[number_of_element]();
        for (int i=0; i<size; i++)
        {
            if (arr[i] == return_null<M>()) {
                continue;
            }
            M element = arr[i];
            if (element.get_data() != return_null<M>().get_data()) {
                new_arr[i] = element;
            }
        }
        for(int i=0; i<number_of_element; i++)
        {
            insert(new_arr->get_key(),new_arr->get_data());
        }
        delete []new_arr;
    }


    void remove(int id, int no)
    {
        int index_to_remove= hash(id),k=1;
        M element= arr[index_to_remove];
        while( element.get_key() != id)
        {
            index_to_remove=double_hashing(id,k);
            element= arr[index_to_remove];
            k++;
        }
        M tombstone= M(element.get_key(), return_null<M>().get_data());
        set_tomb(index_to_remove,tombstone,arr);
        number_of_tombstone++;
        number_of_element--;
        /*
        if(number_of_tombstone > size/20 )//TODO: check what is the number
        {
            clean_tombstone();
        }
        */
    }
};

#endif //HASH_TABLE_H
