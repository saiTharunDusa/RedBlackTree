#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>

enum Color
{
    RED,
    BLACK
};

struct Node
{
    int data;
    Color color;
    Node *left;
    Node *right;
    Node *parent;

    explicit Node(int val);
};

class RedBlackTree
{
private:
    Node *root;

    void leftRotate(Node *x);
    void rightRotate(Node *y);
    void fixInsert(Node *z);
    void transplant(Node *u, Node *v);
    void deleteNode(Node *z);
    void fixDelete(Node *x);
    Node *minimum(Node *node);
    void printHelper(Node *root, int space);

public:
    Node *getMinimum()
    {
        return minimum(root);
    }
    RedBlackTree();
    void insert(int val);
    void remove(int val);
    void printTree();
};

#endif /* REDBLACKTREE_H */
