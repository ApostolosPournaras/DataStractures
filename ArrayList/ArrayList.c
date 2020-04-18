#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ArrayList.h"

static int expand(struct ArrayList *theArrayList, int newCapacity){

    if(newCapacity < theArrayList->capacity){
        //printf("New capacity was smaller than the previous capacity!!!!\n");
        return 0;
    }

    if(theArrayList->capacity == newCapacity){
        //printf("New capacity was equal than the previous capacity. no need of reallocating\n");
        return 1;
    }

    int* newArray = (int*)malloc(newCapacity * sizeof(int));

    int i;
    for(i=0; i<theArrayList->capacity; i++){
        newArray[i] = theArrayList->array[i];
    }

    free(theArrayList->array);

    theArrayList->array = newArray;

    theArrayList->capacity = newCapacity;
    
    return 1;
}

static int contract(struct ArrayList *theArrayList, int newCapacity){

    if(newCapacity < INITIAL_CAPACITY){
        //printf("New capacity was smaller than newCapacity RETURN.\n");
        return 1;
    }

    if(newCapacity > theArrayList->capacity){
        //printf("New capacity was bigger than the previous capacity!!!!\n");
        return 0;
    }

    if(theArrayList->capacity == newCapacity){
        //printf("New capacity was equal than the previous capacity. no need of reallocating\n");
        return 1;
    }

    int* newArray = (int*)malloc(newCapacity * sizeof(int));

    int i;
    for(i=0; i<newCapacity; i++){
        newArray[i] = theArrayList->array[i];
    }

    free(theArrayList->array);

    theArrayList->array = newArray;

    theArrayList->capacity = newCapacity;
    
    return 1;
}

struct ArrayList* newArrayList(){
    struct ArrayList *theArrayList = (struct ArrayList*)malloc(sizeof(struct ArrayList));

    theArrayList->array = (int*)malloc(INITIAL_CAPACITY * sizeof(int));
    theArrayList->capacity = INITIAL_CAPACITY;
    theArrayList->size = 0;
    return theArrayList;
}

int setAt(struct ArrayList *theArrayList, int value, int index){
    if(index < 0 || index > theArrayList->size-1){
        //printf("Out of Bounds!!!\n");
        return 0;
    }

    theArrayList->array[index] = value;

    return 1;
}

int push(struct ArrayList *theArrayList, int value){    
    
    if(theArrayList->size == theArrayList->capacity/2){
        //printf("Reallocate because current size = %i and current capacity = %i\n", theArrayList->size, theArrayList->capacity);
        if(!expand(theArrayList, 2*theArrayList->capacity)){
            return 0;
        }
    }

    theArrayList->array[theArrayList->size] = value;
    theArrayList->size++;
    return 1;
}

int pop(struct ArrayList *theArrayList, int *output){    
    
    if(theArrayList->size == theArrayList->capacity/4 && theArrayList->capacity>INITIAL_CAPACITY){
        //printf("Reallocate because current size = %i and current capacity = %i\n", theArrayList->size, theArrayList->capacity);
        if(!contract(theArrayList, theArrayList->capacity/2)){
            return 0;
        }
    }

    if(theArrayList->size>0){
        *output = theArrayList->array[theArrayList->size-1];
        theArrayList->size--;
        return 1;
    }else{
        return 0;
    }
}

int peekFirst(struct ArrayList *theArrayList, int *output){
    if(theArrayList->size == 0){
        printf("ArrayList is empty!!!\n");
        return 0;
    }
    *output = theArrayList->array[0];
    return 1;
}

int peekLast(struct ArrayList *theArrayList, int *output){
    if(theArrayList->size == 0){
        printf("ArrayList is empty!!!\n");
        return 0;
    }

    *output = theArrayList->array[theArrayList->size-1];
    return 1;
}

int peekAt(struct ArrayList *theArrayList, int index, int *output){
    if(theArrayList->size == 0){
        printf("ArrayList is empty!!!\n");
        return 0;
    }

    if(index > theArrayList->size -1 || index < 0){
        printf("out of bounds!!!\n");
        return 0;
    }

    *output = theArrayList->array[index];
    return 1;
}

int insertAt(struct ArrayList *theArrayList, int value, int index){
    if(index < 0 || index > theArrayList->size){
        //printf("Out of Bounds!!!\n");
        return 0;
    }

    if(theArrayList->size == theArrayList->capacity/2){
        //printf("Reallocate because current size = %i and current capacity = %i\n", theArrayList->size, theArrayList->capacity);
        if(!expand(theArrayList, 2*theArrayList->capacity)){
            return 0;
        }
    }

    int i;
    for (i=theArrayList->size-1; i>=index; i--){
        theArrayList->array[i+1] = theArrayList->array[i];
    }

    theArrayList->array[index] = value;
    theArrayList->size++;

    return 1;
}

int removeFrom(struct ArrayList *theArrayList, int index, int *output){
    if(index < 0 || index > theArrayList->size-1){
        //printf("Out of Bounds!!!\n");
        return 0;
    }

    if(theArrayList->size == theArrayList->capacity/4 && theArrayList->capacity>INITIAL_CAPACITY){
        //printf("Reallocate because current size = %i and current capacity = %i\n", theArrayList->size, theArrayList->capacity);
        if(!contract(theArrayList, theArrayList->capacity/2)){
            return 0;
        }
    }
    
    *output = theArrayList->array[index];

    int i;
    for (i=index; i<=theArrayList->size-1; i++){
        theArrayList->array[i] = theArrayList->array[i+1];
    }
    
    theArrayList->size--;

    return 1;
}

void printArrayList(struct ArrayList *theArrayList){
    
    if(theArrayList->size == 0){
        printf("EMPTY ArrayList!\n");
    }else{  
        printf("Array = [%d", theArrayList->array[0]);

        int i;
        for(i=1; i<theArrayList->size; i++){
            printf(", %d", theArrayList->array[i]);
        }
        printf("]\n");
    }
}