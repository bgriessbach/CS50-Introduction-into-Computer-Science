#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, string argv[])

{
    if (argc!=2)
        {
            printf("Please enter one non-negative number\n");
            return 1;
        }
    printf("plaintext:");
    string plaintext=get_string();
    if (plaintext!=NULL)
{
    int key= atoi(argv[1]);
    int letter=0;
    
    printf("ciphertext:");
    
    for (int i=0, length= strlen(plaintext); i<length;i++)
    {
    
     if (isupper(plaintext[i]))
        {
                char l= plaintext[i];
                letter= (int)l;
                letter-= 65;
                letter= (letter+key)%26;
                letter+= 65;
                printf ("%c", (char)letter);
        }
    else if (islower(plaintext[i]))
        {
                char l= plaintext[i];
                letter= (int)l;
                letter-= 97;
                letter= (letter+key)%26;
                letter+= 97;
                printf ("%c", (char)letter);
        }
    else
        {
            printf("%c", plaintext[i]);
        }
    }

    printf("\n");
}
}
