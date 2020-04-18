#ifndef ARRAYLIST_H_H
#define ARRAYLIST_H

#define INITIAL_CAPACITY 20

struct ArrayList{
    int *array;
    int capacity;
    int size;
};

struct ArrayList* newArrayList();
int push(struct ArrayList *theArrayList, int value);
int pop(struct ArrayList *theArrayList, int *output);
int setAt(struct ArrayList *theArrayList, int value, int index);
int insertAt(struct ArrayList *theArrayList, int value, int index);
int peekAt(struct ArrayList *theArrayList, int index, int *output);
int removeFrom(struct ArrayList *theArrayList, int index, int *output);
int peekFirst(struct ArrayList *theArrayList, int *output);
int peekLast(struct ArrayList *theArrayList, int *output);
void printArrayList(struct ArrayList *theArrayList);
#endif //ARRAYLIST_H