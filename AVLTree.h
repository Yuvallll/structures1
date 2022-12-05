#ifndef STRUCTURES1_AVLTREE_H
#define STRUCTURES1_AVLTREE_H
#include <iostream>
#include <memory>

#define SPACE 10

template <class T, class Cond>
class Node {
public:
    T value;
    Node<T, Cond>* left;
    Node<T, Cond>* right;

    Node(): value() {
        left = nullptr;
        right = nullptr;
    }

    Node(T t): value(t){
        left = nullptr;
        right = nullptr;
    }

};

template <class T, class Cond>
class AVLTree {
private:

public:
    Node<T, Cond>* r;

    AVLTree() {
        r = nullptr;
    }

    int height(Node<T, Cond>* t_node) const{
        if (t_node == nullptr)
            return -1;

        int lheight = height(t_node->left);
        int rheight = height(t_node->right);

        if (lheight > rheight)
            return (lheight + 1);
        else return (rheight + 1);
    }

    int getBalanceFactor(Node<T, Cond>* t_node) const{
        if (t_node == nullptr)
            return -1;
        return height(t_node -> left) - height(t_node -> right);
    }

    Node<T, Cond>* rightRotate(Node<T, Cond> * y) {
        Node<T, Cond> * x = y -> left;
        Node<T, Cond> * T2 = x -> right;

        // Perform rotation
        x -> right = y;
        y -> left = T2;

        return x;
    }

    Node<T, Cond>* leftRotate(Node<T, Cond> * x) {
        Node<T, Cond> * y = x -> right;
        Node<T, Cond> * T2 = y -> left;

        // Perform rotation
        y -> left = x;
        x -> right = T2;

        return y;
    }

    Node<T, Cond>* insert(Node<T, Cond>* root, Node<T, Cond>* new_node) {
        /*if (r == nullptr) {
            r = new_node;
            //cout << "Value inserted successfully" << endl;
            return r;
        }*/

        if (root == nullptr) {
            /// make new Node(!!) and insert the wanted value instead of using operator=
            root = new Node<T, Cond>;
            root -> value = new_node -> value;
            return root;
        }

        Cond c = Cond();
        if (c(new_node -> value, root -> value)) { //new_node -> value < root -> value
            root -> left = insert(root -> left, new_node);
        }

        else if (c(root -> value, new_node->value)) { //new_node -> value > root -> value
            root -> right = insert(root -> right, new_node);
        }
        else {
            // duplicate values, new_node -> value = root -> value
            return root;
        }

        int bf = getBalanceFactor(root);
        // Left Left Case
        if (bf > 1 && c(new_node->value, root->left->value)) //bf > 1 && new_node -> value < root -> left -> value
            return rightRotate(root);

        // Right Right Case
        if (bf < -1 && c(root->right->value, new_node->value)) //bf < -1 && new_node -> value > root -> right -> value
            return leftRotate(root);

        // Left Right Case
        if (bf > 1 && c(root->left->value, new_node->value)) { //bf > 1 && new_node -> value > root -> left -> value
            root -> left = leftRotate(root -> left);
            return rightRotate(root);
        }

        // Right Left Case
        if (bf < -1 && c(new_node->value, root->right->value)) {//bf < -1 && new_node -> value < root -> right
            // -> value
            root -> right = rightRotate(root -> right);
            return leftRotate(root);
        }

        /* return the (unchanged) node pointer */
        return root;

    }

    Node<T, Cond> * minValueNode(Node<T, Cond> * node) const{
        Node<T, Cond> * current = node;
        /* loop down to find the leftmost leaf */
        while (current -> left != nullptr) {
            current = current -> left;
        }
        return current;
    }

    Node<T, Cond>* deleteNode(Node<T, Cond>* root, T val) {
        Cond c = Cond();

        // base case
        if (root == nullptr) {
            return nullptr;
        }

            // If the key to be deleted is smaller than the root's key,
            // then it lies in left subtree
        else if (c(val, root->value)) { //val < root -> value
            root -> left = deleteNode(root -> left, val);
        }
            // If the key to be deleted is greater than the root's key,
            // then it lies in right subtree
        else if (c(root->value, val)) { //val > root -> value
            root -> right = deleteNode(root -> right, val);
        }
            // if key is same as root's key, then This is the node to be deleted
        else {
            // node with only one child or no child
            if (root -> left == nullptr) {
                Node<T, Cond> * temp = root -> right;
                delete root;
                return temp;
            }
            else if (root -> right == nullptr) {
                Node<T, Cond> * temp = root -> left;
                delete root;
                return temp;
            }
            else {
                // node with two children: Get the inorder successor (smallest
                // in the right subtree)
                Node<T, Cond> * temp = minValueNode(root -> right);
                // Copy the inorder successor's content to this node
                root -> value = temp -> value;
                // Delete the inorder successor
                root -> right = deleteNode(root -> right, temp -> value);
                //deleteNode(r->right, temp->value);
            }
        }

        int bf = getBalanceFactor(root);
        // Left Left Imbalance/Case or Right rotation
        if (bf == 2 && getBalanceFactor(root -> left) >= 0)
            return rightRotate(root);
            // Left Right Imbalance/Case or LR rotation
        else if (bf == 2 && getBalanceFactor(root -> left) == -1) {
            root -> left = leftRotate(root -> left);
            return rightRotate(root);
        }
            // Right Right Imbalance/Case or Left rotation
        else if (bf == -2 && getBalanceFactor(root -> right) <= -0)
            return leftRotate(root);
            // Right Left Imbalance/Case or RL rotation
        else if (bf == -2 && getBalanceFactor(root -> right) == 1) {
            root -> right = rightRotate(root -> right);
            return leftRotate(root);
        }

        return root;
    }

    void print2D(Node<T, Cond>* root, int space) {
        if (root == nullptr) // Base case  1
            return;
        space += SPACE; // Increase distance between levels   2
        print2D(root -> right, space); // Process right child first 3
        std::cout << std::endl;
        for (int i = SPACE; i < space; i++) // 5
            std::cout << " "; // 5.1
        std::cout << root -> value << "\n"; // 6
        print2D(root -> left, space); // Process left child  7
    }

  /*   bool is_exist(Node<T, Cond>* root, T val) const // T val is a ptr
    {
        if (root == nullptr) {
            return false;
        }

        Cond c1(val);
        Cond c2(root -> value);

        if (c1(root -> value)) { //val < root -> value
            root -> left = is_exist(root -> left, val);
        }
        else if (c2(val)) {  //val > root -> value
            root -> right = is_exist(root -> right, val);
        }
        else {
            //duplicate values
            return true;
        }
    }*/
};




#endif //STRUCTURES1_AVLTREE_H
