#include <iostream>
# include "dynamicArray.h"

int main()
{
    /*
    dynamicArray<int> arr(4, -1);
    arr.push(1);
    arr.push(72);
    arr.push(9);
    arr.push(81);
    arr.push(172);
    arr.push(169);
    arr.push(139);
    arr.push(115);
    arr.push(65);
    arr.push(11);
    arr.push(131);
    arr.push(178);
    arr.push(86);
    arr.push(74);
    arr.push(135);
    arr.push(139);
    for(int index=0; index<16; index++)
    {
        cout<< arr[index]<< endl;
    }
    */

    dynamicArray<int*> arr(4, nullptr);
    int a=9,b=2;
    arr.push(&a);
    arr.push(&b);
    for(int index=0; index<2; index++)
    {
        cout<< *arr[index]<< endl;
    }
    return 0;
}