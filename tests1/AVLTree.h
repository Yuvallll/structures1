#ifndef STRUCTURES1_AVLTREE_H
#define STRUCTURES1_AVLTREE_H
#include <iostream>
#include <memory>

#define SPACE 10

template <class T, class Cond>
class Node {
public:
    T value;
    std::shared_ptr<Node<T, Cond>> left;
    std::shared_ptr<Node<T, Cond>> right;

    Node(): value() {
        left = nullptr;
        right = nullptr;
    }

    Node(T t) : value(t){
        left = nullptr;
        right = nullptr;
    }
};

template <class T, class Cond>
class AVLTree {
private:

public:
    std::shared_ptr<Node<T, Cond>> r;

    AVLTree() {
        r = nullptr;
    }

    int height(std::shared_ptr<Node<T, Cond>> t_node) const{
        if (t_node == nullptr)
            return -1;

        int lheight = height(t_node->left);
        int rheight = height(t_node->right);

        if (lheight > rheight)
            return (lheight + 1);
        else return (rheight + 1);
    }

    int getBalanceFactor(std::shared_ptr<Node<T, Cond>> t_node) const{
        if (t_node == nullptr)
            return -1;
        return height(t_node -> left) - height(t_node -> right);
    }

    std::shared_ptr<Node<T, Cond>> rightRotate(std::shared_ptr<Node<T, Cond>> y) {
        std::shared_ptr<Node<T, Cond>> x = y -> left;
        std::shared_ptr<Node<T, Cond>> T2 = x -> right;

        // Perform rotation
        x -> right = y;
        y -> left = T2;

        return x;
    }

    std::shared_ptr<Node<T, Cond>> leftRotate(std::shared_ptr<Node<T, Cond>> x) {
        std::shared_ptr<Node<T, Cond>> y = x -> right;
        std::shared_ptr<Node<T, Cond>> T2 = y -> left;

        // Perform rotation
        y -> left = x;
        x -> right = T2;

        return y;
    }

    std::shared_ptr<Node<T, Cond>> insert(std::shared_ptr<Node<T, Cond>> root, Node<T, Cond> new_node) {
        if (r == nullptr) {
            //r = new Node<T, Cond>;
            std::shared_ptr<Node<T, Cond>> ptr = std::shared_ptr<Node<T, Cond>>(new Node<T, Cond>(new_node));
            r = ptr;
            return r;
        }

        if (root == nullptr) {
            /// make new Node(!!) and insert the wanted value instead of using operator=
            //root = new Node<T, Cond>;
            std::shared_ptr<Node<T, Cond>> ptr = std::shared_ptr<Node<T, Cond>>(new Node<T, Cond>(new_node));
            root = ptr;
            return root;
        }

        Cond c = Cond();
        if (c(new_node.value, root->value)) { //new_node -> value < root -> value
            root->left = insert(root->left, new_node);
        }

        else if (c(root->value, new_node.value)) { //new_node -> value > root -> value
            root->right = insert(root->right, new_node);
        }
        else {
            // duplicate values, new_node -> value = root -> value
            return root;
        }

        int bf = getBalanceFactor(root);
        // Left Left Case
        if (bf > 1 && c(new_node.value, root->left->value)) //bf > 1 && new_node -> value < root -> left -> value
            return rightRotate(root);

        // Right Right Case
        if (bf < -1 && c(root->right->value, new_node.value)) //bf < -1 && new_node -> value > root -> right -> value
            return leftRotate(root);

        // Left Right Case
        if (bf > 1 && c(root->left->value, new_node.value)) { //bf > 1 && new_node -> value > root -> left -> value
            root -> left = leftRotate(root -> left);
            return rightRotate(root);
        }

        // Right Left Case
        if (bf < -1 && c(new_node.value, root->right->value)) {//bf < -1 && new_node -> value < root -> right
            // -> value
            root -> right = rightRotate(root -> right);
            return leftRotate(root);
        }

        /* return the (unchanged) node pointer */
        return root;
    }

    std::shared_ptr<Node<T, Cond>> minValueNode(std::shared_ptr<Node<T, Cond>> node) const{
        std::shared_ptr<Node<T, Cond>> current = node;
        /* loop down to find the leftmost leaf */
        while (current -> left != nullptr) {
            current = current -> left;
        }
        return current;
    }

    std::shared_ptr<Node<T, Cond>> maxValueNode(std::shared_ptr<Node<T, Cond>> node) const{
        std::shared_ptr<Node<T, Cond>> current = node;
        /* loop down to find the rightmost leaf */
        while (current -> right != nullptr) {
            current = current -> right;
        }
        return current;
    }

    std::shared_ptr<Node<T, Cond>> Delete(std::shared_ptr<Node<T, Cond>> root, T val) {
        Cond c = Cond();

        // base case (if node not found)
        if (root == nullptr) {
            return nullptr;
        }

            // If the key to be deleted is smaller than the root's key,
            // then it lies in left subtree
        else if (c(val, root->value)) { //val < root -> value
            root -> left = Delete(root -> left, val);
        }
            // If the key to be deleted is greater than the root's key,
            // then it lies in right subtree
        else if (c(root->value, val)) { //val > root -> value
            root -> right = Delete(root -> right, val);
        }
            // if key is same as root's key, then This is the node to be deleted
        else {
            // node with only one child or no child
            if (root -> left == nullptr) {
                std::shared_ptr<Node<T, Cond>> temp = root -> right;

                if (root->right == nullptr) {
                    root->value.reset();
                    //root = nullptr;
                }
                return temp;
            }
            else if (root -> right == nullptr) {
                std::shared_ptr<Node<T, Cond>> temp = root -> left;
                return temp;
            }
            else {
                // node with two children: Get the inorder successor (smallest
                // in the right subtree)
                std::shared_ptr<Node<T, Cond>> temp = minValueNode(root -> right);
                // Copy the inorder successor's content to this node
                root -> value = temp -> value;
                // Delete the inorder successor
                root -> right = Delete(root -> right, temp -> value);
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

   std::shared_ptr<Node<T, Cond>> deleteNode(std::shared_ptr<Node<T, Cond>> root, T val){
        if (root == nullptr)
            return nullptr;

        //tree with onl one node, which we want to remove
        else if (this->height(root) == 0 && r->left == nullptr && r->right == nullptr && root->value == val){
            root -> value.reset();
            r = nullptr;///changed from root = nullptr (we didn't initialize the original root)
            return nullptr;
        }

        else {
            return Delete(root, val);
        }
   }


    void print2D(std::shared_ptr<Node<T, Cond>> root, int space) {
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

  /*   bool is_exist(std::shared_ptr<Node<T, Cond>> root, T val) const // T val is a ptr
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
