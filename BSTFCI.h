#ifndef BSTFCI_H
#define BSTFCI_H
#include <iostream>
#include <BSTNode.h>

using namespace std;
template  <class t>
class BSTFCI
{
    public:
        BSTFCI()
        {
            root = NULL;
        };
        ~BSTFCI()
        {
            cleardata(root);
        };
        void cleardata(BSTNode<t> *&cur)
        {
            if(cur != NULL)
            {
                cleardata(cur->left);
                cleardata(cur->right);
                delete cur;
                cur = NULL;
            }
        };
        void insertnode(t value)
        {
            BSTNode<t> *newnode, *cur, *bef;
            newnode = new BSTNode<t>();
            newnode->item = value;
            newnode->left = NULL;
            newnode->right = NULL;
            if(root == NULL)
            {
                root = newnode;
            }
            else
            {
                cur = root;
                while(cur != NULL)
                {
                    bef = cur;
                    if(cur->item == value)
                    {
                        cout<<"this value is already in the tree"<<endl;
                        cout<<"you can not enter two equal values"<<endl;
                        delete newnode;
                        return;
                    }
                    else if(cur->item > value)
                    {
                        cur = cur->left;
                    }
                    else
                    {
                        cur = cur->right;
                    }
                }
                if(bef->item > value)
                {
                    bef->left = newnode;
                }
                else
                {
                    bef->right = newnode;
                }
            }
        };
        bool searchOfNode(t value)
        {
            BSTNode<t> *cur;
            cur = root;
            while(cur != NULL)
            {
                if(cur->item == value)
                {
                    return true;
                }
                else if(cur->item > value)
                {
                    cur = cur->left;
                }
                else
                {
                    cur = cur->right;
                }
            }
            return false;
        };
        BSTNode<t>* searchOfNode(BSTNode<t> *p)
        {
            BSTNode<t> *cur;
            cur = root;
            while(cur != NULL)
            {
                if(cur->item == p->item)
                {
                    return cur;
                }
                else if(cur->item > p->item)
                {
                    cur = cur->left;
                }
                else
                {
                    cur = cur->right;
                }
            }
            return NULL;
        };
        t getMaxValue(BSTNode<t> *&Root, bool deleteNode)
        {
            t value;
            BSTNode<t> *cur, *bef = NULL;
            cur = Root;
            while(cur->right != NULL)
            {
                bef = cur;
                cur = cur->right;
            }
            value = cur->item;
            if(deleteNode)
            {
                if(bef != NULL)
                    bef->right = cur->left;
                else
                    Root = NULL;
                delete cur;
                cur = NULL;
            }
            return value;
        };
        t getMinValue(BSTNode<t> *&Root, bool deleteNode)
        {
            t value;
            BSTNode<t> *cur, *bef = NULL;
            cur = Root;
            while(cur->left != NULL)
            {
                bef = cur;
                cur = cur->left;
            }
            value = cur->item;
            if(deleteNode)
            {
                if(bef != NULL)
                    bef->left = cur->right;
                else
                    Root = NULL;
                delete cur;
                cur = NULL;
            }
            return value;
        };
        void postorderTraversal()
        {
            postorder(root);
            cout<<endl;
        };
        bool isBalance()
        {
            return isBalance(root);
        };
        int heightofnode(BSTNode<t> *node)
        {
            if(node == NULL)
            {
                return 0;
            }
            else if(node->left == NULL && node->right == NULL)
            {
                return 0;
            }
            else
            {
               return (1 + getmax(heightofnode(node->right), heightofnode(node->left)));
            }
        };
        int getmax(int x, int y)
        {
            if(x > y)
                return x;
            else
                return y;
        };
        void printRange(int x, int y)
        {
            cout<<"[ ";
            print(root,x,y);
            cout<<"]"<<endl;
        };
        BSTNode<t>* getRoot()
        {
            return root;
        };
        int pathofleaf(BSTNode<t> *p, int sum = 0)
        {
            if(p->left ==  NULL && p->right == NULL)
            {
                return ((sum*10)+p->item);
            }
            else if(p != NULL)
            {
                return (pathofleaf(p->left, (sum*10)+p->item) + pathofleaf(p->right, (sum*10)+p->item));
            }
            else
            {
                return (0);
            }
        };
    protected:

    private:
        BSTNode<t> *root;
        void postorder(BSTNode<t> *p)
        {
            if(p != NULL)
            {
                postorder(p->left);
                postorder(p->right);
                cout<<p->item<<" ";
            }
        };
        void print(BSTNode<t> *p, int x, int y)
        {
            if(p == NULL)
            {
                return;
            }
            else if(p->item >= x && p->item <= y)
            {
                print(p->left,x,y);
                cout<<p->item<<" ";
                print(p->right,x,y);
            }
            else if(p->item > y)
            {
                print(p->left,x,y);
            }
            else
            {
                print(p->right,x,y);
            }
        };
        bool isBalance(BSTNode<t> *p)
        {
            int x = heightofnode(root->left);
            int y = heightofnode(root->right);
            if(p == NULL)
                return true;
            else if ((x - y) < -1 || (x - y) > 1)
                return false;
            else
            {
                return (isBalance(p->left) && isBalance(p->right));
            }
        };
};

#endif // BSTFCI_H
