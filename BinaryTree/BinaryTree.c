#include<stdio.h>
#include<stdlib.h>
#include "BinaryTree.h"


static int hasLeft(struct BST_node *theNode){
    if(theNode ==NULL){
        return 0;
    }else{
        if(theNode->left != NULL){
            return 1;
        }else{
            return 0;
        }
    }
}

static int hasRight(struct BST_node *theNode){
    if(theNode ==NULL){
        return 0;
    }else{
        if(theNode->right != NULL){
            return 1;
        }else{
            return 0;
        }
    }
}

static struct BST_node* newNode(int value){
    struct BST_node* nd = malloc(sizeof(struct BST_node));

    if(nd != NULL){        
        nd->value = value;
        nd->left = NULL;
        nd->right = NULL;
    }else{
        printf("FAILED to allocate memory for new node.\n");
    }

    return nd;
}

struct BST* newBST(){
    struct BST* tree = malloc(sizeof(struct BST));

    if(tree != NULL){
        tree->root = NULL;
    }else{
        printf("FAILED to allocate memory for new BST.\n");
    }

    return tree;
}

struct BST_node* find(struct BST *tree, int value){
    
    if (tree->root == NULL){
        return NULL;
    }else{
        struct BST_node *curr_node = tree->root;

        while(curr_node != NULL){
            if(value == curr_node->value){
                return curr_node;
            }else if(value < curr_node->value){
                curr_node = curr_node->left;
            }else{
                curr_node = curr_node->right;
            }
        }
        free(curr_node);
        return NULL;
    }
}

int insert(struct BST *tree, int value){

    struct BST_node *new_node = newNode(value);

    if(new_node ==NULL){
        //printf("failed to allocate memory for new node. ABORTED\n");
        return 0;
    }

    //int hops=0;
    if (tree->root == NULL){
        tree->root = new_node;
        //printf("---------new root = %i\n", tree->root->value);
    }else{
        struct BST_node *curr_node = tree->root;
        while(1){
            //hops++;
            if(value <= curr_node->value){
                if(curr_node->left==NULL){//!hasLeft(curr_node)){
                    curr_node->left = new_node;
                    //printf("new node %i is left child of %i\n", new_node->value, curr_node->value);
                    break;
                }else{
                    curr_node = curr_node->left;   
                }
            }else{
                if(curr_node->right==NULL){//!hasRight(curr_node)){
                    curr_node->right = new_node;
                    //printf("new node %i is right child of %i\n", new_node->value, curr_node->value);
                    break;
                }else{
                    curr_node = curr_node->right;
                }
            }
        }
    }
    //printf("insertion of %i required %i hops.\n", value, hops);
    return 1;
}

static struct BST_node* FindMin(struct BST_node* root){
	while(!hasLeft(root->left)){
        root = root->left;
    }
	return root;
}

static struct BST_node* deleteStatic(struct BST_node *root, int value){
    if(root == NULL){
        return NULL;

    }else if(value < root->value){
        root->left = deleteStatic(root->left, value);

    }else if (value > root->value){
        root->right = deleteStatic(root->right, value);

    // Wohoo... I found you, Get ready to be deleted	
    }else {
        // Case 1:  No child
        if(root->left == NULL && root->right == NULL) { 
            free(root);
            root = NULL;
        }
        //Case 2a: One right child 
        else if(root->left == NULL) {
            //struct BST_node *temp = root;
            root = root->right;
            //free(temp);
        }
        //Case 2b: One left child 
        else if(root->right == NULL) {
            //struct BST_node *temp = root;
            root = root->left;
            //free(temp);
        }
        // case 3: 2 children
        else { 
            struct BST_node *temp = FindMin(root->right);
            root->value = temp->value;
            root->right = deleteStatic(root->right,temp->value);
        }
    }
	return root;
}

void delete(struct BST *tree, int value){

    if (tree->root == NULL){
        printf("tree is empty!\n");
    }else{
        tree->root = deleteStatic(tree->root, value);
    }

    return;
}

 void printPLR(struct BST_node* root){
    if(root == NULL){
        printf("EMPTY tree!\n");
    }else{            
        printf("%d\n", root->value);
        if(hasLeft(root)){
            printPLR(root->left);
        }
        if(hasRight(root)){
            printPLR(root->right);
        }
    }
}

 void printLPR(struct BST_node* root){
    if(root == NULL){
        printf("EMPTY tree!\n");
    }else{                    
        if(hasLeft(root)){
            printLPR(root->left);
        }
        printf("%d\n", root->value);

        if(hasRight(root)){
            printLPR(root->right);
        }
    }
}

 void printLRP(struct BST_node* root){
    if(root == NULL){
        printf("EMPTY tree!\n");
    }else{            
        if(hasLeft(root)){
            printLRP(root->left);
        }
        if(hasRight(root)){
            printLRP(root->right);
        }
        printf("%d\n", root->value);
    }
}