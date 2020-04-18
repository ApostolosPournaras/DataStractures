#ifndef STACK_H
#define STACK_H

struct node {
    int value;
    struct node *next;
};


struct Stack{
    struct node *top;
    int size;
};

struct Stack* newStack();
int push(struct Stack *theStack, int value);
int pop(struct Stack *theStack, int *output);
int isEmpty(struct Stack *theStack);
int peek(struct Stack *theStack, int *output);
void printStack(struct Stack *theStack);
#endif //STACK_H