#ifndef MAX_HEAP_H
#define MAX_HEAP_H

struct node {
    int value;
    int priority;
    struct node *parent;
    struct node *left;
    struct node *right;
};


struct MaxHeap{
    struct node *root;
    int nodes_qty;
};

struct MaxHeap* newMaxHeap();
int enqueue(struct MaxHeap *theHeap, int value, int priority);
int pop(struct MaxHeap *theHeap, int* output);
int isEmpty(struct MaxHeap *theHeap);
int peek(struct MaxHeap *theHeap, int* output);
void printPLR(struct MaxHeap *theHeap);
void printLPR(struct MaxHeap *theHeap);
void printLRP(struct MaxHeap *theHeap);

#endif //MAX_HEAP_H