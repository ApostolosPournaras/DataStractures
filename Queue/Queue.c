#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Queue.h"


static int hasNext(struct node *theNode){
    if(theNode == NULL){
        return 0;
    }else{
        if(theNode->next != NULL){
            return 1;
        }else{
            return 0;
        }
    }
}

struct Queue* newQueue(){
    return (struct Queue*)malloc(sizeof(struct Queue));
}

static struct node* newNode(int value){
    struct node* nd = malloc(sizeof(struct node));

    if(nd != NULL){        
        nd->value = value;
    }

    return nd;
}

int enqueue(struct Queue *theQueue, int value){
    //printf("->psuh %i\n", value);
    struct node* new_nd = newNode(value);

    if(new_nd == NULL){
        //printf("FAILED to push %i\n", value);
        return 0;
    }

    if(isEmpty(theQueue)){
        theQueue->last = new_nd;
        theQueue->first = new_nd;
    }else{
        new_nd->next = theQueue->last;
        theQueue->last->prev = new_nd;
        theQueue->last = new_nd;
    }
    
    theQueue->size++;
    //printf("  ->node (%i, %i) added as top\n", value);
    return 1;
}

int deQueue(struct Queue *theQueue, int* output){

    if(theQueue->first == NULL){        
        //printf("The Queue is empty!!\n");
        return 0;
    }
    
    struct node* curr_first = theQueue->first;

    int return_value = curr_first->value;

    if(theQueue->first != theQueue->last){
        theQueue->first = curr_first->prev;
        theQueue->first->next = NULL;

    }else{
        theQueue->first = NULL;
        theQueue->last = NULL;
    }

    theQueue->size--;

    free(curr_first);

    *output = return_value;
    return 1;
}

int peek(struct Queue *theQueue, int* output){
    if(theQueue->first == NULL){
        return 0;
    }else{
        *output = theQueue->first->value;
        return 1;
    }
}

int isEmpty(struct Queue *theQueue){
    return (theQueue->size==0 && theQueue->first==NULL && theQueue->last==NULL);
}

void printQueue(struct Queue *theQueue){
    struct node* cur_node = theQueue->last;

    if(cur_node == NULL){
        printf("EMPTY Queue!\n");
    }else{  
        printf("%d", cur_node->value);
        while(hasNext(cur_node)){
            cur_node = cur_node->next;
            printf(" -> %d", cur_node->value);
        }
    }
    printf("\n");
}