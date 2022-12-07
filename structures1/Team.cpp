#include "Team.h"

int Team::getId() const {
    return teamId;
}

int Team::getNumPlayers() const {
    return numPlayers;
}

int Team::getPoints() const {
    return points;
}

int Team::getTotalCards() const {
    return total_cards;
}

int Team::getTotalGoals() const {
    return total_goals;
}

void Team::setPoints(int p) {
    points = p;
}
