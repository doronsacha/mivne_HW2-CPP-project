//
// Created by tsahiedri on 06/01/2022.
//

#include "DS.h"

int main()
{
    PlayersManager player(16,69);
    player.addPlayer(531300935,16,69);
    player.addPlayer(2109360950,39,78);
    player.removePlayer(531300935);
    player.removePlayer(2109360950);

    player.addPlayer(1765824312,10,60);
    player.addPlayer(1774460279,11,78);
    player.mergeGroups(10,11);
    player.changePlayerIDScore(1765824312, 20);
    player.increasePlayerIDLevel(1765824312,19);
}

