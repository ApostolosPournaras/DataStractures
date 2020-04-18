#include<stdio.h>
#include <sys/time.h> // for clock_gettime()
#include <stdlib.h> // For random(), RAND_MAX
#include <math.h>
#include "BinaryTree.h"

void main(){
    struct timeval insert_start, insert_end;
    struct timeval find_start, find_end;
    struct timeval delete_start, delete_end;
    long insert_secs_used, insert_micros_used;
    long find_secs_used, find_micros_used;
    long delete_secs_used, delete_micros_used;

    printf("------ BST performance test ------\n");
    printf("elements qty_p1\tInsert Time elasped(sec)\tSearch Time elasped(sec)\tDelete Time elasped(sec)\n");

    int q;
    int i;
    int x;

    for(q=5; q<=25; q++){

        struct BST *aBST = newBST();

        int qty_p1 = (int)pow(2, q);
        //printf("qty_p1_p1 = %i\n", qty_p1);
        gettimeofday(&insert_start, NULL);
        int denom;
        int coef;
        for(denom=2 ; denom<=qty_p1; denom*=2){
            for(coef=1; coef<=denom-1; coef+=2){
                //printf("coef = %i, denom = %i. Insert value = %i\n",coef, denom, coef*(qty_p1/denom));
                insert(aBST, coef*(qty_p1/denom));
            }
        }
        gettimeofday(&insert_end, NULL);

        // printf("PLR---------\n");
        // printPLR(aBST->root);
        // printf("LPR---------\n");
        // printLPR(aBST->root);
        // printf("LRP---------\n");
        // printLRP(aBST->root);

        gettimeofday(&find_start, NULL);
        for(coef=1; coef<=qty_p1-1; coef+=2){
            //printf("find value = %i\n",coef);
            find(aBST, coef);
        }
        gettimeofday(&find_end, NULL);

        gettimeofday(&delete_start, NULL);
        for(denom=qty_p1; denom>=2; denom/=2){
            for(coef=1; coef<=denom-1; coef+=2){
                //printf("coef = %i, denom = %i. delete value = %i\n",coef, denom, coef*(qty_p1/denom));
                delete(aBST, coef*(qty_p1/denom));
            }
        }
        gettimeofday(&delete_end, NULL);

        //printLPR(aBST->root);

        insert_secs_used=(insert_end.tv_sec - insert_start.tv_sec); //avoid overflow by subtracting first
        insert_micros_used= ((insert_secs_used*1000000) + insert_end.tv_usec) - (insert_start.tv_usec);

        find_secs_used=(find_end.tv_sec - find_start.tv_sec); //avoid overflow by subtracting first
        find_micros_used= ((find_secs_used*1000000) + find_end.tv_usec) - (find_start.tv_usec);

        delete_secs_used=(delete_end.tv_sec - delete_start.tv_sec); //avoid overflow by subtracting first
        delete_micros_used= ((delete_secs_used*1000000) + delete_end.tv_usec) - (delete_start.tv_usec);

        printf("%i\t%f\t%f\t%f\n",qty_p1, (float)insert_micros_used/1000000.0, (float)find_micros_used/1000000.0, (float)delete_micros_used/1000000.0);
        free(aBST);
    }
    // insert(aBST, 4);
    // insert(aBST, 3);
    // insert(aBST, 8);
    // insert(aBST, 1);
    // insert(aBST, 2);
    // insert(aBST, 10);

    // printPLR(aBST->root);
    // printf("\n\n");
    // printLPR(aBST->root);
    // printf("\n\n");
    // printLRP(aBST->root);
    // printf("\n\n");

    // printf("find 3? %s\n", find(aBST, 3)!=NULL?"yes":"no");
    // printf("find 4? %s\n", find(aBST, 4)!=NULL?"yes":"no");
    // printf("find 1? %s\n", find(aBST, 1)!=NULL?"yes":"no");
    // printf("find 8? %s\n", find(aBST, 8)!=NULL?"yes":"no");
    // printf("find 2? %s\n", find(aBST, 2)!=NULL?"yes":"no");
    // printf("find 10? %s\n", find(aBST, 10)!=NULL?"yes":"no");
    // printf("find 5? %s\n", find(aBST, 5)!=NULL?"yes":"no");
    // printf("find 6? %s\n", find(aBST, 6)!=NULL?"yes":"no");
    
    // delete(aBST, 777);
    // delete(aBST, 3);
    // printPLR(aBST->root);
    // printf("\n\n");
    // printLPR(aBST->root);
    // printf("\n\n");
    // printLRP(aBST->root);
    // printf("\n\n");
    // delete(aBST, 8);
    // printPLR(aBST->root);
    // printf("\n\n");
    // printLPR(aBST->root);
    // printf("\n\n");
    // printLRP(aBST->root);
    // printf("\n\n");
    // delete(aBST, 1);
    // printPLR(aBST->root);
    // printf("\n\n");
    // printLPR(aBST->root);
    // printf("\n\n");
    // printLRP(aBST->root);
    // printf("\n\n");
    // delete(aBST, 2);
    // printPLR(aBST->root);
    // printf("\n\n");
    // printLPR(aBST->root);
    // printf("\n\n");
    // printLRP(aBST->root);
    // printf("\n\n");
    // delete(aBST, 10);
    // printPLR(aBST->root);
    // printf("\n\n");
    // printLPR(aBST->root);
    // printf("\n\n");
    // printLRP(aBST->root);
    // printf("\n\n");
    // delete(aBST, 4);

    // printPLR(aBST->root);
    // printf("\n\n");
    // printLPR(aBST->root);
    // printf("\n\n");
    // printLRP(aBST->root);
    // printf("\n\n");

    return;
}