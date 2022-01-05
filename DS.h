//
// Created by Tsahiedri and Doron on 05/01/2022.
//

#ifndef MIVNEHW2_DS_H
#define MIVNEHW2_DS_H
#include "UnionFind.h"
#include "avltree.h"
#include "hashTable.h"
#include "box.h"
#include "player_info.h"
#include "library2.h"

using namespace std;

class PlayersManager{
private:
    UnionFind<Box> uni;
    Box system;
    HashTable<PlayerInfo> players_in_ds;
    PlayerInfo* tomb;
public:
    PlayersManager(int k, int scale) : uni(UnionFind<Box>(k)), tomb(new PlayerInfo(-1,-1,-1,-1)),
    players_in_ds(HashTable<PlayerInfo> (*tomb)), system(Box(scale))
    {
        players_in_ds = HashTable<PlayerInfo>(*tomb);
    }
    ~PlayersManager()
    {
        delete tomb;
    }
    StatusType mergeGroups(int GroupID1,int GroupID2)
    {
        if (GroupID1 <=0 || GroupID2<= 0 || GroupID1 > uni.getUniverseSize() || GroupID2 > uni.getUniverseSize())
        {
            return INVALID_INPUT;
        }
    }
};



#endif //MIVNEHW2_DS_H