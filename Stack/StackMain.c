#include <stdio.h>
#include <sys/time.h> // for clock_gettime()
#include "Stack.h"
#include <math.h>

void main(){

    struct Stack *theStack = newStack();
    int i;

    struct timeval start, end;
    long secs_used,micros_used;

    int q;

    printf("------ Stack performance test ------\n");
    printf("elements QTY\tTime elasped(sec)\n");

    for(q=1; q<=25; q++){
        int qty = (int)pow(2, q);
        
        gettimeofday(&start, NULL);
        for(i=0; i<qty; i++){
            if(!push(theStack, i)){
                printf("push of %i failed!\n", i);
            }
        }

        for(i=0; i<qty; i++){
            int v;
            if(!pop(theStack, &v)){
                printf("pop failed!\n");
            }
         }        
        gettimeofday(&end, NULL);

        secs_used=(end.tv_sec - start.tv_sec); //avoid overflow by subtracting first
        micros_used= ((secs_used*1000000) + end.tv_usec) - (start.tv_usec);

        printf("%i\t%f\n",qty, (float)micros_used/1000000.0);
                
    }
    
    //------------------------------------------------------------------------------------------------------------
    
    // printStack(theStack);

    // push(theStack, 1);
    // printStack(theStack);

    // push(theStack, 2);    
    // printStack(theStack);
    
    // push(theStack, 3);   
    // printStack(theStack);

    // push(theStack, 4);    
    // printStack(theStack);

    // push(theStack, 5);
    // printStack(theStack);
    
    // printf("\n\n");

    // int out;
    // if(peek(theStack, &out)){
    //     printf("\npeek: = %i\n", out);
    // }else{
    //     printf("\npeek failed!\n");
    // }
        
    // printf("\n\n");

    // int nodes_added = theStack->size;
    // int value;
    // for(i=0; i<nodes_added+3; i++){

    //     if(i==nodes_added/2){
    //         printf("\n ______ the stack: ______\n");
    //         printStack(theStack);
            
    //         printf("\n\n");
    //     }
        
    //     if(!isEmpty(theStack)){
    //         if(pop(theStack, &value)){
    //             printf("poped: %i\n", value);
    //         }else{
    //             printf("pop failed!\n");
    //         }
    //     }else{
    //         printf("The stack was empty!\n");
    //     }
    // }

    // printf("\n ______ the stack ______\n");    
    // printStack(theStack);
    
    // printf("\n\n");

    // return;
}