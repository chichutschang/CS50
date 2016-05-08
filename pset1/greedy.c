#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main (void)
{
    float f;
      
    do
    {
    printf("O hai! How much change is owed?");
    printf("\n");
    f = GetFloat();
    int i = round(f*100);
    
    if ( f < 0)
    {
    printf("How much change is owed?");
    printf("\n");
    f = GetFloat();
    }    
    
    int q = 0;
    while ( i - (25*q) >= 25)
    {
    q++;
    }
    int w = q;
        
        int d = 0;
        while (i - (25*w) - (10*d) >=10)
        {
        d++;
        }
        int x = d;
            
            int n = 0;
            while (i - (25*w) - (10*x) - (5*n) >=5)
            {
            n++;
            }
            int y = n;
                        
                int p = 0;
                while (i - (25*w) - (10*x) - (5*y) - (1*p) >=1)
                {
                p++;
                }
                int z = p;
                                
                int coins = w + x + y + z;
                printf("%d\n", coins);
             
    }
    while (f < 0);
    return 0;
    
}    
