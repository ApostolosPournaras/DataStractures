#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "listMaxHeap.h"

static int hasPrev(struct node *theNode){
    if(theNode ==NULL){
        return 0;
    }else{
        if(theNode->prev != NULL){
            return 1;
        }else{
            return 0;
        }
    }
}

static int hasNext(struct node *theNode){
    if(theNode ==NULL){
        return 0;
    }else{
        if(theNode->next != NULL){
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
    struct node* nd = malloc(sizeof(struct node));

    if(nd != NULL){        
        nd->value = value;
        nd->priority = priority;
    }

    return nd;
}

int enqueue(struct MaxHeap *theHeap, int value, int priority){
    //printf("->enqueue %i with priority %i\n", value, priority);
    struct node* new_nd = newNode(value, priority);

    if(new_nd == NULL){
        //printf("FAILED to add node (%i, %i)\n", value, priority);
        return 0;
    }

    if(theHeap->head == NULL){
        theHeap->head = new_nd;
        theHeap->tail = new_nd;
        theHeap->nodes_qty++;
        //printf("  ->node (%i, %i) added as root\n", value, priority);
        return 1;
    }

    struct node* curr_node = theHeap->head;

    while(curr_node != NULL){
        if(curr_node->priority < new_nd->priority && !hasNext(curr_node)){
            //add as new tail
            curr_node->next = new_nd;
            new_nd->prev = curr_node;            
            theHeap->tail = new_nd;
            //printf("  ->node (%i, %i) added as new tail\n", value, priority);
            break;

        }else if(curr_node->priority < new_nd->priority && hasNext(curr_node)){
            //check next node
            curr_node = curr_node->next;
            //printf("  ->node's (%i, %i) priority is lower than curr_node's priority (%i, %i). check next\n", value, priority, curr_node->value, curr_node->priority);

        }else if(curr_node->priority > new_nd->priority && !hasPrev(curr_node)){
            //add as new head
            curr_node->prev = new_nd;
            new_nd->next = curr_node;            
            theHeap->head = new_nd;
            //printf("  ->node (%i, %i) added as new head\n", value, priority);
            break;
            

        }else{
            // if(curr_node->priority > new_nd->priority && hasPrev(curr_node)
            //add before curr_node
            new_nd->prev = curr_node->prev;
            curr_node->prev->next = new_nd;
            new_nd->next = curr_node;
            curr_node->prev = new_nd;
            //printf("  ->node (%i, %i) added before (%i, %i) and after (%i, %i)\n", value, priority, new_nd->next->value, new_nd->next->priority,new_nd->prev->value, new_nd->prev->priority);
            break;
            
        }
    }

    theHeap->nodes_qty++;
    return 1;        
}

int pop(struct MaxHeap *theHeap, int* output){

    if(theHeap->tail == NULL){        
        //printf("The Heap is empty!!\n");
        return 0;
    }

    struct node* curr_tail = theHeap->tail;

    int return_value = curr_tail->value;

    if(theHeap->tail != theHeap->head){
        struct node* tail_prev = theHeap->tail->prev;
        theHeap->tail = tail_prev;
        theHeap->tail->next = NULL;
    }else{
        theHeap->head=NULL;
        theHeap->tail=NULL;
        //printf("last element to be poped!!\n");
    }

    theHeap->nodes_qty--;

    free(curr_tail);
    *output = return_value;
    return 1;
}

int peek(struct MaxHeap *theHeap, int *output){
    if(theHeap->tail == NULL){
        return 0;
    }else{
        *output = theHeap->tail->value;
        return 1;
    }
}

int isEmpty(struct MaxHeap *theHeap){
    return (theHeap->nodes_qty==0 && theHeap->head==NULL && theHeap->tail==NULL);
}

void printTailtoHead(struct MaxHeap *theHeap){
    struct node* cur_node = theHeap->tail;

    if(cur_node == NULL){
        printf("EMPTY heap!\n");
    }else{  
        printf("(%d,%d)", cur_node->value,cur_node->priority);
        while(hasPrev(cur_node)){
            cur_node = cur_node->prev;
            printf(" <- (%d,%d)", cur_node->value,cur_node->priority);
        }
    }
    printf("\n");
}

void printHeadtoTail(struct MaxHeap *theHeap){
    struct node* cur_node = theHeap->head;

    if(cur_node == NULL){
        printf("EMPTY heap!\n");
    }else{  
        printf("(%d,%d)", cur_node->value,cur_node->priority);
        while(hasNext(cur_node)){
            cur_node = cur_node->next;
            printf(" -> (%d,%d)", cur_node->value,cur_node->priority);
        }
    }
    printf("\n");
}