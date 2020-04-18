#include <stdio.h>
#include <sys/time.h> // for clock_gettime()
#include "ArrayList.h"
#include <math.h>
#include <stdlib.h>

void main(){

    struct ArrayList *theArrayList = newArrayList(10);
    int out;
    int i;

    struct timeval start, end;
    long secs_used,micros_used;

    int q;

    printf("------ ArrayList performance test ------\n");
    printf("elements QTY\tTime elasped(sec)\n");

    for(q=1; q<=27; q++){
        int qty = (int)pow(2, q);
        
        gettimeofday(&start, NULL);
        for(i=0; i<qty; i++){
            if(!push(theArrayList, i)){
                printf("push %i failled\n", i);
            }
        }

        for(i=0; i<qty; i++){
            if(!pop(theArrayList, &out)){
                printf("pop failled\n");
            }
         }        
        gettimeofday(&end, NULL);

        secs_used=(end.tv_sec - start.tv_sec); //avoid overflow by subtracting first
        micros_used= ((secs_used*1000000) + end.tv_usec) - (start.tv_usec);

        printf("%i\t%f\n",qty, (float)micros_used/1000000.0);
                
    }
    
    //------------------------------------------------------------------------------------------------------------
  

//     printArrayList(theArrayList);
//     for(i=0; i<30; i++){
//         if(push(theArrayList, i)){
//             printf("size = %i, capacity = %i\n", theArrayList->size, theArrayList->capacity);            
//         }
//         printArrayList(theArrayList);
//     }

//     printf("\n\n");

//     setAt(theArrayList, 30, 3);
//     printArrayList(theArrayList);

//     setAt(theArrayList, 50, 50);
//     printArrayList(theArrayList);

//     if(!peekAt(theArrayList, 7, &out)){
//         printf("peekAt(7) failled\n");
//     }else{
//         printf("Array[7] = %i\n", out);
//     }

//     if(!peekAt(theArrayList, 70, &out)){
//         printf("peekAt(70) failled\n");
//     }else{
//         printf("Array[70] = %i\n", out);
//     }

//     if(!pop(theArrayList, &out)){
//         printf("pop failled\n");
//     }else{
//         printf("poped %i\n", out);
//     }
//     if(!pop(theArrayList, &out)){
//         printf("pop failled\n");
//     }else{
//         printf("poped %i\n", out);
//     }

//     if(!peekFirst(theArrayList, &out)){
//         printf("peekFirst failled\n");
//     }else{
//         printf("first is %i\n", out);
//     }

//     if(!peekLast(theArrayList, &out)){
//         printf("peekLast failled\n");
//     }else{
//         printf("last is %i\n", out);
//     }
   
//    for(i=0; i<40; i++){
//        if(!pop(theArrayList, &out)){
//             printf("pop failled\n");
//         }else{
//             printf("poped %i, size = %i, capacity = %i\n", out, theArrayList->size, theArrayList->capacity);
//         }
        
//         printArrayList(theArrayList);
//     }

//     printf("\n\n");

    // for(i=0; i<10; i++){
    //     if(push(theArrayList, i)){
    //         printf("size = %i, capacity = %i\n", theArrayList->size, theArrayList->capacity);            
    //     }
    //     printArrayList(theArrayList);
    // }


    // int testInIdx[] = {0, 12, -1, 10, 5};
    // int testInVal[] = {55, 66, 77, 88, 99};

    // for(i=0; i<5;i++){
    //     if(!insertAt(theArrayList, testInVal[i], testInIdx[i])){
    //         printf("insertAt(%i) failled\n", testInIdx[i]);
    //     }else{
    //         printf("insertAt(%i) the value %i\n", testInIdx[i], testInVal[i]);
    //         printArrayList(theArrayList);
    //     }        
    // }

    // int testRemIdx[] = {0, 12, -1, 10, 5, 9};

    // for(i=0; i<6;i++){
    //     if(!removeFrom(theArrayList, testRemIdx[i], &out)){
    //         printf("removeFrom(%i) failled\n", testRemIdx[i]);
    //     }else{
    //         printf("removeFrom(%i) returned %i\n", testRemIdx[i], out);
    //         printArrayList(theArrayList);
    //     }        
    // }

    // printf("\n\n");

    // return;
}