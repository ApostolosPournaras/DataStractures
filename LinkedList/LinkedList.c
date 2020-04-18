#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "LinkedList.h"

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

struct LinkedList* newLinkedList(){
    return (struct LinkedList*)malloc(sizeof(struct LinkedList));
}

static struct node* newNode(int value){
    struct node* nd = malloc(sizeof(struct node));

    if(nd != NULL){        
        nd->value = value;
    }

    return nd;
}

int addLast(struct LinkedList *theList, int value){
    // printf("->add %i as tail\n", value);
    struct node* new_nd = newNode(value);

    if(new_nd == NULL){
        // printf("FAILED to add %i\n", value);
        return 0;
    }

    if(theList->head == NULL){
        theList->head = new_nd;
        theList->tail = new_nd;
        theList->nodes_qty++;
        // printf("  ->node %i added as tail\n", value);
        return 1;
    }else{
        //add as new tail
        new_nd->prev = theList->tail;
        theList->tail->next = new_nd;
        theList->tail = new_nd;
        theList->nodes_qty++;
        // printf("  ->node %i added as new tail\n", value);
        return 1;
    }

    return 0;
}

int addFirst(struct LinkedList *theList, int value){
    //printf("->add %i as head\n", value);
    struct node* new_nd = newNode(value);

    if(new_nd == NULL){
        //printf("FAILED to add %i\n", value);
        return 0;
    }

    if(theList->head == NULL){
        theList->head = new_nd;
        theList->tail = new_nd;
        theList->nodes_qty++;
        //printf("  ->node %i added head. (list was empty)\n", value);
        return 1;
    }else{
        //add as new head
        new_nd->next = theList->head;
        theList->head->prev = new_nd;
        theList->head = new_nd;        
        theList->nodes_qty++;
        //printf("  ->node %i added as new head\n", value);
        return 1;
    }

    return 0;
}

int addAt(struct LinkedList *theList, int value, int index){
    //printf("add %i at index %i\n", value, index);
    if(theList->nodes_qty < index){
        //printf("FAILED to add %i. index %i is greater than list's size of %i!\n", value, index, theList->nodes_qty);
        return 0;
    }else if(index < 0){
        //printf("FAILED to add %i. index %i is greater less than zero!!\n", value, index);
        return 0;
    }else if(index ==0){
        return addFirst(theList, value);
    }else if(index == theList->nodes_qty){
        return addLast(theList, value);
    }else if(index <= theList->nodes_qty/2){
        //printf("->add %i at #%i\n", value, index);
        struct node* new_nd = newNode(value);

        if(new_nd == NULL){
            //printf("FAILED to add %i\n", value);
            return 0;
        }

        struct node* curr_node = theList->head;

        int idx=1;

        while(idx<index){
            curr_node = curr_node->next;
            idx++;
        }
        
        new_nd->prev = curr_node;
        new_nd->next = curr_node->next;
        curr_node->next->prev = new_nd;
        curr_node->next = new_nd;

        theList->nodes_qty++;
        //printf("  ->node %i added at index %i\n", value, idx);

        return 1;
    }else{
        //printf("->add %i at #%i\n", value, index);
        struct node* new_nd = newNode(value);

        if(new_nd == NULL){
            //printf("FAILED to add %i\n", value);
            return 0;
        }

        struct node* curr_node = theList->tail;

        int idx=theList->nodes_qty-1;

        do{
            curr_node = curr_node->prev;
            idx--;
        }while(idx>index);
        
        new_nd->prev = curr_node;
        new_nd->next = curr_node->next;
        curr_node->next->prev = new_nd;
        curr_node->next = new_nd;

        theList->nodes_qty++;
        //printf("  ->node %i added at index %i\n", value, idx);

        return 1;
    }

    return 0;
}

int getLast(struct LinkedList *theList, int* output){

    if(theList->tail == NULL){        
        //printf("The List is empty!!\n");
        return 0;
    }

    struct node* curr_tail = theList->tail;

    int return_value = curr_tail->value;

    if(theList->tail != theList->head){
        struct node* tail_prev = theList->tail->prev;
        theList->tail = tail_prev;
        theList->tail->next = NULL;
    }else{
        theList->head=NULL;
        theList->tail=NULL;
        //printf("last element to be poped!!\n");
    }

    theList->nodes_qty--;

    free(curr_tail);
    *output = return_value;
    return 1;
}

