#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
   //get key
    if(argc != 2)
    {
        printf("Usage: ./caesar key");
        return 1;
    }
    
   //convert key to integer
    int key = atoi(argv[1]); 
   
   string c = GetString();
   
   if (c != NULL);
    {         
    for (int i = 0, n = strlen(c); i < n; i++)
        {
                //leaves a space for space
                if (c[i] == ' ')
                {
                    printf(" ");
                }
                
                //check if argv is alphabet
                else if (isalpha(c[i]))
                {
                //check if argv is lower case
                if (islower(c[i]))
                    {
                    int l = ((c[i] - 97 + key) % 26) + 97;
                    printf("%c", l);
                    }
                //check if argv is upper case    
                if (isupper(c[i]))
                    {
                    int u = ((c[i] - 65 + key ) % 26) + 65;
                    printf("%c", u);
                    }
                }
                else
                {
                printf("%c", c[i]);
                }
        }  
    }
    printf("\n");
    return 0;    
}
