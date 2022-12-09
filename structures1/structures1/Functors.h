#ifndef STRUCTURES1_FUNCTORS_H
#define STRUCTURES1_FUNCTORS_H
#include "Team.h"
//#include <memory>


class PlayerById {
public:
    bool operator()(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2){
        return p1->get_id() < p2->get_id();
    }
};

class PlayerByGoals {
public:
    bool operator()(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2) {
        return p1->get_goals() < p2->get_goals();
    }
};

class PlayerByRank {
public:
    bool operator()(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2) {
        if (p1->get_goals() < p2->get_goals())
            return true;

        else if (p1->get_goals() == p2->get_goals()){
            if (p1->get_cards() < p2->get_cards())
                return true;

            else if (p1->get_cards() == p2->get_cards()){
                return p1->get_id() < p2->get_id();
            }
        }
        return false;
    }
    /*bool operator()(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2) {
        if (p1->get_goals() > p2->get_goals())
            return true;

        else if (p1->get_goals() == p2->get_goals()){
            if (p1->get_cards() > p2->get_cards())
                return true;

            else if (p1->get_cards() == p2->get_cards()){
                return p1->get_id() < p2->get_id();
            }
        }
        return false;
    }*/
};

class TeamById {
public:
    bool operator()(std::shared_ptr<Team> t1, std::shared_ptr<Team> t2) {
        return t1->getId() < t2->getId();
    }

};
#endif //STRUCTURES1_FUNCTORS_H
