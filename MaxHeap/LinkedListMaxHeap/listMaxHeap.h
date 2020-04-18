#ifndef LIST_MAX_HEAP_H
#define LIST_MAX_HEAP_H

struct node {
    int value;
    int priority;
    struct node *prev;
    struct node *next;
};


struct MaxHeap{
    struct node *head;
    struct node *tail;
    int nodes_qty;
};

struct MaxHeap* newMaxHeap();
int enqueue(struct MaxHeap *theHeap, int value, int priority);
int pop(struct MaxHeap *theHeap, int* output);
int isEmpty(struct MaxHeap *theHeap);
int peek(struct MaxHeap *theHeap, int* output);
void printHeadtoTail(struct MaxHeap *theHeap);
void printTailtoHead(struct MaxHeap *theHeap);

#endif //LIST_MAX_HEAP_H