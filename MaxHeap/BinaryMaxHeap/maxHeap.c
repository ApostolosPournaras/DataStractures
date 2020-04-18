#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "maxHeap.h"

static int hasLeft(struct node *theNode){
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

static int hasRight(struct node *theNode){
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

struct MaxHeap* newMaxHeap(){
    return (struct MaxHeap*)malloc(sizeof(struct MaxHeap));
}

static struct node* newNode(int value, int priority){
    ////printf("newNode-1\n");
    struct node* nd = malloc(sizeof(struct node));
    //printf("newNode-2\n");

    if(nd != NULL){        
        nd->value = value;
        nd->priority = priority;
    }
    //printf("newNode-3\n");

    return nd;
}

static int height(int nodes_qty){
    return (int)floor(log2(nodes_qty))+1;
}

static int lvl_capacity(int lvl){
    return (int)pow(2,lvl);
}

static int tree_capacity(int height){
    return (int)pow(2,height)-1;
}

static int last_lvl_load(int qty, int height){
    return qty - tree_capacity(height-1);
}

static void heapify_up(struct node *theNode){
    if(theNode == NULL){
        return;
    }

    if(theNode->parent == NULL){
        return;
    }

    if(theNode->priority > theNode->parent->priority){
        
        int temp_value = theNode->value;
        int temp_priority = theNode->priority;

        //swap node with it's parent
        theNode->value = theNode->parent->value;
        theNode->priority = theNode->parent->priority;

        theNode->parent->value = temp_value;
        theNode->parent->priority = temp_priority;
        
        //printf("swapped node (%i, %i) with it's parent (%i, %i)\n", temp_value, temp_priority, theNode->value, theNode->priority);

        heapify_up(theNode->parent);
    }
}

int enqueue(struct MaxHeap *theHeap, int value, int priority){
    //printf("->enqueue %i with priority %i\n", value, priority);
    struct node* nd = newNode(value, priority);
    //printf("after node creation\n");

    if(nd == NULL){
        printf("FAILED to allocate memory for new node.\n");
        return 0;
    }

    //printf("before root check\n");
    if(theHeap->root == NULL){
        theHeap->root = nd;
        theHeap->nodes_qty++;
        //printf("  ->node (%i, %i) added as root, qty=%i\n", value, priority, theHeap->nodes_qty);
        return 1;
    }
    //printf("after root check\n");

    struct node* subTree_root = theHeap->root;
    int subTree_nodes_qty = theHeap->nodes_qty;
    int subTree_height = height(subTree_nodes_qty);
    //printf("after subTree_height\n");

    /*
    if load of last level of the original tree is equal to its capacity:
        final iteration when height of sub_tree is 1
    else:
        final iteration when height of sub_tree is 2
    */
    int height_to_check;
    if(last_lvl_load(subTree_nodes_qty, subTree_height) == lvl_capacity(subTree_height-1)){
        height_to_check = 1;
    }else{
        height_to_check = 2;
    }
    //printf("after height_to_check\n");

    //  printf("  load_of_last_lvl = %i\n", last_lvl_load(subTree_nodes_qty, subTree_height));
    //  printf("  capacity_of_last_lvl = %i\n", lvl_capacity(subTree_height-1));
    //  printf("  height_to_check = %i\n", height_to_check);
    //  printf("  subTree_height = %i\n", subTree_height);

    while(subTree_root != NULL && subTree_height > height_to_check){
        int last_level = subTree_height-1;
        // printf("    --------\n");
        // printf("    last_level = %i\n", last_level);
        int load_of_last_lvl = last_lvl_load(subTree_nodes_qty, subTree_height);
        // printf("    load_of_last_lvl = %i\n", load_of_last_lvl);
        int capacity_of_last_lvl = lvl_capacity(last_level);
        // printf("    capacity_of_last_lvl = %i\n", capacity_of_last_lvl);

        if(load_of_last_lvl >= 1 &&
           load_of_last_lvl <  capacity_of_last_lvl/2){
            // printf("      move to left sub-tree\n");
            //move to left sub-tree
            subTree_nodes_qty = subTree_nodes_qty - tree_capacity(subTree_height-2)-1;
            subTree_root = subTree_root->left;

        }else if(load_of_last_lvl >= capacity_of_last_lvl/2 &&
                 load_of_last_lvl <  capacity_of_last_lvl){
            // printf("      move to right sub-tree\n");
            //move to right sub-tree
            subTree_nodes_qty = subTree_nodes_qty - tree_capacity(subTree_height-1)-1;
            subTree_root = subTree_root->right;
            
        }else{
            // printf("      move to left sub-tree (else)\n");
            //when load == capacity
            //move to left sub-tree
            subTree_nodes_qty = subTree_nodes_qty - tree_capacity(subTree_height-1)-1;
            subTree_root = subTree_root->left;    
        }
        subTree_height -= 1;
        // printf("    subTree_height = %i\n", subTree_height);
    }

    if(!hasLeft(subTree_root)){
        subTree_root->left = nd;
        nd->parent = subTree_root;
        theHeap->nodes_qty++;
        // printf("  ->node (%i, %i) added as left child of (%i, %i)\n", value, priority, subTree_root->value, subTree_root->priority);
        heapify_up(nd);
        return 1;

    }else if(!hasRight(subTree_root)){
        subTree_root->right = nd;
        nd->parent = subTree_root;
        theHeap->nodes_qty++;
        // printf("  ->node (%i, %i) added as right child of (%i, %i)\n", value, priority, subTree_root->value, subTree_root->priority);
        heapify_up(nd);
        return 1;
    }else{
        // printf("  ->node (%i, %i) already has 2 children!!\n", subTree_root->value, subTree_root->priority);
        return 0;
    }
        
}

static void heapify_down(struct node *theNode){
    if(theNode == NULL){
        return;
    }
    
    if(!hasLeft(theNode) && !hasRight(theNode)){
        //we are in a leaf. no more actions are needed.
        return;

    }else if(hasLeft(theNode) && !hasRight(theNode)){
        //theNode only has a left child. take actions there
        if(theNode->priority < theNode->left->priority){
            
            int temp_value = theNode->value;
            int temp_priority = theNode->priority;

            //swap theNode with it's parent
            theNode->value = theNode->left->value;
            theNode->priority = theNode->left->priority;

            theNode->left->value = temp_value;
            theNode->left->priority = temp_priority;
            
            //printf("swapped node (%i, %i) with it's (only) left child (%i, %i)\n", temp_value, temp_priority, theNode->value, theNode->priority);

            heapify_down(theNode->left);
        }

    }else if(!hasLeft(theNode) && hasRight(theNode)){
        //theNode only has a right child. take actions there
        if(theNode->priority < theNode->right->priority){
            
            int temp_value = theNode->value;
            int temp_priority = theNode->priority;

            //swap theNode with it's parent
            theNode->value = theNode->right->value;
            theNode->priority = theNode->right->priority;

            theNode->right->value = temp_value;
            theNode->right->priority = temp_priority;
            
            //printf("swapped node (%i, %i) with it's (only) right child (%i, %i)\n", temp_value, temp_priority, theNode->value, theNode->priority);

            heapify_down(theNode->right);
        }
    }else{
        //theNode has both left and right child. compare their priorities and act accordingly
        struct node* child;
        //char child_str[5];

        if(theNode->left->priority > theNode->right->priority){
            child = theNode->left;
            // child_str[0] = 'l';
            // child_str[1] = 'e';
            // child_str[2] = 'f';
            // child_str[3] = 't';
            // child_str[4] = '\0';

        }else{
            child = theNode->right;
            // child_str[0] = 'r';
            // child_str[1] = 'i';
            // child_str[2] = 'g';
            // child_str[3] = 'h';
            // child_str[4] = 't';
            // child_str[5] = '\0';
        }

        if(theNode->priority < child->priority){
            
            int temp_value = theNode->value;
            int temp_priority = theNode->priority;

            //swap theNode with it's parent
            theNode->value = child->value;
            theNode->priority = child->priority;

            child->value = temp_value;
            child->priority = temp_priority;
            
            //printf("swapped node (%i, %i) with it's %s child (%i, %i)\n", temp_value, temp_priority, child_str, theNode->value, theNode->priority);

            heapify_down(child);
        }
    }
    return;
}

int pop(struct MaxHeap *theHeap, int* output){

    if(theHeap->root == NULL){        
        //printf("The Heap is empty!!\n");
        return 0;
    }

    struct node* subTree_root = theHeap->root;
    int subTree_nodes_qty = theHeap->nodes_qty;
    int subTree_height = height(subTree_nodes_qty);

    // printf("  load_of_last_lvl = %i\n", last_lvl_load(subTree_nodes_qty, subTree_height));
    // printf("  capacity_of_last_lvl = %i\n", lvl_capacity(subTree_height-1));
    // printf("  subTree_height = %i\n", subTree_height);
    // printf("  root's priority = %i\n", subTree_root->priority);

    while(subTree_height > 1){
        int last_level = subTree_height-1;
        //printf("    --------\n");
        //printf("    last_level = %i\n", last_level);
        int load_of_last_lvl = last_lvl_load(subTree_nodes_qty, subTree_height);
        //printf("    load_of_last_lvl = %i\n", load_of_last_lvl);
        int capacity_of_last_lvl = lvl_capacity(last_level);
        //printf("    capacity_of_last_lvl = %i\n", capacity_of_last_lvl);

        if(load_of_last_lvl >= 1 &&
           load_of_last_lvl <=  capacity_of_last_lvl/2){
            //printf("      move to left sub-tree\n");
            //move to left sub-tree
            subTree_nodes_qty = subTree_nodes_qty - tree_capacity(subTree_height-2)-1;
            subTree_root = subTree_root->left;

        }else if(load_of_last_lvl > capacity_of_last_lvl/2 &&
                 load_of_last_lvl <  capacity_of_last_lvl){
            //printf("      move to right sub-tree\n");
            //move to right sub-tree
            subTree_nodes_qty = subTree_nodes_qty - tree_capacity(subTree_height-1)-1;
            subTree_root = subTree_root->right;
            
        }else{
            //printf("      move to right sub-tree (else)\n");
            //when load == capacity
            //move to left sub-tree
            subTree_nodes_qty = subTree_nodes_qty - tree_capacity(subTree_height-1)-1;
            subTree_root = subTree_root->right;    
        }
        subTree_height--;
        //printf("    subTree_height = %i\n", subTree_height);
    }
    
    
    int return_value = theHeap->root->value;
    theHeap->root->value = subTree_root->value;
    theHeap->root->priority = subTree_root->priority;

    if(hasRight(subTree_root->parent)){
        if(subTree_root->parent->right->value == subTree_root->value && 
           subTree_root->parent->right->priority == subTree_root->priority){
            subTree_root->parent->right = NULL;
        }
    }else if(hasLeft(subTree_root->parent)){
        if(subTree_root->parent->left->value == subTree_root->value && 
           subTree_root->parent->left->priority == subTree_root->priority){
            subTree_root->parent->left = NULL;
        }
    }else{
        //printf("no children!! with root:(%i, %i)\n", theHeap->root->value, theHeap->root->priority);
    }

    theHeap->nodes_qty--;
    free(subTree_root);

    if(theHeap->nodes_qty>0){
        heapify_down(theHeap->root);
    }else{
        theHeap->root=NULL;
    }

    *output = return_value;   
    return 1;
}

int peek(struct MaxHeap *theHeap, int *output){
    if(theHeap->root == NULL){
        return 0;
    }else{
        *output = theHeap->root->value;
        return 1;
    }
}

int isEmpty(struct MaxHeap *theHeap){
    return (theHeap->nodes_qty==0 || theHeap->root==NULL);
}

static void printPLR_node_recursive(struct node* root){
    printf("%d\n", root->value);
    if(hasLeft(root)){
        printPLR_node_recursive(root->left);
    }
    if(hasRight(root)){
        printPLR_node_recursive(root->right);
    }
}

 void printPLR(struct MaxHeap *theHeap){
     struct node* root = theHeap->root;

     if(root == NULL){
        printf("EMPTY heap!\n");
    }else{  
        printPLR_node_recursive(root);
    }     
 }

static void printLPR_node_recursive(struct node* root){    
    if(hasLeft(root)){
        printLPR_node_recursive(root->left);
    }
    printf("%d\n", root->value);
    if(hasRight(root)){
        printLPR_node_recursive(root->right);
    }
}

 void printLPR(struct MaxHeap *theHeap){
     struct node* root = theHeap->root;

     if(root == NULL){
        printf("EMPTY heap!\n");
    }else{  
        printLPR_node_recursive(root);
    }     
 }

static void printLRP_node_recursive(struct node* root){    
    if(hasLeft(root)){
        printLRP_node_recursive(root->left);
    }    
    if(hasRight(root)){
        printLRP_node_recursive(root->right);
    }
    printf("%d\n", root->value);
}

 void printLRP(struct MaxHeap *theHeap){
     struct node* root = theHeap->root;

     if(root == NULL){
        printf("EMPTY heap!\n");
    }else{  
        printLRP_node_recursive(root);
    }     
 }