#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    //check if argc points to 2nd argc
    if(argc != 2)
    {
        printf("Usage: ./caesar key");
        return 1;   
    }   

    //get key 
    string key = argv[1]; 
        
    //check if keyword is alphabet
    for(int k = 0; k < strlen(key); k++)
        {
        if(!isalpha(key[k]))
            {
            printf("Usage: ./caesar key");
            return 1;
            }          
        }
        
    //get message   
    string c = GetString();
   
    if (c != NULL);
    {
    int j = 0;
             
    for (int i = 0, n = strlen(c); i < n; i++)
         {                                   
                //check if string is alphabet                
                if (isalpha(c[i]))
                {
                    int k = j % strlen(key);                              
                
                //if string is lower case & key is lower case
                if (islower(c[i]) && islower(key[k]))                   
                    {                  
                        int lc = (key[k]) - 97;    
                        int l = ((c[i] - 97 + lc) % 26) + 97;
                        printf("%c", l);   
                    }
                
                //if string is upper case & key is lower case
                if (isupper(c[i]) && islower(key[k]))
                    {    
                        int lc = (key[k]) - 97;    
                        int l = ((c[i] - 65 + lc) % 26) + 65;
                        printf("%c", l);
                    } 
                       
                //if string is upper case & key is upper case   
                if (isupper(c[i]) && isupper(key[k]))
                    {             
                        int uc = (key[k]) - 65;    
                        int u = ((c[i] - 65 + uc ) % 26) + 65;
                        printf("%c", u);
                    }
                    
                //if string is lower case & key is upper case
                if (islower(c[i]) && isupper(key[k]))
                    {
                        int uc = (key[k]) - 65;
                        int u = ((c[i] - 97 + uc ) % 26) + 97;
                        printf("%c", u); 
                    }
                j++; 
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
        
