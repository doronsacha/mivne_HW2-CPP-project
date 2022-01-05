
#include "UnionFind.h"
#include <iostream>
#include "cassert"
using namespace std;


class Box{
int group_id;
public:
int size;
Node<Box>* head;
Box(int id): group_id(id), size(1){}
int getID()
{
return group_id;
}
};

int main()
{
    return 0;
}