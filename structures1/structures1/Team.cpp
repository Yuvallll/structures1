#include "Team.h"
#include "Functors.h"

void print2D(Node<std::shared_ptr<Player>, PlayerById>* root, int space) {
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

    players.r = players.insert(players.r, &player_by_id);
    playersByGoals.r = playersByGoals.insert(playersByGoals.r, &player_by_goals);
    playersByRank.r = playersByRank.insert(playersByRank.r, &player_by_rank);

    //std::cout << "team tree: " << players.r->value->get_id() << std::endl;
    //print2D(players.r, 5);

    if(player->is_goalKeeper())
        goalkeepers++;

    numPlayers += 1;

    total_goals = total_goals + player -> get_goals();

    total_cards = total_cards + player -> get_cards();
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
    players.deleteNode(players.r, player);
    playersByGoals.deleteNode(playersByGoals.r, player);
    playersByRank.deleteNode(playersByRank.r, player);

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
