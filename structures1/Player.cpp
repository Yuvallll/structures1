#include "Player.h"

void Player::update_player_stats(int player_id, int games_played, int scored_goals, int cards_received){
    playerId = player_id;
    gamesPlayed = games_played;
    scoredGoals = scored_goals;
    cardsReceived = cards_received;
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

Player::~Player() {
    all_players.value.reset();
    team.value.reset();

}




