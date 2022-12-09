#include "Player.h"
#include "Functors.h"///////////// legal??

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

int Player::get_closest() {
    return closest;
}

bool Player::is_goalKeeper(){
    return isGoalKeeper;
}

int abs_dist(int a, int b){
    if (a-b < 0)
        return b-a;

    return a-b;
}

void Player::find_pre_post(Node<std::shared_ptr<Player>, PlayerByRank>* root, std::shared_ptr<Player>& player,
                           Node<std::shared_ptr<Player>, PlayerByRank>*& pre, Node<std::shared_ptr<Player>,
                                   PlayerByRank>*& post, PlayerByRank cond) {
    if (root == nullptr)
        return;

    // If we reached the wanted node (this)
    if (root->value->get_id() == player->get_id()) {
        // the maximum value in left subtree is the previous in inorder
        if (root->left != nullptr) {
            Node<std::shared_ptr<Player>, PlayerByRank> *tmp = root->left;
            while (tmp->right)
                tmp = tmp->right;
            pre = tmp;
        }

        // the minimum value in right subtree is the post in inorder
        if (root->right != nullptr) {
            Node<std::shared_ptr<Player>, PlayerByRank> *tmp = root->right;
            while (tmp->left)
                tmp = tmp->left;
            post = tmp;
        }
        return;
    }

    // If key is smaller than root's key, go to left subtree
    if (cond(player, root->value)) {
        std::cout << root->value->get_id() << std::endl;
        post = root;
        find_pre_post(root->left, player, pre, post, cond);
    }
    // go to right subtree
    else{
        pre = root;
        find_pre_post(root->right, player, pre, post, cond);
    }
}

void Player::calc_closest(Node<std::shared_ptr<Player>, PlayerByRank>* root, std::shared_ptr<Player>& player) {
    Node<std::shared_ptr<Player>, PlayerByRank> *previous = nullptr, *post = nullptr;
    PlayerByRank cond = PlayerByRank();

    if (player->get_id() == 2008){
        std::cout << "now 2008" << std::endl;
    }
    find_pre_post(root, player, previous, post, cond);
    /*    if (previous != nullptr)
            std::cout << "prev: " <<previous->value->get_id() <<std::endl;

        if (post != nullptr)
            std::cout << "post: " << post->value->get_id() << std::endl;*/

    if (previous == nullptr) {
        if (post == nullptr)
            closest = 0;

        else
            closest = post->value->get_id();

        return;
    }

    if (post == nullptr) {
        closest = previous->value->get_id();
        return;
    }

    if (abs_dist(previous->value->get_goals(), player->get_goals()) < abs_dist(post->value->get_goals(),
                                                                               player->get_goals())) {
        closest = previous->value->get_id();
    } else if (abs_dist(previous->value->get_goals(), player->get_goals()) > abs_dist(post->value->get_goals(),
                                                                                      player->get_goals())) {
        closest = post->value->get_id();
    } else {
        if (abs_dist(previous->value->get_cards(), player->get_cards()) < abs_dist(post->value->get_cards(),
                                                                                   player->get_cards())) {
            closest = previous->value->get_id();
        } else if (abs_dist(previous->value->get_cards(), player->get_cards()) > abs_dist(post->value->get_cards(),
                                                                                          player->get_cards())) {
            closest = post->value->get_id();
        } else {
            if (abs_dist(previous->value->get_id(), player->get_id()) < abs_dist(post->value->get_id(),
                                                                                 player->get_id()))
                closest = previous->value->get_id();

            else if(abs_dist(previous->value->get_id(), player->get_id()) > abs_dist(post->value->get_id(),
                                                                                     player->get_id()))
                closest = post->value->get_id();

            else{
                if (previous->value->get_id() > post->value->get_id())
                    closest = previous->value->get_id();

                else
                    closest = post->value->get_id();
            }
        }
    }
}

int Player::get_cards() const {
    return cardsReceived;
}

int Player::get_games_played() const {
    return gamesPlayed;
}

void Player::set_games_played(int g){
gamesPlayed = g;
}

int Player::get_games_played_fix() const {
    return gamesPlayed_fix;
}

void Player::set_games_played_fix(int f) {
    gamesPlayed_fix = f;
}

std::shared_ptr<Team>& Player::get_team(){
    return team;
}

Player::~Player() {
    all_players.value.reset();
}




