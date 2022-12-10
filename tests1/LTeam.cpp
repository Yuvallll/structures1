#include "LTeam.h"

void LTeam::setTeamId(int id){
  teamId = id;
}

void LTeam::setPoints(int p){
    points = p;
}

int LTeam::getPoints() const {
    return points;
}

int LTeam::getTeamId() const {
    return teamId;
}