#ifndef QUEUE_H
#define QUEUE_H

struct node {
    int value;
    struct node *next;
    struct node *prev;
};


struct Queue{
    struct node *first;
    struct node *last;
    int size;
};

struct Queue* newQueue();
int enqueue(struct Queue *theQueue, int value);
int deQueue(struct Queue *theQueue, int *output);
int isEmpty(struct Queue *theQueue);
int peek(struct Queue *theQueue, int *output);
void printQueue(struct Queue *theQueue);
#endif //QUEUE_H