#ifndef BINARYTREE_H
#define BINARYTREE_H

struct BST {
    struct BST_node *root;
};

struct BST_node {
    int value;
    struct BST_node *left;
    struct BST_node *right;
};

struct BST* newBST();
static struct BST_node* newNode(int value);
int insert(struct BST *tree, int value);
struct BST_node* find(struct BST *tree, int value);
void delete(struct BST *tree, int value);
void printPLR(struct BST_node* root);
void printLPR(struct BST_node* root);
void printLRP(struct BST_node* root);

#endif //BINARYTREE_H