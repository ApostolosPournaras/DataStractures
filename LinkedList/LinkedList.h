#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct node {
    int value;
    struct node *prev;
    struct node *next;
};


struct LinkedList{
    struct node *head;
    struct node *tail;
    int nodes_qty;
};

struct LinkedList* newLinkedList();
int addLast(struct LinkedList *theList, int value);
int addFirst(struct LinkedList *theList, int value);
int addAt(struct LinkedList *theList, int value, int index);
int getLast(struct LinkedList *theList, int* output);
int getFirst(struct LinkedList *theList, int* output);
int getFrom(struct LinkedList *theList, int index, int* output);
int isEmpty(struct LinkedList *theList);
int peekFirst(struct LinkedList *theList, int* output);
int peekLast(struct LinkedList *theList, int* output);
int peekAt(struct LinkedList *theList, int index, int* output);
void printHeadtoTail(struct LinkedList *theList);
void printTailtoHead(struct LinkedList *theList);

#endif //LINKEDLIST_H