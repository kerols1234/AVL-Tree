#ifndef BINARYTREEFCI_H
#define BINARYTREEFCI_H
#include <iostream>
#include <queue>
#include <BSTNode.h>

using namespace std;

template  <class t>

class BinaryTreeFCI
{
    public:
        BinaryTreeFCI()
        {
            root = NULL;
        };
        ~BinaryTreeFCI()
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
            BSTNode<t> *newnode;
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
                queue<BSTNode<t>**> q;
                q.push(&root);
                while(!q.empty())
                {
                    if(*q.front() != NULL)
                    {
                        q.push(&(*q.front())->left);
                        q.push(&(*q.front())->right);
                        q.pop();
                    }
                    else
                    {
                        *q.front() = newnode;
                        break;
                    }
                }
            }
        };
        void postorderTraversal()
        {
            postorder(root);
            cout<<endl;
        };
        void flip(BSTNode<t> *node = nullptr)
        {
            if(node == nullptr)
            {
                printimage(root);
            }
            else
            {
                printimage(node);
            }
            cout<<endl;
        };
        void printmaxoflevel(queue<BSTNode<t>*> q1)
        {
            queue<BSTNode<t>*> q2;
            int Max = -1001;
            while(!q1.empty())
            {
                if(q1.front() != NULL)
                {
                    q2.push(q1.front()->left);
                    q2.push(q1.front()->right);
                    if(Max < q1.front()->item)
                        Max = q1.front()->item;
                }
                q1.pop();
            }
            if(!q2.empty())
            {
                cout<<Max<<" ";
                printmaxoflevel(q2);
            }
        }
        BSTNode<t>* getRoot()
        {
            return root;
        };
    protected:

    private:
        BSTNode<t> *root;
        void printimage(BSTNode<t> *p)
        {
            if(p != NULL)
            {
                printimage(p->right);
                printimage(p->left);
                cout<<p->item<<" ";
            }
        };
        void postorder(BSTNode<t> *p)
        {
            if(p != NULL)
            {
                postorder(p->left);
                postorder(p->right);
                cout<<p->item<<" ";
            }
        };
};

#endif // BINARYTREEFCI_H
