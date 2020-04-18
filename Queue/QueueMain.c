#include <stdio.h>
#include <sys/time.h> // for clock_gettime()
#include "Queue.h"
#include <math.h>

void main(){

    struct Queue *theQueue = newQueue();
    int i;

    struct timeval start, end;
    long secs_used,micros_used;

    int q;

    printf("------ Queue performance test ------\n");
    printf("elements QTY\tTime elasped(sec)\n");

    for(q=1; q<=25; q++){
        int qty = (int)pow(2, q);
        
        gettimeofday(&start, NULL);
        for(i=0; i<qty; i++){
            if(!enqueue(theQueue, i)){
                printf("enqueue of %i failed\n", i);
            }
        }

        int out;
        for(i=0; i<qty; i++){
            if(!deQueue(theQueue, &out)){
                printf("denqueue failed\n");
            }
         }        
        gettimeofday(&end, NULL);

        secs_used=(end.tv_sec - start.tv_sec); //avoid overflow by subtracting first
        micros_used= ((secs_used*1000000) + end.tv_usec) - (start.tv_usec);

        printf("%i\t%f\n",qty, (float)micros_used/1000000.0);
                
    }
    
    //------------------------------------------------------------------------------------------------------------
    
    // printQueue(theQueue);

    // enqueue(theQueue, 1);
    // printQueue(theQueue);

    // enqueue(theQueue, 2);    
    // printQueue(theQueue);
    
    // enqueue(theQueue, 3);   
    // printQueue(theQueue);

    // enqueue(theQueue, 4);    
    // printQueue(theQueue);

    // enqueue(theQueue, 5);
    // printQueue(theQueue);
    
    // enqueue(theQueue, 6);
    // printQueue(theQueue);

    // enqueue(theQueue, 7);
    // printQueue(theQueue);

    // enqueue(theQueue, 8);
    // printQueue(theQueue);
    // printf("\n\n");

    // int out;

    // if(peek(theQueue, &out)){
    //     printf("\npeek: = %i\n", out);
    // }else{
    //     printf("\npeek failed\n");
    // }
    
    // printf("\n\n");

    // int nodes_added = theQueue->size;
    // for(i=0; i<nodes_added+3; i++){

    //     if(i==nodes_added/2){
    //         printf("\n ______ the Queue: ______\n");
    //         printQueue(theQueue);
            
    //         printf("\n\n");
    //     }
        
    //     if(!isEmpty(theQueue)){
    //         if(deQueue(theQueue, &out)){
    //             printf("deQueueed: %i\n", out);
    //         }else{
    //             printf("deQueue failed\n");
    //         }
    //     }else{
    //         printf("The Queue was empty!\n");
    //     }
    // }

    // printf("\n ______ the Queue ______\n");    
    // printQueue(theQueue);
    
    // printf("\n\n");

    // return;
}