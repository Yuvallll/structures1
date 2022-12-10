#include "worldcup23a1.h"
LTeam winner(LTeam tournament[], int size);

template <class Cond>//for teams
void print2D(std::shared_ptr<Node<std::shared_ptr<Player>, Cond>> root, int space) {
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

template <class Cond>//for players
void print2D(Node<std::shared_ptr<Team>, Cond>* root, int space) {
    if (root == nullptr) // Base case  1
        return;

    space += SPACE; // Increase distance between levels   2
    print2D(root -> right, space); // Process right child first 3
    std::cout << std::endl;

    for (int i = SPACE; i < space; i++) // 5
        std::cout << " "; // 5.1
    std::cout << root -> value->getId() << "\n"; // 6
    print2D(root -> left, space); // Process left child  7
}

template <class Cond>
void merge(std::shared_ptr<Player>*& a, int na, std::shared_ptr<Player>*& b, int nb, std::shared_ptr<Player>*& c, Cond cond) {// maybe should be Node** instead
    int ia = 0, ib = 0, ic = 0;
    while (ia < na && ib < nb) {
        if (cond(a[ia], b[ib]))//פה זה קורס על הבדיקה של getScoredGoals
        {
            c[ic] = a[ia];
            ia++;
            ic++;
        }
        else {
            c[ic] = b[ib];
            ib++;
            ic++;
        }
    }

    while (ia < na)
        c[ic++] = a[ia++];
    while (ib < nb)
        c[ic++] = b[ib++];
}
/*
template <class Cond>
Node<std::shared_ptr<Player>, Cond>* create_new_node(std::shared_ptr<Player>& data, Cond c){
    Node<std::shared_ptr<Player>, Cond>* node = new Node<std::shared_ptr<Player>, Cond>(data);
    node->left = nullptr;
    node->right = nullptr;

    return node;
}*/

std::shared_ptr<Team> find_in_range(std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> root, int minVal, int maxVal){
    if (root == nullptr)
        return nullptr;

    if (root->value->getId() < minVal){
        return find_in_range(root->right, minVal, maxVal);
    }

    else if (root->value->getId() > maxVal){
        return find_in_range(root->left, minVal, maxVal);
    }

    else{
        return root->value;
    }
}

template<class Cond>
std::shared_ptr<Node<std::shared_ptr<Player>, Cond>> buildTree(std::shared_ptr<Player>*& arr,int start, int end, Cond c){
   if(start > end)
       return nullptr;

   int mid = (start + end)/2;
   //הורדתי את התנאי כי הוא מה שדפק לנו את המערך

    std::shared_ptr<Node<std::shared_ptr<Player>, Cond>> root = std::shared_ptr<Node<std::shared_ptr<Player>, Cond>>(new Node<std::shared_ptr<Player>, Cond>(arr[mid]));

    root->left = nullptr;
    root->right = nullptr;

   root -> left = buildTree(arr, start, mid - 1, c);

   root -> right = buildTree(arr, mid + 1, end, c);

   return root;
}

template <class Cond>
void printInorder(std::shared_ptr<Node<std::shared_ptr<Player>, Cond>> root, int * const output) {
    int index = 0;

    if (root == nullptr)
        return;

    std::shared_ptr<Node<std::shared_ptr<Player>, Cond>> node = root;
    std::shared_ptr<Node<std::shared_ptr<Player>, Cond>> pre;

    while (node != nullptr) {
        if (node->left == nullptr) {
            output[index++] = node->value->get_id();
            node = node->right;
        } else {
            pre = node->left;
            while (pre->right != nullptr && pre->right != node)
                pre = pre->right;

            if (pre->right == nullptr) {
                pre->right = node;
                node = node->left;
            }
            else {
                pre->right = nullptr;
                output[index++] = node->value->get_id();
                node = node->right;
            }
        }

    }
}

template <class Cond>
void fillInorder(std::shared_ptr<Node<std::shared_ptr<Player>, Cond>> root, std::shared_ptr<Player>* output){
    int index = 0;

    if (root == nullptr)
        return;

    std::shared_ptr<Node<std::shared_ptr<Player>, Cond>> node = root;
    std::shared_ptr<Node<std::shared_ptr<Player>, Cond>> pre;

    while (node != nullptr) {
        if (node->left == nullptr) {
            output[index++] = node->value;
            node = node->right;
        } else {
            pre = node->left;
            while (pre->right != nullptr && pre->right != node)
                pre = pre->right;

            if (pre->right == nullptr) {
                pre->right = node;
                node = node->left;
            }
            else {
                pre->right = nullptr;
                output[index++] = node->value;
                node = node->right;
            }
        }

    }
}

std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> find_team(std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> root, int id);

std::shared_ptr<Node<std::shared_ptr<Player>, PlayerById>> find_player_by_id(std::shared_ptr<Node<std::shared_ptr<Player>, PlayerById>> root, int id);

template <class Cond>
std::shared_ptr<Node<std::shared_ptr<Player>, PlayerById>> find_player_by_cond(std::shared_ptr<Node<std::shared_ptr<Player>, Cond>> root, std::shared_ptr<Node<std::shared_ptr<Player>,
        Cond>> player);


bool isLegal(std::shared_ptr<Team>& team, std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> legal_teams_r) // do we need to add this team to legal team
{
    if( team -> getNumPlayers() < 11 || team -> getGoalKeepers() < 1)
    {
        return false;
    }

    std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> t = find_team(legal_teams_r, team -> getId());

    if ( t != nullptr)
        return false;

    return true;
}

template <class S, class Cond>
void delete_tree(AVLTree<std::shared_ptr<S>, Cond> t);



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
        Node<std::shared_ptr<Team>, TeamById> to_add(team_to_add);

        allTeams.r = allTeams.insert(allTeams.r, to_add);

        //std::cout <<allTeams.r->value.use_count()<< std::endl;
        //print2D(allTeams.r, 5);
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
        std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> team_to_remove = find_team(allTeams.r, teamId);
        if (team_to_remove == nullptr || allTeams.height(allTeams.r) == -1 || team_to_remove->value->getNumPlayers() > 0)
            return StatusType::FAILURE;

        std::shared_ptr<Team> team = team_to_remove->value;

        legalTeams.r = legalTeams.deleteNode(legalTeams.r, team_to_remove->value);
        allTeams.r = allTeams.deleteNode(allTeams.r, team_to_remove->value);

        //team_to_remove = nullptr;
        team.reset();
    }

    catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }

    //print2D(allTeams.r, 5);

    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper) {
    if ((playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || goals < 0 || cards < 0)
        || (gamesPlayed == 0 && (goals > 0 || cards > 0))) {
        return StatusType::INVALID_INPUT;
    }
    // if there is a player with this ID or teamId does not exist //

    try {
        std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> team = find_team(allTeams.r, teamId);

        if((find_player_by_id(allPlayers.r, playerId) != nullptr) || team == nullptr){
            return StatusType::FAILURE;
        }

        std::shared_ptr<Player> player_to_add(new Player(playerId, teamId, gamesPlayed, goals, cards, goalKeeper, team->value));

        Node<std::shared_ptr<Player>, PlayerById> player_by_id(player_to_add);
        Node<std::shared_ptr<Player>, PlayerByRank> player_by_rank(player_to_add);
        Node<std::shared_ptr<Player>, PlayerByGoals> player_by_goals(player_to_add);

        allPlayers.r = allPlayers.insert(allPlayers.r, player_by_id);
        playersByRank.r = playersByRank.insert(playersByRank.r, player_by_rank);
        playersByGoals.r = playersByGoals.insert(playersByGoals.r, player_by_goals);

        team->value->addPlayer(player_by_id.value);

        if (playersByGoals.r == nullptr)
            topPlayer = player_by_goals.value;

        // check if the new player is the new top player //
        if (playersByGoals.maxValueNode(playersByGoals.r) -> value -> get_id() == player_by_goals.value->get_id()){
            topPlayer = player_by_goals.value;
        }

        if (isLegal(team-> value, legalTeams.r)) {
            legalTeams.r = legalTeams.insert(legalTeams.r, team->value);

            //team->value->find_pre_post(allTeams.r, team->value, pre_team, post_team);
            team->value->calc_neighbors(allTeams.r, team->value);
        }

        PlayerByRank cond = PlayerByRank();
        std::shared_ptr<Node<std::shared_ptr<Player>, PlayerByRank>> pre = nullptr, post = nullptr;
        player_by_rank.value->find_pre_post(playersByRank.r, player_by_rank.value, pre, post, cond);
        player_by_rank.value->calc_closest(playersByRank.r, player_by_rank.value);

        if (pre != nullptr && pre->value!= nullptr)
            pre->value->calc_closest(playersByRank.r, pre->value);

        if (post != nullptr && post->value != nullptr)//////////////////////////////////////////////
            post->value->calc_closest(playersByRank.r, post->value);

    }
    catch(std::exception &e){
        return StatusType::ALLOCATION_ERROR;
    }

    numPlayers += 1;
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId){
    if (playerId <= 0)
        return StatusType::INVALID_INPUT;

    try{
        if (allPlayers.height(allPlayers.r) == -1)
            return StatusType::FAILURE;

        std::shared_ptr<Node<std::shared_ptr<Player>, PlayerById>> player_to_remove = find_player_by_id(allPlayers.r, playerId);

        if (player_to_remove == nullptr) {
            return StatusType::FAILURE;
        }

        std::shared_ptr<Player> player = player_to_remove->value;

        //remove from ranking tree
        playersByRank.deleteNode(playersByRank.r, player_to_remove->value);

        //remove from goals tree
        playersByGoals.r = playersByGoals.deleteNode(playersByGoals.r, player_to_remove->value);

        //if needed, replace the top player with the second best
        if (topPlayer->get_id() == player_to_remove->value->get_id()){
            if (playersByGoals.r == nullptr)
                topPlayer = nullptr;

            else
                topPlayer = (playersByGoals.maxValueNode(playersByGoals.r)->value);
        }

        std::shared_ptr<Team> team = player_to_remove -> value -> get_team();
        player_to_remove->value->get_team()->removePlayer(player_to_remove->value);

        player_to_remove->value->get_team().reset();


        //remove from the main players tree
        allPlayers.r = allPlayers.deleteNode(allPlayers.r, player_to_remove->value);

        player.reset();

        if(!isLegal(team, legalTeams.r)) {
            legalTeams.r = legalTeams.deleteNode(legalTeams.r, team);
            team->update_neighbors();
        }
    }

    catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }

    numPlayers -= 1;
    return StatusType::SUCCESS;

}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed, int scoredGoals, int cardsReceived){
    if (playerId <= 0 || gamesPlayed < 0 || scoredGoals < 0 || cardsReceived < 0)
        return StatusType::INVALID_INPUT;

    try {
        std::shared_ptr<Node<std::shared_ptr<Player>, PlayerById>> player_to_update = find_player_by_id(allPlayers.r, playerId);
        if (player_to_update == nullptr)
            return StatusType::FAILURE;

        player_to_update->value->update_player_stats(gamesPlayed, scoredGoals, cardsReceived);
        int team_id = player_to_update->value->get_team()->getId();
        int games = player_to_update->value->get_games_played();
        int cards = player_to_update->value->get_cards();
        int goals = player_to_update->value->get_goals();
        bool goal_k = player_to_update->value->is_goalKeeper();

        remove_player(playerId);
        add_player(playerId, team_id, games, goals, cards, goal_k);
    }
    catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
        return StatusType::INVALID_INPUT;

    // check if teams can play
    try {
        std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> team1 = find_team(legalTeams.r, teamId1);
        std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> team2 = find_team(legalTeams.r, teamId2);
        if (team1 == nullptr || team2 == nullptr) {
            return StatusType::FAILURE; }
        int team1_points = ( team1 -> value -> getPoints() )
                + (( team1 -> value -> getTotalGoals()) - (team1 -> value -> getTotalCards()));
        int team2_points = ( team2 -> value -> getPoints() )
                + (( team2 -> value -> getTotalGoals()) - (team2 -> value -> getTotalCards()));
         //there is a tie
        if (team1_points == team2_points){
            team1 -> value -> setPoints((team1 -> value -> getPoints()) + 1);
            team2 -> value -> setPoints((team2 -> value -> getPoints()) + 1);
        }

        // team1 won
        if (team1_points > team2_points){
            team1 -> value -> setPoints((team1 -> value -> getPoints()) + 3);
        }
        else {
            team2 -> value -> setPoints((team2 -> value -> getPoints()) + 3);
        }

        team1 -> value ->setMatches( team1-> value -> getMatches() + 1);
        team2 -> value ->setMatches( team2-> value -> getMatches() + 1);
    }
    catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }

    // add 1 to gamesPlayed of players

    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId){
    if (playerId <= 0)
        return output_t<int>(StatusType::INVALID_INPUT);

    try {
        std::shared_ptr<Node<std::shared_ptr<Player>, PlayerById>> player = find_player_by_id(allPlayers.r, playerId);

        if (player == nullptr)
            return output_t<int>(StatusType::FAILURE);

        return output_t<int>(player->value->get_games_played() + player->value->get_team()->getMatches() - player->value->get_games_played_fix());

    } catch (std::exception &e)
    { return output_t<int>(StatusType::ALLOCATION_ERROR); }
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId <= 0)
        return output_t<int>(StatusType::INVALID_INPUT);
    try{
        std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> t = find_team(allTeams.r , teamId);
        if (t == nullptr)
            return output_t<int>(StatusType::FAILURE);

        return output_t<int>(t -> value -> getPoints());

    }catch (std::exception &e)
    { return output_t<int>(StatusType::ALLOCATION_ERROR); }
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId) {
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2 || newTeamId <= 0)
        return StatusType::INVALID_INPUT;

    //=nullptr so we can use delete[] later
    std::shared_ptr<Player> *team1_array_id = nullptr;
    std::shared_ptr<Player> *team2_array_id = nullptr;
    std::shared_ptr<Player> *players_array_id = nullptr;

    //arrays for AVLTree by rank
    std::shared_ptr<Player> *team1_array_r = nullptr;
    std::shared_ptr<Player> *team2_array_r = nullptr;
    std::shared_ptr<Player> *players_array_r = nullptr;

    //arrays for AVLTree by goals
    std::shared_ptr<Player> *team1_array_g = nullptr;
    std::shared_ptr<Player> *team2_array_g = nullptr;
    std::shared_ptr<Player> *players_array_g = nullptr;

    try {
        std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> team1 = find_team(allTeams.r, teamId1);
        std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> team2 = find_team(allTeams.r, teamId2);
        std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> team_n = find_team(allTeams.r, newTeamId);

        //print2D(team1->value->getPlayersByGoals().r, 5);

        if (team1 == nullptr || team2 == nullptr || (team_n != nullptr && newTeamId != teamId1 && newTeamId != teamId2))
            return StatusType::FAILURE;

        int count1 = get_all_players_count(team1->value->getId()).ans();// size of team1
        int count2 = get_all_players_count((team2->value->getId())).ans();// size of team2

        //arrays for AVLTree by id
        team1_array_id = new std::shared_ptr<Player>[count1];
        team2_array_id = new std::shared_ptr<Player>[count2];
        players_array_id = new std::shared_ptr<Player>[count1 + count2];

        //arrays for AVLTree by rank
        team1_array_r = new std::shared_ptr<Player>[count1];
        team2_array_r = new std::shared_ptr<Player>[count2];
        players_array_r = new std::shared_ptr<Player>[count1 + count2];

        //arrays for AVLTree by goals
        team1_array_g = new std::shared_ptr<Player>[count1];
        team2_array_g = new std::shared_ptr<Player>[count2];
        players_array_g = new std::shared_ptr<Player>[count1 + count2];

        //fill the large arrays
        fillInorder(team1->value->getPlayersById().r, team1_array_id);
        fillInorder(team2->value->getPlayersById().r, team2_array_id);

        fillInorder(team1->value->getPlayersByRank().r, team1_array_r);
        fillInorder(team2->value->getPlayersByRank().r, team2_array_r);

        fillInorder(team1->value->getPlayersByGoals().r, team1_array_g);
        fillInorder(team2->value->getPlayersByGoals().r, team2_array_g);


        // merge
        PlayerById by_id = PlayerById();
        PlayerByGoals by_goals = PlayerByGoals();
        PlayerByRank by_rank = PlayerByRank();
        merge(team1_array_id, count1, team2_array_id, count2, players_array_id, by_id);
        merge(team1_array_r, count1, team2_array_r, count2,players_array_r, by_rank);
        merge(team1_array_g, count1, team2_array_g, count2, players_array_g, by_goals);

        //build new trees
        std::shared_ptr<Node<std::shared_ptr<Player>, PlayerById>> root_by_id = buildTree(players_array_id, 0, count1 + count2 -1, by_id);
        std::shared_ptr<Node<std::shared_ptr<Player>, PlayerByRank>> root_by_rank = buildTree(players_array_r, 0, count1 + count2 -1, by_rank);
        std::shared_ptr<Node<std::shared_ptr<Player>, PlayerByGoals>> root_by_goals = buildTree(players_array_g, 0, count1 + count2 -1, by_goals);

        //save fields for the united team
        int matches;
        int points = team1 -> value -> getPoints() + team2 -> value -> getPoints();
        int num_players = team1 -> value -> getNumPlayers() + team2 -> value ->getNumPlayers();
        int goalsKeepers = team1 -> value -> getGoalKeepers() + team2 -> value -> getGoalKeepers();
        int total_goals = team1 -> value -> getTotalGoals() + team2 -> value -> getTotalGoals();
        int total_cards = team1 -> value -> getTotalCards() + team1 -> value -> getTotalCards();
        std::shared_ptr<Player> topScorer;

        if (by_rank(team1 -> value -> getTopPlayer(), team2 -> value -> getTopPlayer()))
            topScorer = team2 -> value -> getTopPlayer();
        else
            topScorer = team1 -> value -> getTopPlayer();

        // unite team 1 <----- team2
        if (teamId1 == newTeamId){
            matches = team1 -> value -> getMatches();

            for (int i = 0; i< count2; i++){  // players in team2 games_played update
                team2_array_id[i] -> setTeamId(teamId1);
                team2_array_id[i] -> set_games_played(team2 -> value -> getMatches() - team2_array_id[i] -> get_games_played_fix());
                team2_array_id[i] -> set_games_played_fix(team1 -> value -> getMatches() - team2_array_id[i] -> get_games_played());
            }
        }
        // unite team2 <------ team1
        else if (teamId2 == newTeamId) {
            matches = team2 -> value -> getMatches();

            for (int i = 0; i < count1; i++){  // players in team1 games_played update
                team1_array_id[i] -> setTeamId(teamId2);
                team1_array_id[i] -> set_games_played(team1 -> value -> getMatches() - team1_array_id[i] -> get_games_played_fix());
                team1_array_id[i] -> set_games_played_fix( team2 -> value -> getMatches() - team1_array_id[i] -> get_games_played());
            }
        }
        // unite to newTeamId
        else {
            matches = 0;

            for (int i = 0; i< count2; i++){  // players in team2 games_played update
                team2_array_id[i] -> setTeamId(newTeamId);
                team2_array_id[i] -> set_games_played(team2 -> value -> getMatches() - team2_array_id[i] -> get_games_played_fix());
                team2_array_id[i] -> set_games_played_fix(0 - team2_array_id[i] -> get_games_played());
            }

            for (int i = 0; i < count1; i++){  // players in team1 games_played update
                team1_array_id[i] -> setTeamId(newTeamId);
                team1_array_id[i] -> set_games_played(team1 -> value -> getMatches() - team1_array_id[i] -> get_games_played_fix());
                team1_array_id[i] -> set_games_played_fix(0 - team1_array_id[i] -> get_games_played());
            }
        }

        remove_team(teamId1);
        remove_team(teamId2);
        add_team(newTeamId, points);

        std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> newTeam = find_team(allTeams.r, newTeamId);
        newTeam->value->getPlayersById().r = root_by_id;
        newTeam->value->getPlayersByRank().r = root_by_rank;
        newTeam->value->getPlayersByGoals().r = root_by_goals;
        newTeam -> value -> updateTeamStats(num_players, goalsKeepers, matches, total_goals, total_cards);


        if (isLegal(newTeam->value, legalTeams.r)){
            legalTeams.insert(legalTeams.r, newTeam->value);
            newTeam->value->calc_neighbors(legalTeams.r, newTeam->value);//find closest
        }

        for (int i = 0; i < count1 + count2; ++i) {
            players_array_id[i]->set_team(newTeam->value);
        }

        //print2D(newTeam->value->getPlayersById().r, 5);

    }
    catch (std::exception &e) {
        delete[] team1_array_id;
        delete[] team2_array_id;
        delete[] players_array_id;

        delete[] team1_array_r;
        delete[] team2_array_r;
        delete[] players_array_r;

        delete[] team1_array_g;
        delete[] team2_array_g;
        delete[] players_array_g;

        return StatusType::ALLOCATION_ERROR;
    }

    delete[] team1_array_id;
    delete[] team2_array_id;
    delete[] players_array_id;

    delete[] team1_array_r;
    delete[] team2_array_r;
    delete[] players_array_r;

    delete[] team1_array_g;
    delete[] team2_array_g;
    delete[] players_array_g;

    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId) {
    //print2D(playersByGoals.r, 5);
    if (teamId == 0)
        return output_t<int>(StatusType::INVALID_INPUT);

    if (teamId < 0){
        if (numPlayers == 0)
            return output_t<int>(StatusType::FAILURE);

        return output_t<int>(topPlayer->get_id());
    }

    std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> team = find_team(allTeams.r, teamId);
    if (team == nullptr || team->value->getNumPlayers() == 0)
        return output_t<int>(StatusType::FAILURE);

    return output_t<int>(team->value->getTopPlayerId());
}

