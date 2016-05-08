#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = GetString();
    
    if (s != NULL);
    {         
    for (int i = 0, n = strlen(s); i < n; i++)
        {
            if (i == 0)
                {
                printf("%c", toupper(s[i]));
                }
            if (s[i] == ' ')
                {
                printf("%c", toupper(s[i+1]));
                }    
            else
                {
                }    
        }     
    printf("\n");
    }    
}

