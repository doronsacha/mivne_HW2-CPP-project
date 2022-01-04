#include <iostream>
#include "hashTable.h"
#include <cassert>
using namespace std;

class Player{
private:
    int key;
    int data;
public:
    Player(int key, int data): key(key), data(data) {}
    int getID()
    {
        return key;
    }
    int getData()
    {
        return data;
    }
};
int main()
{
    Player tomb_player(-2, -2);
    HashTable<Player *> table(&tomb_player);
    //here insert the tests
    return 0;
}