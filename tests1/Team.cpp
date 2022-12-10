#include "Team.h"
#include "Functors.h"

void print2D(std::shared_ptr<Node<std::shared_ptr<Player>, PlayerByRank>> root, int space) {
    if (root == nullptr) // Base case  1
        return;

    space += SPACE; // Increase distance between levels   2
    print2D(root -> right, space); // Process right child first 3
    std::cout << std::endl;

    for (int i = SPACE; i < space; i++) // 5
        std::cout << " "; // 5.1
    std::cout << root -> value->get_id() << "\n"; // 6
    print2D(root -> left, space); // Process left child  7
}

AVLTree<std::shared_ptr<Player>, PlayerByRank>& Team::getPlayersByRank() {
    return playersByRank;
}

AVLTree<std::shared_ptr<Player>, PlayerById>& Team::getPlayersById(){
    return players;
}

AVLTree<std::shared_ptr<Player>, PlayerByGoals>& Team::getPlayersByGoals(){
    return playersByGoals;
}

void Team::addPlayer(std::shared_ptr<Player> player) {
    Node<std::shared_ptr<Player>, PlayerById> player_by_id(player);
    Node<std::shared_ptr<Player>, PlayerByGoals> player_by_goals(player);
    Node<std::shared_ptr<Player>, PlayerByRank> player_by_rank(player);

    players.r = players.insert(players.r, player_by_id);
    playersByGoals.r = playersByGoals.insert(playersByGoals.r, player_by_goals);
    playersByRank.r = playersByRank.insert(playersByRank.r, player_by_rank);

    if (topPlayer == nullptr)
        topPlayer = player;

    else{
        PlayerByGoals c = PlayerByGoals();
        if (c(topPlayer, player))
            topPlayer = player;
    }
    /* std::cout << "team" << teamId << " tree by goals: " << std::endl;
    print2D(playersByGoals.r, 5);
    */
    player->set_games_played_fix(matches);

    if(player->is_goalKeeper())
        goalkeepers++;

    numPlayers += 1;

    total_goals = total_goals + player -> get_goals();

    total_cards = total_cards + player -> get_cards();
}

void Team::find_pre_post(std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> root, std::shared_ptr<Team>& team,
                         std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>>& pre, std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>>& post) {
    if (root == nullptr)
        return;

    // If we reached the wanted node (this)
    if (root->value->getId() == team->getId()) {
        // the maximum value in left subtree is the previous in inorder
        if (root->left != nullptr) {
            std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> tmp = root->left;
            while (tmp->right)
                tmp = tmp->right;
            pre = tmp;
        }

        // the minimum value in right subtree is the post in inorder
        if (root->right != nullptr) {
            std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> tmp = root->right;
            while (tmp->left)
                tmp = tmp->left;
            post = tmp;
        }
        return;
    }
}

void Team::calc_neighbors(std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> root, std::shared_ptr<Team>& team) {
    std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> prev = nullptr, post = nullptr;

    find_pre_post(root, team, prev, post);
    if(post == nullptr)
        next_team = nullptr;
    else
        next_team = post->value;

    if(prev == nullptr)
        prev_team = nullptr;
    else
        prev_team = prev->value;
}

void Team::update_neighbors(){
    if(next_team != nullptr)
        next_team->prev_team = prev_team;

    if(prev_team != nullptr)
        prev_team->next_team = next_team;

    prev_team = nullptr;
    next_team = nullptr;
}

int Team::getId() const {
    return teamId;
}

int Team::getNumPlayers() const {
    return numPlayers;
}

int Team::getGoalKeepers() const {
    return goalkeepers;
}

void Team::removePlayer(std::shared_ptr<Player>& player){
    int player_id = player->get_id();

    players.r = players.deleteNode(players.r, player);
    playersByGoals.r = playersByGoals.deleteNode(playersByGoals.r, player);
    playersByRank.r = playersByRank.deleteNode(playersByRank.r, player);

    if(topPlayer->get_id() == player_id){
        if (playersByGoals.r == nullptr) {
            topPlayer = nullptr;
        }
        else
            topPlayer = (playersByGoals.maxValueNode(playersByGoals.r)->value);
    }

    if (player->is_goalKeeper())
        goalkeepers--;
    numPlayers -= 1;
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

int Team::getMatches() const {
    return matches;
}

void Team::setMatches(int m) {
    matches = m;
}

int Team::getTopPlayerId(){
    return topPlayer->get_id();
}

std::shared_ptr<Team>& Team::get_prev(){
    return prev_team;
}

std::shared_ptr<Team>& Team::get_next(){
    return next_team;
}

std::shared_ptr<Player>& Team::getTopPlayer() {
    return topPlayer;
}

void Team::updateTeamStats(int num_players, int goal_keepers, int matches, int t_goals, int t_cards) {
    numPlayers = num_players;
    goalkeepers = goal_keepers;
    this -> matches = matches;
    total_goals = t_goals;
    total_cards = t_cards;
}

void Team::setPoints(int p) {
    points = p;
}
