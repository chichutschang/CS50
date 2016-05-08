#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
        
    do
    {
    printf("height: ");
    n = GetInt();
    
    if ( n > 23)
    {
    printf("height: ");
    n = GetInt();
    }
           
    //for every row
    for (int r = 1; r <= n; r++)
    {

    //print space
        for (int s = n - r; s > 0; s--)
        {
        printf(" ");
        } 
         
    //print hash
    
        for (int h = 0; h <= r; h++)
        {
        printf("#");
        }

    //print new line
    printf("\n");
    }
    }
   
    while (n < 0);
    return 0;
    
}
