#include "Player.h"

void Player::update_player_stats(int games_played, int scored_goals, int cards_received){
    gamesPlayed += games_played;
    scoredGoals += scored_goals;
    cardsReceived += cards_received;
}

int Player::get_id() const{
    return playerId;
}

int Player::get_goals() const {
    return scoredGoals;
}

int Player::get_cards() const {
    return cardsReceived;
}

int Player::get_games_played() const {
    return gamesPlayed;
}

std::shared_ptr<Team>& Player::get_team(){
    return team;
}

Player::~Player() {
    all_players.value.reset();
}




