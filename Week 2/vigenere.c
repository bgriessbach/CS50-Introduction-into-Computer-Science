#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int check_ktemp (char ktemp)
{
    if (isupper(ktemp))
    {
        ktemp=(int)ktemp;
        ktemp-=65;
        return ktemp;
    }
    else
    {
        ktemp=(int)ktemp;
        ktemp-=97;
        return ktemp;
    }
}


int main (int argc, string k[])
{

    if (argc!=2)
        {
            printf("Please enter one non-negative number\n");
            return 1;
        }
    
    string key= k[1];
    
    for (int b=0; b<strlen(key); b++)
    {
        if (isalpha(key[b])==0)
        {
            printf("Please enter one non-negative number\n");
            return 1;
        }
    }
    
    printf("plaintext:");
    string p=get_string();
    if (p!=NULL)
{

    int letter=0;
    int j=0;
    

    printf("ciphertext:");
    
    for (int i=0, length= strlen(p); i<length;i++)
    {
    
     if (isupper(p[i]))
        {
                char l= p[i];
                letter= (int)l;
                char ktemp= key[j];
                letter-= 65;
                ktemp= check_ktemp(ktemp);
                letter= (letter+ktemp)%26;
                letter+=65;
                printf ("%c", (char)letter);
                
                if ((j+1)<strlen(key))
                {
                    j++;
                }
                else
                {
                    j=0;
                }
        }
    else if (islower(p[i]))
        {
                char l= p[i];
                letter= (int)l;
                char ktemp= key[j];
                letter-= 97;
                ktemp= check_ktemp(ktemp);
                letter= (letter+ktemp)%26;
                letter+= 97;
                printf ("%c", (char)letter);
                
                if ((j+1)<strlen(key))
                {
                    j++;
                }
                else
                {
                    j=0;
                }
        }
    else
        {
            printf("%c", p[i]);
        }

    }

    printf("\n");
 }

}
