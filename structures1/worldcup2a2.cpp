#include "worldcup2a2.h"

template <class S, class Cond>
void delete_tree(AVLTree<std::shared_ptr<S>, Cond> t);

Node<std::shared_ptr<Team>, TeamById>* find_team(Node<std::shared_ptr<Team>, TeamById>* root, int id);

Node<std::shared_ptr<Player>, PlayerById>* find_player_by_id(Node<std::shared_ptr<Player>, PlayerById>* root, int id);

template <class Cond>
Node<std::shared_ptr<Player>, PlayerById>* find_player_by_cond(Node<std::shared_ptr<Player>, Cond>* root, Node<std::shared_ptr<Player>, Cond>* player);


//world_cup_t::world_cup_t(){

//}

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

    //Node<std::shared_ptr<Team>>* to_add = new Node<new std::shared_ptr<Team>(teamId, points)>;

    try {
        if (find_team(allTeams.r, teamId) != nullptr){
            return StatusType::FAILURE;
        }

        std::shared_ptr<Team> team_to_add(new Team(teamId, points));
        Node<std::shared_ptr<Team>, TeamById> to_add(std::move(team_to_add));// move? רק מעדכן את השורש

        allTeams.r =  allTeams.insert(allTeams.r, &to_add);
        //std::cout << allTeams.r->value->getId() <<std::endl;
    }

    catch (const std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId) {
    if (teamId <= 0)
        return StatusType::INVALID_INPUT;

    try {
        Node<std::shared_ptr<Team>, TeamById>* team_to_remove = find_team(allTeams.r, teamId);
        if (team_to_remove == nullptr || allTeams.height(allTeams.r) == -1)
            return StatusType::FAILURE;

        legalTeams.deleteNode(legalTeams.r, team_to_remove->value);
        allTeams.deleteNode(allTeams.r, team_to_remove->value);
    }

    catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper) {
    if ((playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || goals < 0 || cards < 0)
        || (gamesPlayed == 0 && (goals > 0 || cards > 0))) {
        return StatusType::INVALID_INPUT;
    }
    // if there is a player with this ID or teamId does not exist //
    if((find_player_by_id(allPlayers.r, playerId) != nullptr) || (find_team(allTeams.r, teamId) == nullptr))
    { return StatusType::FAILURE; }

    try {
        std::shared_ptr<Player> player_to_add1(new Player(playerId, teamId, gamesPlayed, goals, cards, goalKeeper));
        std::shared_ptr<Player> player_to_add2 = player_to_add1;
        std::shared_ptr<Player> player_to_add3 = player_to_add1;
        Node<std::shared_ptr<Player>, PlayerById> player_by_id(player_to_add1);
        Node<std::shared_ptr<Player>, PlayerByRank> player_by_rank(player_to_add2);
        Node<std::shared_ptr<Player>, PlayerByGoals> player_by_goals(player_to_add3);

        allPlayers.r = allPlayers.insert(allPlayers.r, &player_by_id);
        playersByRank.r = playersByRank.insert(playersByRank.r, &player_by_rank);
        playersByGoals.r = playersByGoals.insert(playersByGoals.r, &player_by_goals);


        // check if the new player is the new top player //
        if(playersByRank.maxValueNode(playersByRank.r) -> value -> get_id() == player_by_rank.value->get_id())
        {
            topPlayer.swap(player_by_rank.value);
        }

        //std::cout << allTeams.r->value->getId() <<std::endl; //
    }
    catch(std::exception &e){
        return StatusType::ALLOCATION_ERROR;
    }

    std::cout << "use count: " << allPlayers.r->value.use_count() << std::endl;

    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
    if (playerId <= 0)
        return StatusType::INVALID_INPUT;

    try {
        if (allPlayers.height(allPlayers.r) == -1)
            return StatusType::FAILURE;

        Node<std::shared_ptr<Player>, PlayerById>* player_to_remove = find_player_by_id(allPlayers.r, playerId);
        if (player_to_remove == nullptr)
            return StatusType::FAILURE;
        std::cout << "after find" << std::endl;

        //remove from ranking tree
        playersByRank.deleteNode(playersByRank.r, player_to_remove->value);
        std::cout << "after delete from rank tree" << std::endl;

        //if needed, replace the top player with the second best
        if (topPlayer->get_id() == player_to_remove->value->get_id()){
            topPlayer.reset(/*playersByRank.maxValueNode(playersByRank.r)->value*/);
        }
        std::cout << "after top player check" << std::endl;

        //remove from goals tree
        playersByGoals.deleteNode(playersByGoals.r, player_to_remove->value);
        std::cout << "after delete from goals tree" << std::endl;


        //std::cout << "use count: " << player_to_remove->value.use_count() << std::endl;

        //remove from the main players tree
        allPlayers.deleteNode(allPlayers.r, player_to_remove->value);
        std::cout << "after delete from main tree" << std::endl;

        std::cout << "height: " << (allPlayers.height(allPlayers.r)) << std::endl;

        std::cout << "is root null: " << (allPlayers.r->value == nullptr) << std::endl;
    }

    catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;

}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed, int scoredGoals, int cardsReceived)
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
void delete_tree(AVLTree<std::shared_ptr<S>, Cond> t){
    while (t.r != nullptr){
        t.deleteNode(t.r, t.r -> value);
    }

    /*while (1){
        //reset the shared_ptr to release the pointed object
        root.r -> value.reset();

        //if both children are nullptr then we have a root with only one node
        if (root.r -> right == nullptr && root.r -> left == nullptr) {
            delete root.r;
            root.r = nullptr;
            break;
        }

        //if the root only has a left child then remove the root and remain with a root with one node
        else if (root.r -> right == nullptr){
            root = root.r -> left -> value;
            root.deleteNode(root.r, root);
            root.r -> value = root;
        }

            //if the root only has a right child then remove the root and remain with a root with one node
        else if (root.r->left == nullptr){
            S temp = root.r->right->value;
            root.deleteNode(root.r, temp);
            root.r->value = temp;
        }

        else
            root.deleteNode(root.r, root.r->value);
    }*/
}
//Team*
    Node<std::shared_ptr<Team>, TeamById>* find_team(Node<std::shared_ptr<Team>, TeamById>* root, int id){
    if (root == nullptr) {
        return nullptr;
    }
    if (root -> value -> getId() < id) { //id > root id
        return find_team(root -> right, id);
    }
    else if (root -> value -> getId() > id) {  //val > root -> value
        return find_team(root -> left, id);
    }
    else {
        //duplicate values
        return root;
    }
}

Node<std::shared_ptr<Player>, PlayerById>* find_player_by_id(Node<std::shared_ptr<Player>, PlayerById>* root, int id) {
    if (root == nullptr || root->value == nullptr) {
        return nullptr;
    }

    if ( root -> value -> get_id() < id) { //id > root id
        return find_player_by_id(root->right, id);
    }
    else if (root ->  value -> get_id() > id) {  // val > root -> value
        return find_player_by_id(root->left, id);
    }
    else {
        //duplicate values
        return root;
    }
}

template <class Cond>
Node<std::shared_ptr<Player>, Cond>* find_player_by_cond(Node<std::shared_ptr<Player>, Cond>* root,Node<std::shared_ptr<Player>, Cond>* player)
 {
    Cond c = Cond();

    if (root == nullptr) {
        return nullptr;
    }
    if (c(root->value, player)) { //player > root -> player
        return find_player_by_cond(root->right, player);
    }
    else if (c(player, root->value)) {  // player < root -> player
        return find_player_by_cond(root->left, player);
    }
    else {
        //duplicate values
        return root;
    }
}