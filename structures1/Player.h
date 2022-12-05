#ifndef STRUCTURES1_PLAYER_H
#define STRUCTURES1_PLAYER_H
#include "AVLTree.h"
//#include <memory>

class PlayerById;

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
    Node<std::shared_ptr<Player>, PlayerById> team;

public:
    Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, int closest, bool goalKeeper):
        playerId(playerId),
        teamId(teamId),
        gamesPlayed(gamesPlayed),
        scoredGoals(goals),
        cardsReceived(cards),
        closest(closest),
        isGoalKeeper(goalKeeper)
    {};

    ~Player();

    int get_id () const;

    int get_goals() const;

    int get_cards() const;

    void update_player_stats(int playerId, int gamesPlayed, int scoredGoals, int cardsReceived);

};


#endif //STRUCTURES1_PLAYER_H
