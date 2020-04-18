#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Stack.h"


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

struct Stack* newStack(){
    return (struct Stack*)malloc(sizeof(struct Stack));
}

static struct node* newNode(int value){
    struct node* nd = malloc(sizeof(struct node));

    if(nd != NULL){        
        nd->value = value;
    }

    return nd;
}

int push(struct Stack *theStack, int value){
    //printf("->psuh %i\n", value);
    struct node* new_nd = newNode(value);

    if(new_nd == NULL){
        //printf("FAILED to push %i\n", value);
        return 0;
    }

    if(theStack->top != NULL){
        new_nd->next = theStack->top;
    }

    theStack->top = new_nd;
    theStack->size++;
    //printf("  ->node (%i, %i) added as top\n", value);
    return 1;
}

int pop(struct Stack *theStack, int *output){

    if(theStack->top == NULL){        
        //printf("The stack is empty!!\n");
        return 0;
    }
    
    struct node* cur_top = theStack->top;

    int return_value = cur_top->value;

    theStack->top=cur_top->next;
    
    theStack->size--;

    free(cur_top);

    *output = return_value;
    return 1;
}

int peek(struct Stack *theStack, int *output){
    if(theStack->top == NULL){
        return 0;
    }else{
        *output = theStack->top->value;
        return 1;
    }
}

int isEmpty(struct Stack *theStack){
    return (theStack->size==0 && theStack->top==NULL);
}

void printStack(struct Stack *theStack){
    struct node* cur_node = theStack->top;

    if(cur_node == NULL){
        printf("EMPTY stack!\n");
    }else{  
        printf("%d", cur_node->value);
        while(hasNext(cur_node)){
            cur_node = cur_node->next;
            printf(" -> %d", cur_node->value);
        }
    }
    printf("\n");
}