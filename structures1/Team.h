#ifndef STRUCTURES1_TEAM_H
#define STRUCTURES1_TEAM_H
#include "Player.h"

class PlayerById;
class PlayerByGoals;
class PlayerByRank;

class Team {
private:
    int teamId;
    int points;
    int numPlayers;
    std::shared_ptr<Player> topPlayer;
    AVLTree<std::shared_ptr<Player>, PlayerByRank> playersByRank;
    AVLTree<std::shared_ptr<Player>, PlayerByGoals> playersByGoals;
    AVLTree<std::shared_ptr<Player>, PlayerById> players;

public:
    Team(int team_id, int points):
    teamId(team_id),
    points(points),
    numPlayers(0)
    {};

    /*Team(int teamId ,int points, int numPlayers, Player* topPlayer, AVLTree<Player> team):
        m_teamId(teamId), m_points(points), m_numPlayers(numPlayers),
        m_topPlayer(topPlayer), m_team(team)
    {};*/

    int getId() const;

    int getNumPlayers() const;
    

};
#endif //STRUCTURES1_TEAM_H
