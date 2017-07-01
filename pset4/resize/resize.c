/**
 * Takes bmp file from user as command-line argument.
 * 
 * Takes factor by which the file need to be enlarged
 * as command-line argument.
 * 
 * Resizes the input file by given factor
 * and writes new enlarged bmp file in side file
 * given as command-line argument by user.
 * 
 */
   
#include <ctype.h>       
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    // checking if arg[1] is integer
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            fprintf(stderr, "n must be an integer.\n");
            return 2;
        }
    }
    
    // checking value of in
    int n = atoi(argv[1]);
    if (n <0 || n > 100)
    {
        fprintf(stderr, "n must be a positive integer less than or equal to 100\n");
        return 3;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 4;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 5;
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
        return 6;
    }
    
    // outfile's bi and bf
    BITMAPFILEHEADER bf_out;
    BITMAPINFOHEADER bi_out;
    
    // defining bf and bi for outfile
    bf_out = bf;
    bi_out = bi;
    
    // changinh height and width
    bi_out.biHeight = n * bi.biHeight;
    bi_out.biWidth = n * bi.biWidth;
    
    // determining padding for outfile's scanlines
    int padding_out = (4 - (bi_out.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determining biSizeImage of outfile
    bi_out.biSizeImage = ((sizeof(RGBTRIPLE) * bi_out.biWidth) + padding_out) * abs(bi_out.biHeight);
    
    // total size outfile
    bf_out.bfSize = bi_out.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for infile's scanlines
    int padding_in = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // a measure of the length of an infile line in bytes
    int offset = bi.biWidth * sizeof(RGBTRIPLE) + padding_in;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // for n - 1 times write pixels and padding to outfile
        for (int ver = 0; ver < n ; ver++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // write RGB triple n times to outfile
                for (int hor = 0; hor < n; hor++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
            // skip over input padding, if any
            fseek(inptr, padding_in, SEEK_CUR);
            // add padding to outfile if necessary
            for (int k = 0; k < padding_out; k++)
            {
                fputc(0x00, outptr);
            }
            
            // returning to the initial position of infile's scanline
            fseek(inptr, -offset, SEEK_CUR);
        }
        
        // move the pointer to the start of the next line
        fseek(inptr, offset , SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
