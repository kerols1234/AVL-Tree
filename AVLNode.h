#ifndef AVLNODE_H
#define AVLNODE_H

template<class T>
struct AVLNode {
    T key;
    AVLNode* left;
    AVLNode* right;

    AVLNode() {
        left = 0;
        right = 0;
    }

    AVLNode (T& val, AVLNode* l = 0, AVLNode* r = 0) : key(val), left(l), right(r) {
    }
};

#endif // AVLNODE_H