output_t<int> world_cup_t::get_all_players_count(int teamId){
    if (teamId == 0)
        return output_t<int>(StatusType::INVALID_INPUT);

    if (teamId < 0) {
        return output_t<int>(numPlayers);
    }

    std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> team = find_team(allTeams.r, teamId);
    if (team == nullptr)
        return output_t<int>(StatusType::FAILURE);

    return output_t<int>(team->value->getNumPlayers());
}

StatusType world_cup_t::get_all_players(int teamId, int *const output) {
    if (teamId == 0 || output == nullptr)
        return StatusType::INVALID_INPUT;

    int *players_array;

    try {
        if (teamId < 0) {
            if(numPlayers == 0)
                return StatusType::FAILURE;

            int count = get_all_players_count(-1).ans();
             players_array = new int[count];

            printInorder(allPlayers.r, players_array);
        }

        else {
            std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> team = find_team(allTeams.r, teamId);
            if (team == nullptr || team->value->getNumPlayers() == 0)
                return StatusType::FAILURE;

            int count = get_all_players_count(team->value->getId()).ans();
            players_array = new int[count];

            printInorder(team->value->getPlayersByRank().r, players_array);

            for (int i = 0; i < count; ++i) {
                output[i] = players_array[i];
            }
        }
    }

    catch (std::exception& e){
        delete[] players_array;

        return StatusType::ALLOCATION_ERROR;
    }

    delete[] players_array;
    return StatusType::SUCCESS;
}// test

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId) {
    if (playerId <= 0 || teamId <= 0) {
        output_t<int> res = output_t<int>(StatusType::INVALID_INPUT);
        return res;
    }

    try {
        std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> team = find_team(allTeams.r, teamId);
        std::shared_ptr<Node<std::shared_ptr<Player>, PlayerById>> player = find_player_by_id(team->value->getPlayersById().r, playerId);

        if (player == nullptr || team == nullptr || player->value->get_team() == nullptr || player->value->get_team()->getId() != teamId) {
            return output_t<int>(StatusType::FAILURE);
        }

        int closest = player->value->get_closest();

        if (closest == 0)
            return output_t<int>(StatusType::FAILURE);

        return output_t<int>(closest);
    }
    catch (std::exception &e) {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId) {
    if (minTeamId < 0 || maxTeamId < 0 || maxTeamId < minTeamId)
        return output_t<int>(StatusType::INVALID_INPUT);
    int count = 0;
    std::shared_ptr<Team> team_in_range = find_in_range(legalTeams.r, minTeamId, maxTeamId);
    if (team_in_range == nullptr) {
        return output_t<int>(StatusType::FAILURE);
    }
    std::shared_ptr<Team> temp = team_in_range;
    while (temp -> get_prev() != nullptr && temp -> get_prev() -> getId() > minTeamId) {
        temp = temp -> get_prev();
        count++;
    }
    temp = team_in_range;
    while (temp -> get_next() != nullptr && temp -> get_next() -> getId() < maxTeamId){
        temp = temp -> get_next();
        count++;
    }

    LTeam* tournament;

    try{
        tournament = new LTeam[count];
        for (int i = 0; i < count; ++i) {
            tournament[i].setPoints(temp->getPoints() + temp->getTotalGoals() - temp->getTotalCards());
            tournament[i].setTeamId(temp->getId());
            temp = temp -> get_prev();
        }

        LTeam winning_team = winner(tournament, count);

        delete[] tournament;

        return output_t<int>(winning_team.getTeamId());
    }
    catch(std::exception& e){
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }
}

LTeam winner(LTeam tournament[], int size){
    if (size == 1)
        return tournament[0];

    for (int i = 0; i < size - 1*(size%2); i += 2) {
        tournament[i].setPoints(tournament[i].getPoints() + tournament[i + 1].getPoints() + 3);

        if(tournament[i].getPoints() < tournament[i+1].getPoints()) {
            tournament[i].setTeamId(tournament[i+1].getTeamId());
        }

        else if(tournament[i].getPoints() == tournament[i+1].getPoints()){
            if (tournament[i].getTeamId() < tournament[i+1].getTeamId())
                tournament[i].setTeamId(tournament[i+1].getTeamId());
        }
    }

    LTeam* smaller_tournament = new LTeam[size/2 + 1*(size%2)];
    for (int i = 0; i < size/2; ++i) {
        smaller_tournament[i] = tournament[i*2];
    }
    if (size%2 == 1)
        smaller_tournament[size/2] = tournament[size-1];

    return winner(smaller_tournament, size/2 + 1*(size%2));

    delete[] smaller_tournament;
}

template <class S, class Cond>
void delete_tree(AVLTree<std::shared_ptr<S>, Cond> t){
    t.r.reset();
    //while (t.r != nullptr){
    //    t.deleteNode(t.r, t.r -> value);
    //}
}

//Team*
std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> find_team(std::shared_ptr<Node<std::shared_ptr<Team>, TeamById>> root, int id){
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

std::shared_ptr<Node<std::shared_ptr<Player>, PlayerById>> find_player_by_id(std::shared_ptr<Node<std::shared_ptr<Player>, PlayerById>> root, int id) {
    if (root == nullptr) {
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

    if (root == nullptr || root->value == nullptr) {
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