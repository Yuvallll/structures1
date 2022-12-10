#ifndef STRUCTURES1_LTEAM_H
#define STRUCTURES1_LTEAM_H

class LTeam {
    int teamId;
    int points;

public:
    LTeam(): teamId(0), points(0){};

    LTeam(int team_id, int p): teamId(team_id), points(p) {};

    void setTeamId(int id);

    void setPoints(int p);

    int getPoints() const;

    int getTeamId() const;
};


#endif //STRUCTURES1_LTEAM_H
