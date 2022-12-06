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
    Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper):
        playerId(playerId),
        teamId(teamId),
        gamesPlayed(gamesPlayed),
        scoredGoals(goals),
        closest(0),
        cardsReceived(cards),
        isGoalKeeper(goalKeeper)
    {
        all_players.value = nullptr;
        team.value = nullptr;
        // update closest player with other function
    };

    ~Player();

    int get_id () const;

    int get_goals() const;

    int get_cards() const;

    void update_player_stats(int playerId, int gamesPlayed, int scoredGoals, int cardsReceived);

};


#endif //STRUCTURES1_PLAYER_H
