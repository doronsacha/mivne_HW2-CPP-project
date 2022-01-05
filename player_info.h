//
// Created by tsahiedri on 05/01/2022.
//

#ifndef MIVNEHW2_PLAYER_INFO_H
#define MIVNEHW2_PLAYER_INFO_H


class PlayerInfo{
private:
    int player_id;
    int group_id;
    int score;
    int level;
public:
    PlayerInfo() = default;
    PlayerInfo(int playerId, int groupId, int score, int level) :
        player_id(playerId), group_id(groupId), score(score), level(level) {}
    ~PlayerInfo() = default;

    int getPlayerId() const {
        return player_id;
    }

    int getGroupId() const {
        return group_id;
    }

    int getScore() const {
        return score;
    }

    int getLevel() const {
        return level;
    }

    void setPlayerId(int playerId) {
        player_id = playerId;
    }

    void setGroupId(int groupId) {
        group_id = groupId;
    }

    void setScore(int score) {
        PlayerInfo::score = score;
    }

    void setLevel(int level) {
        PlayerInfo::level = level;
    }
};

#endif //MIVNEHW2_PLAYER_INFO_H
