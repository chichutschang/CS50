/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 * Chi-Chu Tschang
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char* multiple = argv[1];
    char* infile = argv[2];
    char* outfile = argv[3];

    //convert multiple to integer
    int n = atoi(multiple);
    
    //ensures multiple is less than or equal to 100 and a positive number
    if (n >= 100 || n < 0)
    {
        printf("Please input another number\n"); 
        return 2;
    }
       
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
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
        return 5;
    }

    //keep original width & height
    int original_width = bi.biWidth;

    //create new header files
    BITMAPFILEHEADER bfNew = bf;
    BITMAPINFOHEADER biNew = bi;

    //store new width after multiply width by multiple
    biNew.biWidth = bi.biWidth * n;
  
    //store new height after multiply height by multiple
    biNew.biHeight = bi.biHeight * n;

    // determine padding of infile
    int original_padding =  (4 - (original_width * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine padding of outfile
    int padding = (4 - (biNew.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //resize raw BMP data
    biNew.biSizeImage = abs(biNew.biHeight) * (biNew.biWidth * sizeof(RGBTRIPLE) + padding);
    
    //resize size of BMP file
    bfNew.bfSize = biNew.biSizeImage + bf.bfOffBits;
   
    // write outfile's BITMAPFILEHEADER
    fwrite(&bfNew, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biNew, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //iterate by n times
        for (int m = 0; m < n; m++)       
        {              
            // iterate over pixels in scanline
            for (int j = 0; j < original_width; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                triple.rgbtBlue = 0x00;
                triple.rgbtGreen = 0x00;
                triple.rgbtRed = 0xff;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                    
                //horizontal resizing
                for (int i = 0; i < n; i++)
                {
                   // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }           
            }

            // skip over padding, if any
            fseek(inptr, original_padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }

       //move cursor to beginning of line if repeating vertically
       if ( m < n - 1 )
            {           
            fseek(inptr, -(original_width * sizeof(RGBTRIPLE) + original_padding) , SEEK_CUR);
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
