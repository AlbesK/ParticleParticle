#include<stdio.h>
#include<stdbool.h>
#include"bhHeaders.h"

/*
    Boolean function checking if queue is empty
*/
bool queue_empty()
{
  return (begin==NULL && end==NULL);
}