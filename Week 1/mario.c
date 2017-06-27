#include <stdio.h>
#include <cs50.h>

int main (void)
{
    int h;     
    do
    {
     printf("Height:");
     h= get_int();   
    } 
    while (h<0||h>=24);
       
    for (int i=0; i<h; i++)
    {
        for (int a=0; a<h-i-1; a++)
        {
            printf(" ");
        }
        for (int b=0; b<i+1; b++)
        {
            printf ("#");
        }
        
        for (int c=0; c<2; c++)
        {
            printf (" ");
        }
        
         for (int d=0; d<i+1; d++)
        {
            printf ("#");
        }
        
        printf("\n");
    }
}
