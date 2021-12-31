//
// Created by tsahiedri on 31/12/2021.
//
#include <iostream>
#include "hashTable.h"
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
int main(){
    Player tomb_player(-1,-1);
    HashTable<Player*> table(&tomb_player);
    /** inserting and deleting*/
    Player player1(7567432,1);
    Player player2(252123,5);
    Player player3(3213234,7);
    Player player4(464646,1);
    Player player5(325646,5);
    Player player6(999999,7);
    Player player7(87654,1);
    Player player8(345111,5);
    Player player9(1010101,7);
    Player player10(777777,1);
    Player player11(666666,5);
    Player player12(888888,7);
    Player player13(995666,1);
    Player player14(8976999,5);
    Player player15(1134563,7);
    table.insert(player1.getID(), &player1);
    table.insert(player2.getID(), &player2);
    table.insert(player3.getID(), &player3);
    table.insert(player4.getID(), &player4);
    table.insert(player5.getID(), &player5);
    table.insert(player6.getID(), &player6);
    table.insert(player7.getID(), &player7);
    table.insert(player8.getID(), &player8);
    table.insert(player9.getID(), &player9);
    table.insert(player10.getID(), &player10);
    table.insert(player11.getID(), &player11);
    table.insert(player12.getID(), &player12);
    table.insert(player13.getID(), &player13);
    table.insert(player14.getID(), &player14);
    table.insert(player15.getID(), &player15);
    table.remove(player10.getID());
    table.remove(player11.getID());
    table.remove(player12.getID());
    return 0;
}