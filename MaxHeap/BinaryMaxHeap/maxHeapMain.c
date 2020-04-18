#include <stdio.h>
#include <sys/time.h> // for clock_gettime()
#include "maxHeap.h"
#include <math.h>

void main(){

    struct timeval start, end;
    long secs_used,micros_used;

    int q;
    int out;
    int i;

    printf("------ MaxHeap performance test ------\n");
    printf("elements QTY\tTime elasped(sec)\n");

    for(q=18; q<=20; q++){
        struct MaxHeap *theHeap = newMaxHeap();        
        int qty = (int)pow(2, q);

        //printf("------------------------- q = %i qty = %i -------------------------\n", q, qty);

        gettimeofday(&start, NULL);
        for(i=0; i<qty; i++){
            int priority = i%2==0?floor(i/2)+1:qty-floor(i/2);
            //printf("\tenqueue (%i,%i)\n", i+1, priority);
            enqueue(theHeap, i+1, priority);
        } 
        // printf("q = %i -- 2\n", q);
        for(i=0; i<qty; i++){            
            if(!pop(theHeap, &out)){
                printf("failed to pop\n");
            // }else{
            //     printf("\tpopped %i\n", out);
            }
        }
        // printf("q = %i -- 3\n", q);
        gettimeofday(&end, NULL);
        // printf("Heap has %i nodes\n", theHeap->nodes_qty);
        // if(!isEmpty(theHeap)){
        //     printf("Heap's root is (%i,%i)\n", theHeap->root->value, theHeap->root->priority);
        // }
        //printf("q = %i -- 4\n", q);
        secs_used=(end.tv_sec - start.tv_sec); //avoid overflow by subtracting first
        micros_used= ((secs_used*1000000) + end.tv_usec) - (start.tv_usec);

        printf("%i\t%f\n",qty, (float)micros_used/1000000.0);
        
    }

    //------------------------------------------------

    // enqueue(theHeap, 1, 2);
    // enqueue(theHeap, 2, 20);
    // enqueue(theHeap, 3, 7);
    // enqueue(theHeap, 4, 1);
    // enqueue(theHeap, 5, 7);
    // enqueue(theHeap, 6, 7);
    // enqueue(theHeap, 7, 8);
    // enqueue(theHeap, 8, 12);
    // enqueue(theHeap, 9, 3);
    
    // if(peek(theHeap, &out)){
    //     printf("peek: = %i\n", out);
    // }else{
    //     printf("failed to peek\n");
    // }
    

    // printf("\n ______ Parent, Left-child, rioght-child order ______\n");
    // printPLR(theHeap);
    // printf("\n ______ Left-child, Parent, right-child order ______\n");
    // printLPR(theHeap);
    // printf("\n ______ Left-child, right-child, Parent order ______\n");
    // printLRP(theHeap);
    // printf("\n\n");

    // int nodes_added = theHeap->nodes_qty;
    // int value;
    // for(i=0; i<nodes_added+3; i++){

    //     if(i==nodes_added/2){
    //         printf("\n ______ Parent, Left-child, rioght-child order ______\n");
    //         printPLR(theHeap);
    //         printf("\n ______ Left-child, Parent, right-child order ______\n");
    //         printLPR(theHeap);
    //         printf("\n ______ Left-child, right-child, Parent order ______\n");
    //         printLRP(theHeap);
    //         printf("\n\n");
    //     }
        
    //     if(!isEmpty(theHeap)){
    //         if(pop(theHeap, &out)){
    //             printf("poped: = %i\n", out);
    //         }else{
    //             printf("failed to pop\n");
    //         }
    //     }else{
    //         printf("The heap was empty!\n");
    //     }
    // }

    // printf("\n ______ Parent, Left-child, rioght-child order ______\n");
    // printPLR(theHeap);
    // printf("\n ______ Left-child, Parent, right-child order ______\n");
    // printLPR(theHeap);
    // printf("\n ______ Left-child, right-child, Parent order ______\n");
    // printLRP(theHeap);
    // printf("\n\n");
    // return;
}