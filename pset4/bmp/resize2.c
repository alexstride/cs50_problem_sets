#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    //ensure proper usage of the resizer
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
    }
    
    //remember scale factor
    int n = atoi(argv[1]);
    if(n<1 || n>1000)
    {
        printf("Invalid scale factor. Enter value between 1 and 100.");
        return 1;
    }
    
    //remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    //open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n",infile);
        return 2;
    }
    
    //open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        printf("Could not create %s.\n", outfile);
        return 2;
    }
    
    //read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    //ensure infule is likely to be a 24bit uncompressed BMP4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // ADDED: save old dimensions of bitmap before continuing
    int oldWidth = bi.biWidth; 
    int oldHeight = bi.biHeight; // CAUTION: Will probably be negative to signify top-down bmp
    int oldPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE))%4)%4;  
    
    //make header transformations
    bi.biWidth = oldWidth*n;
    bi.biHeight = oldHeight*n;
    
    // determine required bytes of padding
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE))%4)%4;
    
    //set relevant sizes
    bi.biSizeImage = ((bi.biWidth*sizeof(RGBTRIPLE))+padding)*abs(bi.biHeight);
    bf.bfSize = 54 + bi.biSizeImage;
    
    //Create the new file
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    //Ascertain the full width of the bmp (including padding)
    int width = (oldWidth*sizeof(RGBTRIPLE))+oldPadding;
    
    
    //iterate over inFile's scanlines
    for(int i = 0, h = abs(oldHeight); i < h; i++)
    {
        //loop n times
        for(int rowNum = 0; rowNum < n; rowNum++)
        {
            //write out each byte, multiplying by the scale factor as we go
            
            //iterating over the bytes in the line
            for(int byteIndex = 0; byteIndex < oldWidth; byteIndex++)
            {
                // temporary storage
                RGBTRIPLE triple;
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write triple to outfile n times
                for (int k = 0; k < n; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
            //skip over padding in the input file
            fseek(inptr, oldPadding, SEEK_CUR);
            
            //add in any new padding
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
            
            //if less than n-1, seek inptr back width number of bytes
            if(rowNum < n - 1)
            {
                fseek(inptr,(width*(-1)),SEEK_CUR);
            }
        }
            
    }
    
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}