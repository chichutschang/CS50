/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 * Chi-Chu Tschang
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *input;  
    typedef unsigned char BYTE;
    BYTE buffer[512];
    int count = 0;
    char title[8];
    FILE* output = NULL;
    
    //opens memory card file
    input = fopen("card.raw", "rb");
    
    //if unable to open memory card file
    if (input == NULL)
    {
        printf("Could not open %s\n", "card.raw");
        return 2;
    }
    
    else
    {
        //repeats until end of card
        while (!feof(input)) 
        {
            fseek(input, 0, SEEK_END);
            input = fopen("card.raw", "rb");

            //reads 512 bytes into buffer
            while (fread(buffer, 512, 1, input)== 1)
            {
                int i = 0; 
                { 
                //finds beginning of jpeg 
                if (buffer[i] == 0xff && buffer[i+1] == 0xd8 && buffer[i+2] == 0xff && (buffer[i+3] == 0xe0 || buffer[i+3] == 0xe1))
                    {
                        //if an output file is already open, close it
                        if(output != NULL)
                        {
                            fclose(output);
                            output=NULL;
                        }
                        
                        //creates filenames jpeg files 
                        if (count < 10)
                            {
                            sprintf(title, "00%d.jpg", count);
                            }
                        else if (count > 9 || count < 100)
                            {
                            sprintf(title, "0%d.jpg", count);
                            }                           
                        
                        //open a new file 
                        output = fopen(title, "w");
                        
                        //writes into new jpeg file                       
                        fwrite(buffer, 512, 1, output);   

                        //counts number of jpegs in memory card file
                        count++;             
                        }
                        
                        else
                        {
                        //continue writing to old file if it is not beginning of file
                        if(output != NULL)
                        fwrite(buffer, 512, 1, output);
                        }                       
                    }
                }
            }
            //closes remaining files
            fclose(input);    
            fclose(output);
            return 0;
    }   
}
