#ifndef STRUCTURES1_TEAM_H
#define STRUCTURES1_TEAM_H
#include "Player.h"

class PlayerById;
class PlayerByGoals;
class PlayerByRank;
class TeamById;

class Team {
private:
    int teamId;
    int points;
    int numPlayers;
    int goalkeepers;
    int total_goals;
    int total_cards;
    int matches;
    AVLTree<std::shared_ptr<Player>, PlayerByRank> playersByRank;
    AVLTree<std::shared_ptr<Player>, PlayerByGoals> playersByGoals;
    AVLTree<std::shared_ptr<Player>, PlayerById> players;
    std::shared_ptr<Player> topPlayer;
    std::shared_ptr<Team> next_team;
    std::shared_ptr<Team> prev_team;


public:
    explicit Team(int team_id, int points):
    teamId(team_id),
    points(points),
    numPlayers(0),
    goalkeepers(0),
    total_goals(0),
    total_cards(0),
    matches(0)
    {};

    AVLTree<std::shared_ptr<Player>, PlayerByRank>& getPlayersByRank();

    AVLTree<std::shared_ptr<Player>, PlayerById>& getPlayersById();

    AVLTree<std::shared_ptr<Player>, PlayerByGoals>& getPlayersByGoals();

    void update_neighbors();

    void addPlayer(std::shared_ptr<Player> player);

    void find_pre_post(std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> root, std::shared_ptr<Team>& team,
                             std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>>& pre, std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>>& post);

    void calc_neighbors(std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> root, std::shared_ptr<Team>& team);

    int getId() const;

    void removePlayer(std::shared_ptr<Player>& player);

    int getNumPlayers() const;

    int getGoalKeepers() const;

    int getPoints() const;

    int getTotalGoals() const;

    int getTotalCards() const;

    int getMatches() const;

    void setMatches(int m);

    int getTopPlayerId();

    std::shared_ptr<Team>& get_prev();

    std::shared_ptr<Team>& get_next();

    void updateTeamStats(int num_players, int goal_keepers, int matches, int t_goals, int t_cards);

    std::shared_ptr<Player>& getTopPlayer();

    void setPoints(int p);

};//send by reference?
#endif //STRUCTURES1_TEAM_H
