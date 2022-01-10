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

class PlayersManager
        {
private:
    UnionFind<Box> uni;
    Box system_box;
    HashTable<PlayerInfo*> players_in_ds; // the group id in each player is the group from the beginning, because we have find leader.
    PlayerInfo* tomb;
    int scale;
public:
    PlayersManager(int k, int scale_) : uni(UnionFind<Box>(k,scale_)), tomb(new PlayerInfo(-1,-1,-1,-1)),
    players_in_ds(HashTable<PlayerInfo*> (tomb)), system_box(Box(scale_)), scale(scale_)
    {
        players_in_ds.setTomb(tomb);
    }
    ~PlayersManager()
    {
        Quit();
    }

    StatusType mergeGroups(int GroupID1,int GroupID2)
    {
        if (GroupID1 <=0 || GroupID2<= 0 || GroupID1 > uni.getUniverseSize() || GroupID2 > uni.getUniverseSize())
        {
            return INVALID_INPUT;
        }
        uni.union_groups(GroupID1,GroupID2,scale);
        return SUCCESS;
    }


    StatusType addPlayer(int PlayerID, int GroupID, int score) // DONE COMPLETELY
    {
        if (GroupID <= 0 || GroupID > uni.getUniverseSize() || PlayerID <= 0 || score <= 0 || score > scale )
        {
            return INVALID_INPUT;
        }
        if(players_in_ds.find(PlayerID) != -1 )
        {
            return FAILURE;
        }
        system_box.insert_player_to_box(score);
        uni.find_team_leader(GroupID)->box->insert_player_to_box(score);
        players_in_ds.insert(PlayerID,new PlayerInfo(PlayerID,GroupID,score,0));
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
        PlayerInfo *player = players_in_ds[players_in_ds.find(PlayerID)];
        //delete the player from the system box
        system_box.remove_player_from_box(player->getScore(),player->getLevel());
        //delete the player from the group box
        uni.find_team_leader(player->getGroupId())->box->remove_player_from_box(player->getScore(),player->getLevel());
        players_in_ds.remove(PlayerID);
        delete player;
        return SUCCESS;
    }

    StatusType increasePlayerIDLevel(int PlayerID, int LevelIncrease)
    {
        if( PlayerID <= 0 || LevelIncrease <= 0 )
        {
            return INVALID_INPUT;
        }
        if(players_in_ds.find(PlayerID) == -1 )
        {
            return FAILURE;
        }
        PlayerInfo *player = players_in_ds[players_in_ds.find(PlayerID)];
        if(player->getLevel() == 0)
        {
            system_box.update_lvl_for_player_lvl_0(LevelIncrease, player->getScore());
            uni.find_team_leader(player->getGroupId())->box->update_lvl_for_player_lvl_0(LevelIncrease, player->getScore());
        }
        else
        {
            system_box.update_lvl_for_player_above_lvl_0(player->getLevel(),LevelIncrease, player->getScore());
            uni.find_team_leader(player->getGroupId())->box->update_lvl_for_player_above_lvl_0(player->getLevel(),LevelIncrease, player->getScore());
        }
        player->setLevel(player->getLevel()+LevelIncrease);
        return SUCCESS;
    }

    StatusType changePlayerIDScore(int PlayerID, int NewScore)
    {
        if (PlayerID <= 0 || NewScore > scale || NewScore <= 0)
        {
            return INVALID_INPUT;
        }
        if (players_in_ds.find(PlayerID) == -1)
        {
            return FAILURE;
        }
        PlayerInfo *player = players_in_ds[players_in_ds.find(PlayerID)];
        if (player->getLevel() != 0)
        {
            system_box.change_score_in_box(player->getScore(), NewScore, player->getLevel());
            uni.find_team_leader(player->getGroupId())->box->change_score_in_box(player->getScore(), NewScore,
                                                                                player->getLevel());
        }
        player->setScore(NewScore);
        return SUCCESS;
    }

    StatusType GetPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel,
                                                    double * players)
    {
        if( GroupID<0 || GroupID>uni.getUniverseSize())
        {
            return INVALID_INPUT;
        }
        AVL<int>* avl= nullptr;
        if(GroupID==0)
        {
            avl= system_box.score_array[score];
        }
        else
        {
            avl= uni.find_team_leader(GroupID)->box->score_array[score];
        }
        avl->insert(lowerLevel);
        avl->insert(higherLevel);
        int low_rank=avl->lowRank(lowerLevel);
        int high_rank= avl->highRank(higherLevel);
        double count_between_level=high_rank-low_rank-1;
        avl->remove(lowerLevel);
        avl->remove(higherLevel);
        if(count_between_level<=0)
        {
            return FAILURE;
        }
        int size_of_avl=avl->getSize()+system_box.score_with_lvl_0[score];
        *players=(count_between_level/size_of_avl)*100;
        return SUCCESS;
    }

    StatusType averageHighestPlayerLevelByGroup(int GroupID, int m, double *avgLevel)
    {
        if( GroupID<0 || GroupID>uni.getUniverseSize())
        {
            return INVALID_INPUT;
        }
        if(m > uni.find_team_leader(GroupID)->box->num_of_players_with_lvl_0 + uni.find_team_leader(GroupID)->box->players_in_group.getSize())
        {
            return FAILURE;
        }
        AVL<int> avl;
        if(GroupID==0)
        {
            avl= system_box.players_in_group;
        }
        else
        {
            avl= uni.find_team_leader(GroupID)->box->players_in_group;
        }
        if(avl.getSize()-m<1)
        {
            *avgLevel=((double)(avl.getSum(avl.getSize())))/m;
            return SUCCESS;
        }
        double low_sum= avl.getSum(avl.getSize()-m);
        double final=uni.find_team_leader(GroupID)->box->total_level -low_sum;
        *avgLevel=(final/m);
        return SUCCESS;
    }



    StatusType GetPlayersBound(void *DS, int GroupID, int score, int m,
                               int * LowerBoundPlayers, int * HigherBoundPlayers);

     //should be enough, because each Box Destructor free all the memory he uses,
     // each tree has only ints so no memory allocated.
     // we will check it more when we'll be able to run using their main.cpp
     void Quit()
     {
        delete tomb;
    }


};



#endif //MIVNEHW2_DS_H
