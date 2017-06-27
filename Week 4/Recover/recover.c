#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    // remember variables
    char *infile = argv[1];
    bool first_JPG = false;
    int JPG_counter= 0;
    unsigned char* search_item = malloc(513);
    char *filename = malloc(8);
    
    //open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
   
    //open output file and create filename
    
    sprintf(filename,"%03d.jpg", JPG_counter);
    FILE *outptr = fopen(filename, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s\n", filename);
        return 1;
    }
    
    // find size of file
    fseek(inptr, 0L, SEEK_END);
    int size=ftell(inptr);
    fseek(inptr, 0L, SEEK_SET);
    
    
    for (int search=0; search<(size/512); search++)
    {
        
        //read in 512 block of memory
        fread(search_item, 512, 1, inptr);
        
        //check for start of JPG
        if (search_item[0]==0xff&&search_item[1]==0xd8&&search_item[2]==0xff&&(search_item[3]& 0xf0)==0xe0)
            {
              
              //if another JPG already exisists, close the outfile, open new one
              if (first_JPG==true)
              {
                  fclose(outptr);
                  JPG_counter++;
                  sprintf(filename,"%03d.jpg", JPG_counter);
                  outptr = fopen(filename, "w");
                if (outptr == NULL)
                    {
                        fclose(inptr);
                        fprintf(stderr, "Could not create %s.\n", filename);
                        return 1;
                    }
              }
            
            //confirm first JPG found
            first_JPG=true;
            }
        
        //if a JPG has been found before, write data in outfile
        if (first_JPG==true)
        {
            fwrite(search_item, 512, 1, outptr);
        }
        
    }

// close all files and free all allocated memory
fclose(inptr);
fclose(outptr);
free(filename);
free(search_item);
}
