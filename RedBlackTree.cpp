#include "RedBlackTree.h"

Node::Node(int val) : data(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}

RedBlackTree::RedBlackTree() : root(nullptr) {}

void RedBlackTree::leftRotate(Node *x)
{
    if (x == nullptr || x->right == nullptr)
        return;

    Node *y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(Node *y)
{
    if (y == nullptr || y->left == nullptr)
        return;

    Node *x = y->left;
    y->left = x->right;
    if (x->right != nullptr)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == nullptr)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void RedBlackTree::fixInsert(Node *z)
{
    while (z != root && z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            Node *y = z->parent->parent->right;
            if (y != nullptr && y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        }
        else
        {
            Node *y = z->parent->parent->left;
            if (y != nullptr && y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RedBlackTree::transplant(Node *u, Node *v)
{
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nullptr)
        v->parent = u->parent;
}

void RedBlackTree::deleteNode(Node *z)
{
    if (z == nullptr)
        return;

    Node *y = z;
    Node *x = nullptr;
    Color y_original_color = y->color;

    if (z->left == nullptr)
    {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == nullptr)
    {
        x = z->left;
        transplant(z, z->left);
    }
    else
    {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == z)
        {
            if (x != nullptr)
                x->parent = y;
        }
        else
        {
            if (x != nullptr)
                x->parent = y->parent;
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == BLACK && x != nullptr)
        fixDelete(x);

    delete z;
}

void RedBlackTree::fixDelete(Node *x)
{
    while (x != root && x != nullptr && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            Node *w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if ((w->left == nullptr || w->left->color == BLACK) &&
                (w->right == nullptr || w->right->color == BLACK))
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right == nullptr || w->right->color == BLACK)
                {
                    if (w->left != nullptr)
                        w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right != nullptr)
                    w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        }
        else
        {
            Node *w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if ((w->right == nullptr || w->right->color == BLACK) &&
                (w->left == nullptr || w->left->color == BLACK))
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left == nullptr || w->left->color == BLACK)
                {
                    if (w->right != nullptr)
                        w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left != nullptr)
                    w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    if (x != nullptr)
        x->color = BLACK;
}

Node *RedBlackTree::minimum(Node *node)
{
    while (node->left != nullptr)
        node = node->left;
    return node;
}

void RedBlackTree::insert(int val)
{
    Node *newNode = new Node(val);
    Node *y = nullptr;
    Node *x = root;

    while (x != nullptr)
    {
        y = x;
        if (newNode->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    newNode->parent = y;
    if (y == nullptr)
        root = newNode;
    else if (newNode->data < y->data)
        y->left = newNode;
    else
        y->right = newNode;

    fixInsert(newNode);
}

void RedBlackTree::remove(int val)
{
    Node *z = root;
    while (z != nullptr)
    {
        if (val < z->data)
            z = z->left;
        else if (val > z->data)
            z = z->right;
        else
        {
            deleteNode(z);
            return;
        }
    }
    std::cout << "Node with value " << val << " not found in the tree." << std::endl;
}

void RedBlackTree::printHelper(Node *root, int space)
{
    constexpr int COUNT = 5;
    if (root == nullptr)
        return;

    space += COUNT;
    printHelper(root->right, space);

    std::cout << std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout << " ";
    std::cout << root->data << "(" << ((root->color == RED) ? "RED" : "BLACK") << ")" << std::endl;

    printHelper(root->left, space);
}

void RedBlackTree::printTree()
{
    printHelper(root, 0);
}
