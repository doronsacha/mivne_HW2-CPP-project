#include <iostream>

#include "hashTable.h"

int main()
{
    struct new_m
            {
        int* data;
        int key;
            };
    int min= -1;
    new_m minus={&min,-1};
    hashTable<int*> table(5,&min);
    int a= 1;
    table.insert(a,{&a,a});
    int b= 2;
    table.insert(b,{&b,b});
    int c= 3;
    table.insert(c,{&c,c});
    int d= 4;
    table.insert(d,{&d,d});
    int e= 5;
    table.insert(e,{&e,e});
    int f= 6;
    table.insert(f,{&f,f});
    int g= 7;
    table.insert(g,{&g,g});
    int h= 8;
    table.insert(h,{&h,h});

    table.remove(1);
    table.remove(2);
    table.remove(3);
    table.remove(4);
    table.remove(5);
    table.remove(6);
    table.remove(7);
    return 0;
}