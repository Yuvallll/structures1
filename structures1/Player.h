#ifndef STRUCTURES1_PLAYER_H
#define STRUCTURES1_PLAYER_H
#include "AVLTree.h"
//#include <memory>

class PlayerById;
class Team;

class Player {
private:
    int playerId;
    int teamId;
    int gamesPlayed;
    int scoredGoals;
    int cardsReceived;
    int closest;
    bool isGoalKeeper;
    Node<std::shared_ptr<Player>, PlayerById> all_players;
    //Node<std::shared_ptr<Team>, PlayerById> team;
    std::shared_ptr<Team> team;

public:
    Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper, std::shared_ptr<Team> t):
        playerId(playerId),
        teamId(teamId),
        gamesPlayed(gamesPlayed),
        scoredGoals(goals),
        closest(0),
        cardsReceived(cards),
        isGoalKeeper(goalKeeper),
        team(t)
    {
        // update closest player with other function
    };

    ~Player();

    int get_id () const;

    int get_goals() const;

    int get_cards() const;

    int get_games_played() const;

    std::shared_ptr<Team>& get_team();

    void update_player_stats(int gamesPlayed, int scoredGoals, int cardsReceived);

};


#endif //STRUCTURES1_PLAYER_H
