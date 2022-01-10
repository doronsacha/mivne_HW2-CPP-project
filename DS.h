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
    int scale;
    UnionFind<Box> uni;
    Box system_box;
    HashTable<PlayerInfo*> players_in_ds; // the group id in each player is the group from the beginning, because we have find leader.
    PlayerInfo* tomb;
public:
    PlayersManager(int k, int scale_) : scale(scale_), uni(UnionFind<Box>(k,scale_)),system_box(Box(scale_)),players_in_ds(HashTable<PlayerInfo*>(new PlayerInfo(-1,-1,-1,-1)))
    {
        tomb= new PlayerInfo(-1,-1,-1,-1);
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
            uni.find_team_leader(player->getGroupId())->box->change_score_in_box(player->getScore(), NewScore,player->getLevel());
        }
        if(player->getLevel()==0)
        {
            system_box.score_with_lvl_0[player->getScore()]--;
            uni.find_team_leader(player->getGroupId())->box->score_with_lvl_0[player->getScore()]--;
            system_box.score_with_lvl_0[NewScore]++;
            uni.find_team_leader(player->getGroupId())->box->score_with_lvl_0[NewScore]++;
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
        if(lowerLevel<=0 || higherLevel<=0)
        {
            return GetNegativePercent(GroupID,score,lowerLevel,higherLevel,players);
        }
        AVL<int>* avl;
        AVL<int>* global_avl;
        int num_zeros=0;
        if(GroupID==0)
        {
            avl= system_box.score_array[score];
            global_avl=&system_box.players_in_group;
            if(avl->getSize()==0)
            {
                *players=0;
                return SUCCESS;
            }
        }
        else
        {
            avl= uni.find_team_leader(GroupID)->box->score_array[score];
            global_avl= &uni.find_team_leader(GroupID)->box->players_in_group;
            if(avl->getSize()==0)
            {
                *players=0;
                return SUCCESS;
            }
        }
        avl->insert(lowerLevel);
        avl->insert(higherLevel);
        global_avl->insert(lowerLevel);
        global_avl->insert(higherLevel);
        int low_rank=avl->lowRank(lowerLevel);
        int high_rank= avl->highRank(higherLevel);
        int global_low=global_avl->lowRank(lowerLevel);
        int global_high=global_avl->highRank(higherLevel);
        double count_between_level=high_rank-low_rank-1;
        double global_count_between=global_high-global_low-1;
        if(global_count_between == 0)
        {
            return FAILURE;
        }
        avl->remove(lowerLevel);
        avl->remove(higherLevel);
        global_avl->remove(lowerLevel);
        global_avl->remove(higherLevel);
        *players=(count_between_level/global_count_between)*100;
        return SUCCESS;
    }

    StatusType averageHighestPlayerLevelByGroup(int GroupID, int m, double *avgLevel)
    {
        if( GroupID<0 || GroupID>uni.getUniverseSize())
        {
            return INVALID_INPUT;
        }
        if(GroupID != 0 && m > uni.find_team_leader(GroupID)->box->num_of_players_with_lvl_0 + uni.find_team_leader(GroupID)->box->players_in_group.getSize())
        {
            return FAILURE;
        }
        AVL<int> *avl;
        if(GroupID==0)
        {
            avl= &(system_box.players_in_group);
        }
        else
        {
            avl= &(uni.find_team_leader(GroupID)->box->players_in_group);
        }
        if(avl->getSize() == 0)
        {
            *avgLevel =0;
            return SUCCESS;
        }
        if(avl->getSize()-m<1)
        {
            *avgLevel=((double)(avl->getSum(avl->getSize())))/m;
            return SUCCESS;
        }
        double low_sum= avl->getSum(avl->getSize()-m);
        double final=uni.find_team_leader(GroupID)->box->total_level -low_sum;
        *avgLevel=(final/m);
        return SUCCESS;
    }

StatusType GetNegativePercent(int GroupID, int score, int lowerLevel, int higherLevel,double * players)
{
        if(higherLevel<0)
        {
            return FAILURE;
        }

        if(lowerLevel<0)
        {
            lowerLevel=0;
        }
        AVL<int>* avl;
        AVL<int>* global_avl;
        double num_zero;
        int global_num_zero;
        if(GroupID==0)
        {
            avl= system_box.score_array[score];
            global_avl=&system_box.players_in_group;
            num_zero=system_box.score_with_lvl_0[score];
            global_num_zero=system_box.num_of_players_with_lvl_0;
        }
        else
        {
            avl= uni.find_team_leader(GroupID)->box->score_array[score];
            global_avl= &uni.find_team_leader(GroupID)->box->players_in_group;
            num_zero=uni.find_team_leader(GroupID)->box->score_with_lvl_0[score];
            global_num_zero=uni.find_team_leader(GroupID)->box->num_of_players_with_lvl_0;
        }
        if(lowerLevel==0 && higherLevel==0)
        {
            *players=(num_zero/global_num_zero)*100;
            return SUCCESS;
        }
        if(lowerLevel==0 && higherLevel!=0)
        {
            avl->insert(lowerLevel);
            avl->insert(higherLevel);
            global_avl->insert(lowerLevel);
            global_avl->insert(higherLevel);
            int low_rank=avl->lowRank(lowerLevel);
            int high_rank= avl->highRank(higherLevel);
            int global_low=global_avl->lowRank(lowerLevel);
            int global_high=global_avl->highRank(higherLevel);
            double count_between_level=high_rank-low_rank-1+num_zero;
            double global_count_between=global_high-global_low-1+global_num_zero;
            if(global_count_between == 0)
            {
                return FAILURE;
            }
            avl->remove(lowerLevel);
            avl->remove(higherLevel);
            global_avl->remove(lowerLevel);
            global_avl->remove(higherLevel);
            *players=(count_between_level/global_count_between)*100;
            return SUCCESS;
        }

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