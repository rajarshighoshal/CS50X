/**
 * recovers JPEG images from .raw file
 * .raw file is given as command-line argument 
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// function for determining file pointer size
long fsize(FILE *fp);

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if(argc != 2)
    {
        fprintf(stderr, "Usage ./recover image\n");
        return 1;
    }
    
    // opening input file
    FILE *card = fopen(argv[1], "r");
    if(card == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }
    
    // determining size of file pointer
    long filesize = fsize(card);
    // determinig no. of blocks
    long blocks;
    if((filesize % 512) == 0)
        blocks = filesize/512;
    else
        blocks = filesize/512 + 1;
        
    // variable to count no. of files
    int filecounter = -1;
    // temporary storage for JPEGs
    FILE *img = NULL;
    // loop for read & write
    for(long i = 0; i < blocks; i++)
    {
        // reading from input file
        BYTE buffer[512];
        fread(buffer, 1, 512, card);
        
        // filename for new JPEG to be created
        char filename[8];
        // checking for begining of JPEG
        if(buffer[0] == 0xff &&
           buffer[1] == 0xd8 &&
           buffer[2] == 0xff &&
           (buffer[3] & 0xf0) == 0xe0)
        {
            // adding file as new JPEG found
            filecounter++;
             
            // closing previously opened img file
            if(img != NULL)
            {
                fclose(img);
            }
        
            // making new JPEG file
            sprintf(filename, "%03i.jpg", filecounter);
            img = fopen(filename, "w");
            if(img == NULL)
            {
                fprintf(stderr, "Problem in creating new file.\n");
                return 3;
            }
        }
        
        // if JPEG has already been found
        if(filecounter >= 0)
        {
            // writing on the open img file
            fwrite(buffer, 512, 1, img);
        }
    }
    
// closing open files
fclose(card);
fclose(img);
}

// implementing fsize
long fsize(FILE *fp)
{
    // checking if file can be opened
    if(fp == NULL)
    {
        printf("File can't be opened\n");
        return -2;
    }
    // determining current position of file
    long prev = ftell(fp);
    // going to the end of file
    fseek(fp, 0L, SEEK_END);
    // determining end position
    long size = ftell(fp);
    // returning to current working position
    fseek(fp, prev, SEEK_SET);
    return size;
}