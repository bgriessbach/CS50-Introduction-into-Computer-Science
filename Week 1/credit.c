#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long long number;
    int produkt=0;
    int summe1=0;
    int summe2=0;
    int result=0;
    int produkt2= 0;
    string type;

    do
    {
        printf("Number:");
        number= get_long_long();
    }
    while (number<1);
    
    long long quersumme=number;
    long long counting=number;
    long long typing=number;

//Count numbers    
    int count=0;
    while(counting>0) 
    {
        counting /= 10;
        count++;
    }
//Get first 2 numbers for final "Type"   
    do
    
    {
        typing/= 10;
        count--;
    }
    while (count>2);
    
//Checksum Test Loop   
   do 
   {
    quersumme = quersumme/10;
    produkt=(quersumme % 10)*2;
    printf("product_before is %i\n", produkt);
        if (produkt>9)
        {
            produkt2=(produkt % 10);
            produkt= produkt/10;
            produkt2=produkt2+((produkt % 10));
        }
        
        else
        {
            produkt2=produkt;
        }
    printf("product_after is %i\n", produkt2);    
    summe1= produkt2+summe1;
    quersumme = quersumme / 10;
   }
   while(quersumme > 0);
  printf("Sum_product is %i\n", summe1);
    do 
   {
    summe2= summe2+((number % 10));
    number = number / 100;
   }
   while(number > 0);
   
   result=(summe1+summe2)%10;

//Decide Type of Card   
   
  if (result!=0)
   {
        type="INVALID";
   }

    else if (typing%100==34||typing%100==37)
    {
        type= "AMEX";
    }
    
     else if (typing%100==51||typing%100==52||typing%100==53||typing%100==54||typing%100==55)
    {
        type= "MASTERCARD";
    }
  
   else if (typing/10==4)
   {
           type= "VISA";
   }
    
    else
    {
        type="INVALID";
    }
    
    printf("%s\n", type);
    
}
