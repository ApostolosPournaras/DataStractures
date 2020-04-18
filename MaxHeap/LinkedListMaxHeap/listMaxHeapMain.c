#include <stdio.h>
#include <sys/time.h> // for clock_gettime()
#include "listMaxHeap.h"
#include <math.h>

void main(){

    struct MaxHeap *theHeap = newMaxHeap();
    int out;
    int i;

    struct timeval start, end;
    long secs_used,micros_used;

    int q;    
    printf("------ list MaxHeap performance test ------\n");
    printf("elements QTY\tTime elasped(sec)\n");

    for(q=1; q<=18; q++){
        int qty = (int)pow(2, q);
        
        gettimeofday(&start, NULL);
        for(i=0; i<qty; i++){
            int priority = i%2==0?floor(i/2)+1:qty-floor(i/2);
            enqueue(theHeap, i+1, priority);
        }
         struct node* head = theHeap->head;
         struct node* tail = theHeap->tail;

        for(i=0; i<qty; i++){
            if(!pop(theHeap, &out)){
                printf("failed to pop\n");
            }
         }        
        gettimeofday(&end, NULL);

        secs_used=(end.tv_sec - start.tv_sec); //avoid overflow by subtracting first
        micros_used= ((secs_used*1000000) + end.tv_usec) - (start.tv_usec);

        printf("%i\t%f\n",qty, (float)micros_used/1000000.0);                
    }

    //--------------------------------------------------

    // printHeadtoTail(theHeap);
    // printTailtoHead(theHeap);
    // enqueue(theHeap, 9, 9);
    // printHeadtoTail(theHeap);
    // printTailtoHead(theHeap);
    // enqueue(theHeap, 8, 1);
    // printHeadtoTail(theHeap);
    // printTailtoHead(theHeap);
    // enqueue(theHeap, 7, 7);
    // printHeadtoTail(theHeap);
    // printTailtoHead(theHeap);
    // enqueue(theHeap, 6, 2);
    // printHeadtoTail(theHeap);
    // printTailtoHead(theHeap);
    // enqueue(theHeap, 5, 3);
    // printHeadtoTail(theHeap);
    // printTailtoHead(theHeap);
    // enqueue(theHeap, 4, 4);
    // printHeadtoTail(theHeap);
    // printTailtoHead(theHeap);
    // enqueue(theHeap, 3, 5);
    // printHeadtoTail(theHeap);
    // printTailtoHead(theHeap);
    // enqueue(theHeap, 2, 6);
    // printHeadtoTail(theHeap);
    // printTailtoHead(theHeap);
    // enqueue(theHeap, 1, 8);
    // printHeadtoTail(theHeap);
    // printTailtoHead(theHeap);
    // printf("\n\n");

    // if(peek(theHeap, &out)){
    //     printf("peek: = %i\n", out);
    // }else{
    //     printf("failed to peek\n");
    // }
    
    // printf("\n\n");

    // int nodes_added = theHeap->nodes_qty;
    // int value;
    // for(i=0; i<nodes_added+3; i++){

    //     if(i==nodes_added/2){
    //         printf("\n ______ the heap: ______\n");
    //         printHeadtoTail(theHeap);
    //         printTailtoHead(theHeap);
    //         printf("\n\n");
    //     }
        
    //     if(!isEmpty(theHeap)){
    //         if(pop(theHeap, &out)){
    //             printf("pop: = %i\n", out);
    //         }else{
    //             printf("failed to pop\n");
    //         }
    //     }else{
    //         printf("The heap was empty!\n");
    //     }
    // }

    // printf("\n ______ the heap ______\n");    
    // printHeadtoTail(theHeap);
    // printTailtoHead(theHeap);
    // printf("\n\n");

    return;
}