/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{

int max=n-1;
int min=0;
int middle=(max+min)/2;
   
   if (n<=0)
   {
       return false;
   }

while (min<=max)
{
 if (values[middle]==value)
    {
        return true;
    }
 else if (values[middle]<value)
    {
       min=middle+1;
    }
 else if (values[middle]>value)
    {
        max=middle-1;
    }
    middle=(min+max)/2;
}

return false;


}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
int xtemp=0;
int ytemp=0;
int counter=1;

do
{
    for (int x=0; x<(n-1);x++)
    {
        counter=0;
        xtemp=values[x];
        ytemp=values[x+1];
        
        if (xtemp>ytemp)
        {
           values[x]= ytemp;
           values[x+1]= xtemp;
           counter++;
        }
    }
    n--;
} while (counter!=0);  
    return;
}
