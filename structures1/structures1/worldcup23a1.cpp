#include "worldcup23a1.h"

world_cup_t::world_cup_t()
{}

world_cup_t::~world_cup_t()
{
    topPlayer.reset();
    delete_tree(allPlayers);
    delete_tree(playersByRank);
    delete_tree(playersByGoals);
    delete_tree(allTeams);
    delete_tree(legalTeams);
}

StatusType world_cup_t::add_team(int teamId, int points)
{
    if (teamId <= 0 || points < 0)
        return StatusType::INVALID_INPUT;

    Node<std::shared_ptr<Team>>* to_add = new Node<new std::shared_ptr<Team>(teamId, points)>;

    try {
        Node<std::shared_ptr<Team>> to_add = new Node<new std::shared_ptr<Team>(teamId, points)>;
        if (is_exist(allTeams.r, to_add)){
            delete to_add;
            return StatusType::FAILURE;
        }
        allTeams.insert(allTeams.r, &to_add);
        return StatusType::SUCCESS;
    }
    catch (const std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType world_cup_t::remove_team(int teamId) {
    if (teamId <= 0)
        return StatusType::INVALID_INPUT;

    Team *team_to_remove = find_team(allTeams.r, teamId);
    if (team_to_remove == nullptr || allTeams.height(allTeams.r) != -1)
        return StatusType::FAILURE;

    try {
        allTeams.deleteNode(allTeams.r, team_to_remove);
    }

    catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
	// TODO: Your code goes here
	return 2008;
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	// TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
	// TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
	// TODO: Your code goes here
	return 1006;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	// TODO: Your code goes here
	return 2;
}

template <class S, class Cond>
void delete_tree(Node<std::shared_ptr<S>, Cond>* tree){
    while (1){
        //reset the shared_ptr to release the pointed object
        tree.r -> value.reset();

        //if both children are nullptr then we have a tree with only one node
        if (tree.r -> right == nullptr && tree.r -> left == nullptr)
            delete tree.r;
            test.r = nullptr;
            break;

        //if the root only has a left child then remove the root and remain with a tree with one node
        else if (tree.r -> right == nullptr){
            S temp = tree.r -> left -> value;
            tree.deleteNode(tree.r, temp);
            tree.r -> value = temp;
        }

        //if the root only has a right child then remove the root and remain with a tree with one node
        else if (tree.r->left == nullptr){
            S temp = tree.r->right->value;
            tree.deleteNode(tree.r, temp);
            tree.r->value = temp;
        }

        else
            tree.deleteNode(tree.r, tree.r->value);
    }
}

Team* find_team(Node<std::shared_ptr<Team>, TeamById>* root, int id) const {
    if (root == nullptr) {
        return nullptr;
    }
    if (root -> value -> getId() < id) { //id > root id
        root -> right = find_team(root -> right, id);
    }
    else if (root -> value -> getId() > id) {  //val > root -> value
        root -> left = find_team(root -> left, id);
    }
    else {
        //duplicate values
        return root -> value;
    }
}

Player* find_player_by_id(Node<std::shared_ptr<Player>, PlayerById>* root, int id) const {
    if (root == nullptr) {
        return nullptr;
    }
    if ( root -> value -> get_id() < id)) { //id > root id
        root -> right = find_player_by_id(root->right, id);
    }
    else if ( root ->  value -> getId() > id) {  // val > root -> value
        root -> left = find_player_by_id(root->left, id);
    }
    else {
        //duplicate values
        return root->value;
    }
}
template <class Cond>

Player* find_player_by_cond(Node<std::shared_ptr<Player>, Cond>* root, Node<std::shared_ptr<Player>, Cond>* player)
const {
    if (root == nullptr) {
        return nullptr;
    }
    if (Cond(root -> value, player)) { //player > root -> player
        root -> right = find_player_by_cond(root -> right, player);
    }
    else if (Cond(player, root -> value)) {  // player < root -> player
        root -> left = find_player_by_cond(root -> left, player);
    }
    else {
        //duplicate values
        return root -> value;
    }
}