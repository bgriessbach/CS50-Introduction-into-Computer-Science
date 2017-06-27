#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main (void)
{
string name= get_string();
    if (name!=NULL)
{
     int length= strlen(name);
    
        for (int j=0; j<length;j++)
        {
            if (name[j]!=' ')
            {
              printf("%c", toupper(name[j]));
            do
              {
               j++;
              }
            while (name[j]!=' '&&j<length); 
            }
        }
    printf("\n");
}
}
