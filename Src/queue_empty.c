#include<stdio.h>
#include<stdbool.h>

/*
    Boolean function checking if queue is empty
*/
bool queue_empty()
{
  return (begin==NULL && end==NULL);
}