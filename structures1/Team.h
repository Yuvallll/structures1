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
    int goalkeepers;
    int total_goals;
    int total_cards;
    int matches;
    std::shared_ptr<Player> topPlayer;


public:
    AVLTree<std::shared_ptr<Player>, PlayerByRank> playersByRank;
    AVLTree<std::shared_ptr<Player>, PlayerByGoals> playersByGoals;
    AVLTree<std::shared_ptr<Player>, PlayerById> players;

    explicit Team(int team_id, int points):
    teamId(team_id),
    points(points),
    numPlayers(0),
    goalkeepers(0),
    matches(0),
    total_goals(0),
    total_cards(0)
    {};

    /*Team(int teamId ,int points, int numPlayers, Player* topPlayer, AVLTree<Player> team):
        m_teamId(teamId), m_points(points), m_numPlayers(numPlayers),
        m_topPlayer(topPlayer), m_team(team)
    {};*/

    int getId() const;

    int getNumPlayers() const;

    int getPoints() const;

    int getTotalGoals() const;

    int getTotalCards() const;

    void setPoints(int p);

};//send by reference?
#endif //STRUCTURES1_TEAM_H
