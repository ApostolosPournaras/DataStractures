#include <stdio.h>
#include <sys/time.h> // for clock_gettime()
#include <stdlib.h> // For random(), RAND_MAX
#include "LinkedList.h"
#include <math.h>

void main(){

    struct LinkedList *theList = newLinkedList();
    int i;

    struct timeval start, end;
    long secs_used,micros_used;

    int q;

    printf("------ Linked-list performance test ------\n");
    printf("elements QTY\tTime elasped(sec)\n");

    for(q=1; q<=17; q++){
        int qty = (int)pow(2, q);
        
        gettimeofday(&start, NULL);
        for(i=0; i<qty; i++){
            if(!addAt(theList, i, i/2)){
                printf("failed to addAt(%i) the value %i\n", i/2, i);
            }
        }

        int out;
        for(i=0; i<qty; i++){
            if(!getFrom(theList, (qty-i)/2, &out)){
                printf("failed to getFrom(%i)\n", (qty-i)/2);
            }
        }
        gettimeofday(&end, NULL);
        //printf("is empty? %s\n", isEmpty(theList)?"yes":"no");

        secs_used=(end.tv_sec - start.tv_sec); //avoid overflow by subtracting first
        micros_used= ((secs_used*1000000) + end.tv_usec) - (start.tv_usec);

        printf("%i\t%f\n",qty, (float)micros_used/1000000.0);
    }

    //------------------------------------------------------------------------------------------------------------------------

    // printHeadtoTail(theList);
    // //printTailtoHead(theList);
    // addFirst(theList, 1);
    // printHeadtoTail(theList);
    // //printTailtoHead(theList);
    // addFirst(theList, 2);
    // printHeadtoTail(theList);
    // //printTailtoHead(theList);
    // addFirst(theList, 3);
    // printHeadtoTail(theList);
    // //printTailtoHead(theList);
    // addLast(theList, 4);
    // printHeadtoTail(theList);
    // //printTailtoHead(theList);
    // addLast(theList, 5);
    // printHeadtoTail(theList);
    // //printTailtoHead(theList);
    // addLast(theList, 6);
    // printHeadtoTail(theList);
    // //printTailtoHead(theList);
    // addAt(theList, 7, 0);
    // printHeadtoTail(theList);
    // //printTailtoHead(theList);
    // addAt(theList, 8, 0);
    // printHeadtoTail(theList);
    // //printTailtoHead(theList);
    // addAt(theList, 9, 9);
    // printHeadtoTail(theList);
    // //printTailtoHead(theList);
    // addAt(theList, 9, 8);
    // printHeadtoTail(theList);
    // //printTailtoHead(theList);
    // addAt(theList, 10, 1);
    // printHeadtoTail(theList);
    // //printTailtoHead(theList);
    // addAt(theList, 11, 2);
    // printHeadtoTail(theList);
    // //printTailtoHead(theList);
    // addAt(theList, 12, 5);
    // printHeadtoTail(theList);
    // //printTailtoHead(theList);
    // addAt(theList, 13, 7);
    // printHeadtoTail(theList);
    // //printTailtoHead(theList);
    // printf("\n\n");

    // int out;

    // if(peekFirst(theList, &out)){
    //     printf("peekFirst: = %i\n", out);
    // }else{
    //     printf("peekFirst failed\n");
    // }
    
    // if(peekLast(theList, &out)){
    //     printf("peekLast: = %i\n", out);
    // }else{
    //     printf("peekLast failed\n");
    // }

    // for(i=-2;i<theList->nodes_qty+4;i++){
    //     if(peekAt(theList, i, &out)){
    //         printf("peekAt(%i): = %i\n", i, out);
    //     }else{
    //         printf("peekAt(%i) failed\n", i);
    //     }
    // }
    
    // printf("\n---------------------------\n");

    // int nodes_added = theList->nodes_qty;
    // for(i=0; i<nodes_added; i++){
    //     printHeadtoTail(theList);
    //     printTailtoHead(theList);

    //     if(!isEmpty(theList)){
    //         int idx = (int)fmax(theList->nodes_qty-2, 0);
    //         if(getFrom(theList, idx, &out)){
    //             printf("getFrom(%i): = %i\n", idx, out);
    //         }else{
    //             printf("getFrom(%i) failed\n", idx);
    //         }
    //     }else{
    //         printf("The list was empty!\n");
    //     }
    // }

    // if(getFrom(theList, -2, &out)){
    //     printf("getFrom(-2): = %i\n", out);
    // }else{
    //     printf("getFrom(-2) failed\n");
    // }


    // if(getFrom(theList, 100, &out)){
    //     printf("getFrom(100): = %i\n", out);
    // }else{
    //     printf("getFrom(100) failed\n");
    // }
            
    // printf("\n ______ the List ______\n");    
    // printHeadtoTail(theList);
    // printTailtoHead(theList);
    // printf("\n\n");

    // return;
}