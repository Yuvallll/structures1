#ifndef STRUCTURES1_PLAYER_H
#define STRUCTURES1_PLAYER_H
#include "AVLTree.h"
//#include <memory>

class PlayerById;
class PlayerByRank;
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
    int gamesPlayed_fix;

public:
    Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper, std::shared_ptr<Team> team):
        playerId(playerId),
        teamId(teamId),
        gamesPlayed(gamesPlayed),
        scoredGoals(goals),
        cardsReceived(cards),
        closest(0),
        isGoalKeeper(goalKeeper),
        team(team)
    {
        // check if t is null
    };

    ~Player();

    int get_id () const;

    bool is_goalKeeper();

    int get_goals() const;

    int get_cards() const;

    int get_closest();

    void find_pre_post(Node<std::shared_ptr<Player>, PlayerByRank>* root, std::shared_ptr<Player>& player, Node<std::shared_ptr<Player>,
            PlayerByRank>*& pre, Node<std::shared_ptr<Player>, PlayerByRank>*& post, PlayerByRank cond);

    void calc_closest(Node<std::shared_ptr<Player>, PlayerByRank>* root, std::shared_ptr<Player>& player);

    int get_games_played() const;

    void set_games_played(int g);

    int get_games_played_fix() const;

    void set_games_played_fix(int f);

    std::shared_ptr<Team>& get_team();

    void update_player_stats(int gamesPlayed, int scoredGoals, int cardsReceived);
};


#endif //STRUCTURES1_PLAYER_H
