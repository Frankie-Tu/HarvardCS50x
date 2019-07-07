#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool checkSignature(unsigned char *buf);

int main(int argc, char *argv[])
{   
    // ensuring proper usage
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: ./recover memoryCard");
        return 1;
    }
    
    // open input file
    FILE *input = fopen(argv[1], "r");
    
    if (input == NULL)
    {   
        fprintf(stderr, "Cannot open file: %s", argv[1]);
        return 2;
    }
    
    int byteRead = 512;
    int imageCount = 0;
    
    // initialize array to hold output file name and output file pointer
    char outFile[10];
    FILE *output = NULL;
    
    // if the bytes read are less than one JPEG block(512 bytes), we have reached EOF
    while (byteRead == 512)
    {
        /* 
        unsigned char of size 1 byte has range of 0 - 255 which aligns with 1 byte of data from JPEG (eg. 0xff)
        512 bytes per block of JPEG image
        */
        unsigned char buffer[512];
        
        // read 512 bytes from input file to array 
        byteRead = fread(&buffer, 1, 512, input);
        
        // if JPEG signature found in the first 4 bytes of memory, this marks the beginning of a JPEG file
        if (checkSignature(buffer))
        {   
            // close any opened output file
            if (output)
            {
                fclose(output);
            }
            
            // output file name in 00i.jpg format where $i is the current image count
            sprintf(outFile, "%03i.jpg", imageCount);
            
            output = fopen(outFile, "w");
            
            imageCount++;
        }
        
        // only write to the file if block size is correct
        if (output && byteRead == 512)
        {
            fwrite(buffer, 1, 512, output);
        }
    }
}

bool checkSignature(unsigned char *buf)
{   
    /*
    check first four bytes of the block to see if they match JPEG pattern
    */
    if (buf[0] == 0xff &&
        buf[1] == 0xd8 &&
        buf[2] == 0xff &&
        (buf[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
