#include "worldcup2a2.h"
#include <string>
#include <iostream>

using namespace std;

void print(string cmd, StatusType res);
void print(string cmd, output_t<int> res);
void query_get_all_players(string cmd, world_cup_t *obj, int teamID);

int main()
{
    cin >> std::boolalpha;

    int d1, d2, d3, d4, d5;
    bool b1;

    // Init
    world_cup_t *obj = new world_cup_t();

    // Execute all commands in file
    string op;
    while (cin >> op) {
        if (!op.compare("add_team")) {
            cin >> d1 >> d2;
            print(op, obj->add_team(d1, d2));

        } else if (!op.compare("remove_team")) {
            cin >> d1;
            print(op, obj->remove_team(d1));
        } else if (!op.compare("add_player")) {
            cin >> d1 >> d2 >> d3 >> d4 >> d5 >> b1;
            print(op, obj->add_player(d1, d2, d3, d4, d5, b1));
        } else if (!op.compare("remove_player")) {
            cin >> d1;
            print(op, obj->remove_player(d1));
        }
    }


    // Quit
    delete obj;
    return 0;
}

// Helpers
static const char *StatusTypeStr[] =
        {
                "SUCCESS",
                "ALLOCATION_ERROR",
                "INVALID_INPUT",
                "FAILURE"
        };

void print(string cmd, StatusType res)
{
    cout << cmd << ": " << StatusTypeStr[(int) res] << endl;
}

void print(string cmd, output_t<int> res)
{
    if (res.status() == StatusType::SUCCESS) {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << ", " << res.ans() << endl;
    } else {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << endl;
    }
}

void query_get_all_players(string cmd, world_cup_t *obj, int teamID)
{
    output_t<int> count = obj->get_all_players_count(teamID);
    // Allocate if okay
    int *out_mem = nullptr;
    if (count.status() == StatusType::SUCCESS && (count.ans() > 0)) {
        out_mem = new int[count.ans()];
        for (int i = 0; i < count.ans(); ++i) out_mem[i] = -1;
    }
    // Call function
    StatusType status = obj->get_all_players(teamID, out_mem);
    print(cmd, status);
    if (status == StatusType::SUCCESS) {
        for (int i = 0; i < count.ans(); ++i)
        {
            cout << out_mem[i] << endl;
        }
    }
    delete[] out_mem;
}


/* #include <iostream>
#include "AVLTree.h"
#include "worldcup23a1.h"

class Player;

int main() {
    //world_cup_t t();

    /*AVLTree<int> test;
    Node<int>* n1 = new Node<int, >(5);
    Node<int>* n2 = new Node<int>(3);
    Node<int>* n3 = new Node<int>(8);
    Node<int>* n4 = new Node<int>(9);

    test.insert(test.r, n1);
    test.insert(test.r, n2);
    test.insert(test.r, n3);
    test.insert(test.r, n4); */


    /*while (1){
        std::cout << "height of tree before removal: " << test.height(test.r) << std::endl;
        test.print2D(test.r, 5);
        std::cout << "--------------------------------------------------------- root value: " << test.r->value <<
        std::endl;

        if (test.r->right == nullptr && test.r->left == nullptr){
            delete test.r;
            test.r = nullptr;
            std::cout << test.height(test.r);
            break;
        }


        else if (test.r->right == nullptr){
            int v =  }test.r->left->value;
            test.deleteNode(test.r, v);
            test.r->value = v;
        }

        else if (test.r->left == nullptr){
            int v = test.r->right->value;
            test.deleteNode(test.r, v);
            test.r->value = v;
        }

        else
            test.deleteNode(test.r, test.r->value);
    }*/

