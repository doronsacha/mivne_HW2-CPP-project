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
    Box system_box;
    HashTable<PlayerInfo> players_in_ds; // the group id in each player is the group from the beginning, because we have find leader.
    PlayerInfo* tomb;
    int scale;
public:
    PlayersManager(int k, int scale_) : uni(UnionFind<Box>(k)), tomb(new PlayerInfo(-1,-1,-1,-1)),
    players_in_ds(HashTable<PlayerInfo> (*tomb)), system_box(Box(scale_)), scale(scale_)
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
        uni.union_groups(GroupID1,GroupID2); // need to complete merge_boxes in box.h
        return SUCCESS;
    }


    StatusType addPlayer(int PlayerID, int GroupID, int score) // DONE COMPLETELY
    {
        if (GroupID <= 0 || GroupID > uni.getUniverseSize() || PlayerID <= 0 || score <= 0 || score > scale )
        {
            return INVALID_INPUT;
        }
        if(players_in_ds.find(PlayerID) == -1 )
        {
            return FAILURE;
        }
        system_box.insert_player_to_box();
        uni.find_team_leader(GroupID)->box->insert_player_to_box();
        players_in_ds.insert(PlayerID,PlayerInfo(PlayerID,GroupID,score,0));
        return SUCCESS;
    }

    StatusType removePlayer(int PlayerID) // DONE COMPLETELY
    {
        if(PlayerID <= 0)
        {
            return INVALID_INPUT;
        }
        if(players_in_ds.find(PlayerID) == -1 )
        {
            return FAILURE;
        }
        PlayerInfo player = players_in_ds[players_in_ds.find(PlayerID)];
        //delete the player from the system box
        system_box.remove_player_from_box(player.getScore(),player.getLevel());
        //delete the player from the group box
        uni.find_team_leader(player.getGroupId())->box->remove_player_from_box(player.getScore(),player.getLevel());
        return SUCCESS;
    }
};



#endif //MIVNEHW2_DS_H
