#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <bits/stdc++.h>
#include "AVLNode.h"

using std::cout;
using std::endl;
using std::queue;

template<class T>
class AVLTree {
private:
    AVLNode<T>* root;

public:

    // Constructor
    AVLTree() {
        root = 0;
    }

    // Search
    AVLNode<T>* getNode(AVLNode<T>* root, T key) {
        if (root == 0 || root->key == key) {
            return root;
        }

        if (root->key < key) {
            return getNode(root->right, key);
        }

        return getNode(root->left, key);
    }

    T* search(T key) {
        AVLNode<T>* found = getNode(root, key);
        if (!found) {
            return 0;
        }
        return &(found->key);
    }

    int max(int a, int b) {
        return a > b ? a : b;
    }

    int height(AVLNode<T>* root) {
        if (root == 0) {
            return 0;
        }
        return 1 + max(height(root->left), height(root->right));
    }

    AVLNode<T>* rightRotate(AVLNode<T>* node) {
        AVLNode<T>* l = node->left;
        AVLNode<T>* lr = l->right;
        l->right = node;
        node->left = lr;
        return l;
    }

    AVLNode<T>* leftRotate(AVLNode<T>* node) {
        AVLNode<T>* r = node->right;
        AVLNode<T>* rl = r->left;
        r->left = node;
        node->right = rl;
        return r;
    }

    int getBalance(AVLNode<T>* node) {
        if (node == 0) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    // Insertion
    AVLNode<T>* insert(AVLNode<T>* node, T key) {
        if (node == 0) {
            return new AVLNode<T>(key);
        }

        if (key < node->key) {
            node->left = insert(node->left, key);
        }
        else if (key > node->key) {
            node->right = insert(node->right, key);
        }
        else {
            return node;
        }

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key) {
            return rightRotate(node);
        }
        else if (balance < -1 && key > node->right->key) {
            return leftRotate(node);
        }
        else if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        else if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void insert(T key) {
        if (root == 0) {
            root = insert(root, key);
        }
        else {
            insert(root, key);
        }
    }

    // Deletion
    AVLNode<T>* maxNode(AVLNode<T>* node) {
        if (node->right == 0) {
            return node;
        }
        return maxNode(node->right);
    }


    AVLNode<T>* deleteNode(AVLNode<T>* root, T key) {
        if (root == NULL) {
            return root;
        }

        if (key < root->key) {
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->key) {
            root->right = deleteNode(root->right, key);
        }
        else {
            if (root->left == 0) {
                AVLNode<T>* tmp = root->right;
                delete root;
                return tmp;
            }
            else if (root->right == 0) {
                AVLNode<T>* tmp = root->left;
                delete root;
                return tmp;
            }
            else {
                AVLNode<T>* pred = maxNode(root->left);
                root->key = pred->key;
                root->left = deleteNode(pred, pred->key);
            }
        }

        if (root == 0)
            return root;

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0) {
            return rightRotate(root);
        }
        else if (balance > 1 && getBalance(root->left) < 0) {
            root->left =  leftRotate(root->left);
            return rightRotate(root);
        }
        else if (balance < -1 && getBalance(root->right) <= 0) {
            return leftRotate(root);
        }
        else if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void deleteNode(T key) {
        deleteNode(root, key);
    }

    // Traversal
    void preOrderTraversal(AVLNode<T>* node) {
        if (node != 0) {
            cout << node->key << endl;
            preOrderTraversal(node->left);
            preOrderTraversal(node->right);
        }
    }

    void inOrderTraversal(AVLNode<T>* node) {
        if (node != 0) {
            inOrderTraversal(node->left);
            cout << node->key << endl;
            inOrderTraversal(node->right);
        }
    }

    void postOrderTraversal(AVLNode<T>* node) {
        if (node != 0) {
            postOrderTraversal(node->left);
            postOrderTraversal(node->right);
            cout << node->key << endl;
        }
    }

    void BFS() {
        queue<AVLNode<T>* > q;

        if (root) {
          q.push(root);
          cout << root->key << " ";
        }
        else {
            cout << "NULL ";
        }

        cout << '\n';
        int level_count = 0;
        int pop_count = 0;

        while (!q.empty()) {
            AVLNode<T>* tmp = q.front();

            if (pop_count == pow(2, level_count)) {
                pop_count = 0;
                ++level_count;
                cout << endl;
            }

            q.pop();
            ++pop_count;

            if (tmp->left) {
              q.push(tmp->left);
              cout << tmp->left->key << " ";
            }
            else {
              cout << "NULL ";
            }

            if (tmp->right) {
              q.push(tmp->right);
              cout << tmp->right->key << " ";
            }
            else {
              cout << "NULL ";
            }
        }

        cout << endl;
    }

    // Verification
    bool isBalance(AVLNode<T>* root) {
        unsigned int lHeight;
        unsigned int rHeight;

        if(root == 0) {
            return 1;
        }

        lHeight = height(root->left);
        rHeight = height(root->right);
        if (abs(lHeight - rHeight) <= 1 && isBalance(root->left) && isBalance(root->right)) {
            return 1;
        }

        return 0;
    }

    bool isBalance() {
        return isBalance(root);
    }
};

#endif // AVLTREE_H
