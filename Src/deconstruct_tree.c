#include<stdio.h>

/*
    Deconstruct quad tree (Postorder)
*/ 
void deconstruct_tree(struct quad* root)
{
    if(root != NULL)
    {
        deconstruct_tree(root->NE);
        deconstruct_tree(root->SE);
        deconstruct_tree(root->SW);
        deconstruct_tree(root->NW);
        if(root->data<0){
            free(root->b);
        }
        free(root);
    }
}