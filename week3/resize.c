// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // reading arguments
    char *ptr;
    int n = strtol(argv[1], &ptr, 10);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER inbf;
    fread(&inbf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER inbi;
    fread(&inbi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (inbf.bfType != 0x4d42 || inbf.bfOffBits != 54 || inbi.biSize != 40 ||
        inbi.biBitCount != 24 || inbi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // create headers for output file
    BITMAPINFOHEADER outbi = inbi;
    BITMAPFILEHEADER outbf = inbf;
    
    outbi.biWidth = n * inbi.biWidth;
    outbi.biHeight = n * inbi.biHeight;
    
    // determine padding for scanlines
    int inpadding = (4 - (inbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outpadding = (4 - (outbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // image size = (width + padding) * height
    outbi.biSizeImage = ((sizeof(RGBTRIPLE) * outbi.biWidth) + outpadding) * abs(outbi.biHeight);

    // output BMP total size = headers + image size
    outbf.bfSize = outbi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&outbf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&outbi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(inbi.biHeight); i < biHeight; i++)
    {
        // repeat current scanline n times to make BMP n times taller
        for (int num = 0; num < n; num++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < inbi.biWidth; j++)
            {    
                // temporary storage
                RGBTRIPLE triple;
        
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // repeat each pixel n times to make BMP n times wider
                for (int num2 = 0; num2 < n; num2++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
            // do not go back to the beginning of the scanline if this is the final iteration of current scanline
            if (num < n - 1) 
            {
                fseek(inptr, -inbi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
            
            
            // add padding to output file if any
            for (int k = 0; k < outpadding; k++)
            {
                fputc(0x00, outptr);
            }
        }
        // skip padding input file and move to next scanline
        fseek(inptr, inpadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}