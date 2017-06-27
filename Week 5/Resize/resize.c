#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize zoom infile outfile\n");
        return 1;
    }

    // remember filenames and n
    char *infile = argv[2];
    char *outfile = argv[3];
    int n= atoi(argv[1]);
    
    if (n<1||n>100)
    {
        fprintf(stderr, "Zoom should be between 1 and 100\n");
        return 1;
    }
    
    //open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 1;
    }
    
    //keep track of original padding
    
    int inptr_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //change outfile's BITMAPINFOHEADER (biSize, biWidth, biHeight, biSizeImage)
    //determine new padding for scanlines

    bi.biWidth *=n;
    bi.biHeight *=n;    
    
    int outptr_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    bi.biSizeImage = ((sizeof(RGBTRIPLE) *bi.biWidth)+outptr_padding)*abs(bi.biHeight);
    
    //Update outfile's BITMAPFILEHEADER (bfSize)
    
    bf.bfSize = bi.biSizeImage+ sizeof(BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int height_count = 0, biHeight = abs(bi.biHeight/n); height_count < biHeight; height_count++)
    {
       //added loop for duplication of rows
       for (int row_duplication=0; row_duplication<n; row_duplication++)
       {
           //iterate over each pixel
            for (int pixel = 0; pixel <abs(bi.biWidth/n); pixel++)
            {
                // temporary storage
                RGBTRIPLE triple;
                //read the pixel in inptr
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // write the pixel n times   
                for (int dupe_pixel= 0; dupe_pixel<n; dupe_pixel++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
          //add padding to outfile and set infile cursor back to start of pixel row
            for (int insert_padding = 0; insert_padding < outptr_padding; insert_padding++)
            {
                fputc(0x00, outptr);
            }
            
            //set cursor back to start of row
            fseek (inptr, -1*(int)sizeof(RGBTRIPLE)*(bi.biWidth/n), SEEK_CUR);  
       }
       
        // set cursor to start of next row (past pixels and padding)
        fseek(inptr, ((sizeof(RGBTRIPLE)*(bi.biWidth/n))+inptr_padding), SEEK_CUR);

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
