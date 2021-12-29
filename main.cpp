#include <iostream>
# include "dynamicArray.h"
#include "hashTable.h"

int main()
{
    int minus=-1;
    int a=1,b=2,c=3,d=4,e=5,f=6,g=7,h=8,i=9,j=10,k=11,l=12,m=12,n=13,o=14;
    hashTable<int*> table(5,&minus);
    table.insert(2,&a);
    table.insert(4,&b);
    table.insert(6,&c);
    table.insert(10,&d);
    table.insert(11,&e);
    table.insert(13,&f);
    table.insert(15,&g);
    table.insert(2050,&h);
    table.insert(88,&i);
    table.insert(9,&j);
    table.insert(7,&k);
    table.insert(854,&l);
    table.insert(3,&m);
    table.insert(21,&o);
    return 0;
}