int getFirst(struct LinkedList *theList, int* output){

    if(theList->head == NULL){        
        //printf("The List is empty!!\n");
        return 0;
    }

    struct node* curr_head = theList->head;

    int return_value = curr_head->value;

    if(theList->tail != theList->head){
        struct node* head_next = theList->head->next;
        theList->head = head_next;
        theList->head->prev = NULL;
    }else{
        theList->head=NULL;
        theList->tail=NULL;
        //printf("last element to be poped!!\n");
    }

    theList->nodes_qty--;

    free(curr_head);
    *output = return_value;
    return 1;
}

int getFrom(struct LinkedList *theList, int index, int* output){

    if(theList->nodes_qty < index){
        //printf("FAILED to get value form index %i, because it's greater than list's size!!\n", value);
        return 0;
    }else if(index < 0){
        //printf("FFAILED to get value form index %i, because it is less less than zero!!\n", value);
        return 0;
    }else if(index == 0){
        return getFirst(theList, output);
    }else if(index == theList->nodes_qty-1){
        return getLast(theList, output);
    }else if(index <= theList->nodes_qty/2){
        //printf(" ->remove node from index %i\n", index);
        struct node* curr_node = theList->head;

        int idx=0;

        do{
            curr_node = curr_node->next;
            idx++;
        }while(idx<index);
        
        int return_value = curr_node->value;
        
        struct node* curr_prev = curr_node->prev;
        struct node* curr_next = curr_node->next;

        curr_prev->next = curr_node->next;
        curr_next->prev = curr_node->prev;
        
        theList->nodes_qty--;
        free(curr_node);
        *output = return_value;
        //printf("  ->node %i removed from idx %i\n", return_value, idx);
        return 1;
    }else{
        //printf(" ->remove node from index %i\n", index);
        struct node* curr_node = theList->tail;

        int idx=theList->nodes_qty-1;

        do{
            curr_node = curr_node->prev;
            idx--;
        }while(idx>index);
        
        int return_value = curr_node->value;
        
        struct node* curr_prev = curr_node->prev;
        struct node* curr_next = curr_node->next;

        curr_prev->next = curr_node->next;
        curr_next->prev = curr_node->prev;
        
        theList->nodes_qty--;
        free(curr_node);
        *output = return_value;
        //printf("  ->node %i removed from idx %i\n", return_value, idx);
        return 1;
    }

    return 0;
}

int peekLast(struct LinkedList *theList, int* output){

    if(theList->tail == NULL){        
        //printf("The List is empty!!\n");
        return 0;
    }

    struct node* curr_tail = theList->tail;

    *output = curr_tail->value;
    return 1;
}

int peekFirst(struct LinkedList *theList, int* output){

    if(theList->head == NULL){        
        //printf("The List is empty!!\n");
        return 0;
    }

    struct node* curr_head = theList->head;
    *output = curr_head->value;
    return 1;
}

int peekAt(struct LinkedList *theList, int index, int* output){

    if(index >= theList->nodes_qty){
        //printf("FAILED to get value form index %i, because it's greater than list's size!!\n", index);
        return 0;
    }else if(index < 0){
        //printf("FAILED to get value form index %i, because it is less less than zero!!\n", index);
        return 0;
    }else if(index ==0){
        return peekFirst(theList, output);
    }else if(index == theList->nodes_qty-1){
        return peekLast(theList, output);
    }else if(index <= theList->nodes_qty/2){
        
        struct node* curr_node = theList->head;

        int idx=0;

        do{
            curr_node = curr_node->next;
            idx++;
        }while(idx<index);
        
        *output = curr_node->value;
        return 1;

    }else{
        
        struct node* curr_node = theList->tail;

        int idx=theList->nodes_qty-1;

        do{
            curr_node = curr_node->prev;
            idx--;
        }while(idx>index);
        
        *output = curr_node->value;
        return 1;
    }

    return 0;
}

int isEmpty(struct LinkedList *theList){
    return (theList->nodes_qty==0 && theList->head==NULL && theList->tail==NULL);
}

void printTailtoHead(struct LinkedList *theList){
    struct node* cur_node = theList->tail;

    if(cur_node == NULL){
        printf("EMPTY List!\n");
    }else{  
        printf("%d", cur_node->value);
        while(hasPrev(cur_node)){
            cur_node = cur_node->prev;
            printf(" <- %d", cur_node->value);
        }
        printf("\n");
    }
}

void printHeadtoTail(struct LinkedList *theList){
    struct node* cur_node = theList->head;

    if(cur_node == NULL){
        printf("EMPTY List!\n");
    }else{  
        printf("%d", cur_node->value);
        while(hasNext(cur_node)){
            cur_node = cur_node->next;
            printf(" -> %d", cur_node->value);
        }
        printf("\n");
    }
}