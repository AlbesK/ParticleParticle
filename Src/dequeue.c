#include<stdio.h>
#include"bhHeaders.h"

 /*
    Pop element from queue and free its memory
 */
void dequeue()
{
    struct linkedList* temp = begin;
    if(begin==NULL){return;}
    if(begin==end){
        begin = NULL;
        end = NULL;
    }
    else{
        begin = begin->next;                    
    }
    free(temp);
}