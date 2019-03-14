#include<stdio.h>
#include<stdlib.h>
#include "bhHeaders.h"

/*
    Function to print quad tree data into csv files
*/
void xy_trees(struct quad* nd){
    FILE * f; 
    f = fopen("/home/albes/Desktop/nodestd.txt", "w"); /* open the file for writing*/
    printf("Writting...\n");
    /* write 10 lines of text into the file stream*/    
    fprintf(f, "N,X,Y,S\n");
    printdata(nd, f);
    /* close the file*/  
    fclose (f);
    printf("Closed file.\n");
}