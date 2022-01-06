#include "DS.h"
#include "library2.h"


void* Init(int k, int scale)
{
    PlayersManager* DS= new PlayersManager(k,scale);
    if(DS == NULL)
    {
        return NULL;
    }
    return (void*) DS;
}
StatusType MergeGroups(void *DS, int GroupID1, int GroupID2)
{
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    return ((PlayersManager*)DS)->mergeGroups(GroupID1,GroupID2);
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int score)
{
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    return ((PlayersManager*)DS)->addPlayer(PlayerID,GroupID,score);
}


StatusType RemovePlayer(void *DS, int PlayerID)
{
    if(DS== NULL)
    {
        return INVALID_INPUT;
    }
    return ((PlayersManager*)DS)->removePlayer(PlayerID);
}


StatusType IncreasePlayerIDLevel(void *DS, int PlayerID, int LevelIncrease)
{
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    return ((PlayersManager*)DS)->increasePlayerIDLevel(PlayerID,LevelIncrease);
}

StatusType ChangePlayerIDScore(void *DS, int PlayerID, int NewScore)
{
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    return ((PlayersManager*)DS)->changePlayerIDScore(PlayerID,NewScore);
}

StatusType GetPercentOfPlayersWithScoreInBounds(void *DS, int GroupID, int score, int lowerLevel, int higherLevel,
                                                double * players)
{
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    return ((PlayersManager*)DS)->getPercentOfPlayersWithScoreInBounds(GroupID,score,lowerLevel,higherLevel,players);
}

StatusType AverageHighestPlayerLevelByGroup(void *DS, int GroupID, int m, double * level)
{
    if (DS==NULL)
    {
        return INVALID_INPUT;
    }
    return ((PlayersManager*)DS)->averageHighestPlayerLevelByGroup(GroupID,m,level);
}

void Quit(void** DS)
{
    delete (*((PlayersManager**)DS));
    *DS=NULL;
}